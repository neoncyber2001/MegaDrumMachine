using DrumMachineDesktopApp.Models;
using NAudio.Wave;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.ComponentModel;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.ServiceModel.Configuration;
using System.Collections.Concurrent;
using NAudio.Dmo;

namespace DrumMachineDesktopApp
{
    public class FileConverter
    {
        private MD5 hasher;
        BackgroundWorker BatchWorker= new BackgroundWorker();
        public FileConverter()
        {
            hasher = MD5.Create();
        }

        private int _ConversionProgress = 0;
        
        public int ConversionProgress { get => _ConversionProgress; }
        
        protected void ProgressAtomicIncrement()
        {
            Interlocked.Increment(ref _ConversionProgress);
        }


        public String Status { get; protected set; } = string.Empty;
        public int Progress { get; protected set; } = 0;
        public bool isRunning { get => BatchWorker.IsBusy; }
        protected ConcurrentQueue<AudioSample> Scratchqueue { get; set; } = new ConcurrentQueue<AudioSample>();
        public List<AudioSample> Result { get; protected set; }
        public event EventHandler<List<AudioSample>> BatchComplete;
        protected void BatchWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            BackgroundWorker worker = sender as BackgroundWorker;
            List<AudioSample> ConversionList;
            if (e.Argument.GetType() == typeof(List<AudioSample>))
            {
                ConversionList = e.Argument as List<AudioSample>;
            }
            else
            {
                ConversionList = null;
                throw new System.ArgumentException("Incorrect or Invalid Conversion list recieved.");
            }
            String libraryPath = Environment.ExpandEnvironmentVariables( Properties.Settings.Default.Library);
            int ConversionTotal = ConversionList.Count;
            if (!Directory.Exists(libraryPath)) { Directory.CreateDirectory(libraryPath); }
            int counter = 0;
            ConversionList.ForEach((asmp) =>
            {

                if (worker.CancellationPending == true)
                {
                    e.Cancel = true;
                    return;
                }

                string oldName = asmp.FileName;
                worker.ReportProgress((counter / ConversionTotal)*100, oldName);
                string newPath = libraryPath + Path.GetFileNameWithoutExtension(asmp.FileName) + "_processed.wav";
                Debug.WriteLine(newPath);
                ConvertWav(asmp.LocalPath, newPath);
                var fileInformation = new FileInfo(newPath);
                asmp.LocalPath = fileInformation.FullName;
                asmp.FileName = fileInformation.Name;
                asmp.channels = 2;
                asmp.depth = 16;
                asmp.speed = 44100;
                asmp.size = fileInformation.Length;
                var fs = File.OpenRead(newPath);
                asmp.Checksum = BitConverter.ToString(hasher.ComputeHash(fs));
                fs.Close();
                asmp.isScanned = true;
                asmp.isTranscoded = true;
                counter++;
            });
            e.Result = ConversionList;
        }

        public void BatchWorker_UpdateStatus(object sender, ProgressChangedEventArgs e)
        {
            Progress = e.ProgressPercentage;
            Status = (String)e.UserState;
        }

        private void BatchWorker_Completed(object sender, RunWorkerCompletedEventArgs e)
        {
            if (e.Error != null)
            {
                Status = e.Error.GetType().ToString() + "\n" + e.Error.Message;
                Debug.WriteLine(e.Error.ToString());
                Debug.WriteLine(e.Error.Message);
                Debug.WriteLine(e.Error.StackTrace);
            }
            else
            {
                if (e.Cancelled)
                {
                    Status += "Cancled";
                    BatchComplete?.Invoke(this, null);
                }
                else
                {
                    Status = "Done!";
                    this.Result = (List<AudioSample>)e.Result;
                    BatchComplete?.Invoke(this, (List<AudioSample>)e.Result);
                }
            }

        }
        
        public void BatchConvertBackground(List<AudioSample> ConvList)
        {
            BatchWorker = new BackgroundWorker();
            BatchWorker.WorkerSupportsCancellation = true;
            BatchWorker.WorkerReportsProgress = true;
            BatchWorker.DoWork += BatchWorker_DoWork;
            BatchWorker.ProgressChanged += BatchWorker_UpdateStatus;
            BatchWorker.RunWorkerCompleted += BatchWorker_Completed;
            this.Status = "Starting...";
            this.Progress = 0;
            BatchWorker.RunWorkerAsync(ConvList);



        }

        public void CancelBackgroundConvert()
        {
            BatchWorker.CancelAsync();
        }

        /*public async Task<List<AudioSample>> BatchConvertAsync(List<AudioSample> ConvertList)
        {
            if (isConversionRunning)
            {
                throw new Exception("already running");
            }
            return await Task.Run(() =>
            {
                String libraryPath = Properties.Settings.Default.Library;
                ConversionTotal = ConvertList.Count;
                _ConversionProgress = 0;
                List<AudioSample> SampleList = new List<AudioSample>(ConvertList);
                SampleList.ForEach((asmp) =>
                {
                    string newPath = libraryPath + Path.GetFileNameWithoutExtension(asmp.FileName) + "_processed.wav";
                    Debug.WriteLine(newPath);
                    var fileInformation = new FileInfo(newPath);
                    ConvertWav(asmp.LocalPath, newPath);
                    asmp.LocalPath = fileInformation.FullName;
                    asmp.FileName = fileInformation.Name;
                    asmp.channels = 2;
                    asmp.depth = 16;
                    asmp.speed = 44100;
                    asmp.size = fileInformation.Length;
                    var fs = File.OpenRead(newPath);
                    asmp.Checksum = BitConverter.ToString(hasher.ComputeHash(fs));
                    fs.Close();
                    asmp.isScanned = true;
                    asmp.isTranscoded = true;
                });
                isConversionRunning = false;
                return SampleList;
            });
        }

        */

        public void ConvertWav(String InPath, String OutPath, int rate = 44100, int depth = 16)
        {
            using (var reader = new WaveFileReader(InPath))
            {
                
                var DrumMachineFormat = new WaveFormat(441000, 16, 2);

                using (var converter = new WaveFormatConversionStream(DrumMachineFormat, reader))
                {
                    WaveFileWriter.CreateWaveFile(OutPath, converter);
                }
            }
        }
    }
}
