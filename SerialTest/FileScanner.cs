using DrumMachineDesktopApp.Models;
using System;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Text.RegularExpressions;
using System.Diagnostics;
using System.Threading;
using System.Reflection;
using System.Windows.Documents;
using System.Windows.Input;
using NAudio.Wave;
using System.Threading;
using System.Runtime.CompilerServices;
using System.ServiceModel.Syndication;

namespace DrumMachineDesktopApp
{
    public class FileScanner
    {
        private object FileErrorLock = new object();
        private Queue<String> FileErrors = new Queue<string>();
        public String getFileError()
        {
            lock (FileErrorLock)
            {
                return FileErrors.Dequeue();
            }
        }
        public int getCueuedErrors() {
            lock (FileErrorLock)
            {
                return FileErrors.Count;
            }
        }
        protected void addFileError(String err)
        {
            lock (FileErrorLock)
            {
                FileErrors.Enqueue(err);
            }
        }

        public String LocateDrumDataSD()
        {
            String ret = null;
            DriveInfo.GetDrives().ToList().ForEach((d) =>
            {
                if (File.Exists(d.RootDirectory.Name + Properties.Settings.Default.MachineCardHiddenFile))
                {
                    ret= d.Name;
                    return;
                }
            });
            return ret;
        }
        public String LocateSampleDataSD()
        {
            String ret = null;
            DriveInfo.GetDrives().ToList().ForEach((d) =>
            {
                if (File.Exists(d.RootDirectory.Name + Properties.Settings.Default.SampleCardHiddenFile))
                {
                    ret = d.Name;
                    return;
                }
            });
            return ret;
        }
        public object ScratchLock = new object();
        public List<AudioSample> Scratch { get; set; }
        protected string fileSearch = "*.wav";
        protected Regex FileNameParser = new Regex(@"(?<NUM>[0-9]{3})_(?<NAME>\\S+).[wW][aA][vV]");
        private MD5 hasher;
        public FileScanner()
        {
            hasher = MD5.Create();
        }

        public async Task<List<AudioSample>> ScanDirectoryForSamples(String path, bool recurse)
        {
            return await Task.Run(() =>
            {

                List<AudioSample> OutList = new List<AudioSample>();
                List<string> fileCueue = new List<string>();
                if (recurse)
                {
                    this.GetFilesFromDirsReurse(path).ToList().ForEach((f) => fileCueue.Add(f));
                }
                else
                {
                    Directory.GetFiles(path).ToList().ForEach((f) => fileCueue.Add(f));
                }
                fileCueue.ForEach((fileName) =>
                {
                    /*
                    * Regex strings for sorting out files.
                    * (?<NUM>[0-9]{3})(_(?<TYPE>\w+))?_(?<NAME>\S+).[wW][aA][vV]
                    * (?<NUM>[0-9]{3})_(?<NAME>\S+).[wW][aA][vV]
                    */
                    Debug.WriteLine(Path.GetExtension(fileName));
                    if (string.Equals(Path.GetExtension(fileName), ".wav") || string.Equals(Path.GetExtension(fileName), "wav"))
                    {
                        Debug.WriteLine(fileName);
                        String file = Path.GetFileName(fileName);
                        /*String numString = file.Substring(0, file.IndexOf((char)'_'));

                        int num;
                        string sampName;
                        if (int.TryParse(numString, out num))
                        {
                            sampName = file.Substring(file.IndexOf((char)'_') + 1, (file.IndexOf((char)'.') - file.IndexOf((char)'_')));
                        }
                        else
                        {
                            num = -1;
                            sampName = file;
                        }
                        Match m = FileNameParser.Match(file);
                        int num = int.Parse(m.Groups["NUM"].Value);
                        string sampname = m.Groups["NAME"].Value;
                        */
                        String hash = String.Empty;
                        FileStream fs = File.OpenRead(fileName);
                        try
                        {
                            hash = BitConverter.ToString(hasher.ComputeHash(fs));
                        }
                        catch (Exception ex)
                        {
                            Debug.WriteLine("EXCEPTION");
                            Debug.WriteLine(ex.GetType().Name);
                            Debug.WriteLine(ex.ToString());
                            Debug.WriteLine(ex.Message);
                            Debug.WriteLine(ex.StackTrace);
                            Debug.WriteLine("on thread " + Thread.CurrentThread.ManagedThreadId.ToString());
                            if (ex.GetType().GetTypeInfo().IsSubclassOf(typeof(System.IO.IOException)))
                            {
                                addFileError("Unable to process " + fileName + " due to an I/O Exception.\n" + ex.Message);
                            }
                        }
                        finally
                        {
                            fs.Close();
                        }
                        OutList.Add(new AudioSample() { Checksum = hash, FileName = file, LocalPath = fileName});
                    }
                    //else skip
                });
                return OutList;
            });
        }



        public async Task ScanAndCreateAuditFile(String path, bool recurse, String OutputFile)
        {
            await Task.Run(() =>
            {
                lock (ScratchLock)
                {
                    Scratch = new List<AudioSample>();

                    List<string> fileCueue = new List<string>();
                    Queue<string> csvLines = new Queue<string>();
                    if (recurse)
                    {
                        this.GetFilesFromDirsReurse(path).ToList().ForEach((f) => fileCueue.Add(f));
                    }
                    else
                    {
                        Directory.GetFiles(path).ToList().ForEach((f) => fileCueue.Add(f));
                    }

                    fileCueue.ForEach((fileName) =>
                    {
                        /*
                        * Regex strings for sorting out files.
                        * (?<NUM>[0-9]{3})(_(?<TYPE>\w+))?_(?<NAME>\S+).[wW][aA][vV]
                        * (?<NUM>[0-9]{3})_(?<NAME>\S+).[wW][aA][vV]
                        */
                        Debug.WriteLine(Path.GetExtension(fileName));
                        if (string.Equals(Path.GetExtension(fileName), ".wav") || string.Equals(Path.GetExtension(fileName), "wav"))
                        {
                            Debug.WriteLine(fileName);
                            String file = Path.GetFileName(fileName);
                            String numString = file.Substring(0, file.IndexOf((char)'_'));

                            int num;
                            string sampName;
                            if (int.TryParse(numString, out num))
                            {
                                sampName = file.Substring(file.IndexOf((char)'_') + 1, (file.IndexOf((char)'.') - file.IndexOf((char)'_')));
                            }
                            else
                            {
                                num = -1;
                                sampName = file;
                            }
                            /*
                            Match m = FileNameParser.Match(file);
                            int num = int.Parse(m.Groups["NUM"].Value);
                            string sampname = m.Groups["NAME"].Value;
                            */
                            String hash = String.Empty;
                            FileStream fs = File.OpenRead(fileName);
                            try
                            {
                                hash = BitConverter.ToString(hasher.ComputeHash(fs));
                            }
                            catch (Exception ex)
                            {
                                Debug.WriteLine("EXCEPTION");
                                Debug.WriteLine(ex.GetType().Name);
                                Debug.WriteLine(ex.ToString());
                                Debug.WriteLine(ex.Message);
                                Debug.WriteLine(ex.StackTrace);
                                Debug.WriteLine("on thread " + Thread.CurrentThread.ManagedThreadId.ToString());
                            }
                            finally
                            {
                                fs.Close();
                            }
                            Scratch.Add(new AudioSample() { SampleNumber = num, Checksum = hash, FileName = file, isTransfered = true });
                            csvLines.Enqueue(file + ", " + num.ToString() + ", " + sampName + ", " + hash);
                        }
                        //else skip
                    });

                    //todo: Output CSV
                    Debug.WriteLine("TESTDUMP");
                    if (File.Exists(OutputFile))
                    {
                        File.Delete(OutputFile);
                    }
                    using (FileStream OutputStream = File.OpenWrite(OutputFile))
                    {
                        while (csvLines.Count > 0)
                        {
                            String outputString = csvLines.Dequeue();
                            RawDatalogger.WriteEntry(outputString,this);
                            OutputStream.Write(Encoding.UTF8.GetBytes(outputString), 0, outputString.Length);
                            OutputStream.Write(Encoding.UTF8.GetBytes(Environment.NewLine), 0, Environment.NewLine.Length);
                        }
                    }
                }

                
            });
        
        }
        protected List<string> GetFilesFromDirsReurse(string path)
        {
            List<string> files = new List<string>();
            try
            {
                if (Directory.Exists(path))
                {
                    Directory.GetDirectories(path).ToList().ForEach((dir) =>
                    {
                        Debug.WriteLine(dir);
                        GetFilesFromDirsReurse(dir).ForEach((a) => files.Add(a));
                    });
                    Directory.GetFiles(path, fileSearch).ToList().ForEach((f) => files.Add(f));
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.ToString());
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace.ToString());
            }
            return files;
        }
    }
}
