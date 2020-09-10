using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using SerialTest.Models;
using System.Windows.Input;
using Microsoft.Win32;
using System.Media;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization.Formatters;
using System.Diagnostics;
using System.Security.Cryptography;
using System.Windows;

namespace SerialTest
{
    

    public class LibraryVM : INotifyPropertyChanged
    { 
        public LibraryVM()
        {
            Auditioner = new SoundPlayer();
            //Todo check to see if library exists.
            //Temp Design Data
        }
        protected bool isAuditioning = false;
        protected SoundPlayer Auditioner;

        private bool _isUiEnabled=true;

        public bool isUiEnabled
        {
            get => _isUiEnabled;
            set
            {
                _isUiEnabled = value;
                NotifyPropertyChanged();
            }
        }


        public void UPdateSD()
        {
            DriveInfo[] drives = System.IO.DriveInfo.GetDrives();
            List<string> temp = new List<string>();
            foreach(DriveInfo drv in drives)
            {
                if (drv.DriveType == DriveType.Removable)
                {
                    temp.Add(drv.Name);
                }
            }
            _Drives = new ObservableCollection<string>(temp);
            NotifyPropertyChanged("Drives");
        }


        protected ObservableCollection<String> _Drives = new ObservableCollection<String>();
        public ReadOnlyObservableCollection<String> Drives
        {
            get => new ReadOnlyObservableCollection<String>(_Drives);
        }

        protected ObservableCollection<Models.AudioSample> _AudioSamples = new ObservableCollection<Models.AudioSample>();
        public ReadOnlyObservableCollection<Models.AudioSample> AudioSamples
        {
            get => new ReadOnlyObservableCollection<Models.AudioSample>(_AudioSamples);
        }
        public void Add_AudioSamples(Models.AudioSample value)
        {
            _AudioSamples.Add(value);
            NotifyPropertyChanged("AudioSamples");
        }
        public void Remove_AudioSamples(Models.AudioSample value)
        {
            _AudioSamples.Remove(value);
            NotifyPropertyChanged("AudioSamples");
        }

        protected async Task ImportWavFiles()
        {
            Task tsk = new Task(() =>
            {
                OpenFileDialog openFD = new OpenFileDialog();
                openFD.Title = "Import Wav File";
                openFD.Filter = "Audio Samples|*.wav";
                openFD.Multiselect = true;
                List<String> importCueue = new List<string>();
                if (openFD.ShowDialog() == true)
                {
                    openFD.FileNames.ToList().ForEach((fn) => importCueue.Add(fn));
                }
                foreach (String Pth in importCueue)
                {
                    if (File.Exists(Pth))
                    {
                        FileInfo info = new FileInfo(Pth);
                        Add_AudioSamples(new AudioSample()
                        {
                            FileName = Path.GetFileName(Pth),
                            LocalPath = Path.GetFullPath(Pth),
                            size = info.Length
                        });

                    }
                }
            });
            await tsk;
        }


        protected async Task AuditionSample(String path)
        {
            isAuditioning = true;
            Auditioner.SoundLocation = path;
            await Task.Run(() => Auditioner.PlaySync());
            isAuditioning = false;
        }

        protected async Task SaveToDisk()
        {
            String outfile = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + Properties.Settings.Default.DataDir + Properties.Settings.Default.SampleLib;
            Debug.WriteLine(outfile);
            String outdir = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + Properties.Settings.Default.DataDir;
            if (!Directory.Exists(outdir))
            {
                Directory.CreateDirectory(outdir);
            }
            if (File.Exists(outfile))
            {
                File.Delete(outfile);
            }
            await Task.Run(()=> {
                FileStream stream = File.Create(outfile);
                BinaryFormatter formatter = new BinaryFormatter();
                formatter.Serialize(stream, _AudioSamples);
                stream.Close();
            });
        }

        protected void LoadFromDisk()
        {
            String inFile = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + Properties.Settings.Default.DataDir + Properties.Settings.Default.SampleLib;
            Debug.WriteLine(inFile);
            if (File.Exists(inFile))
            {
                FileStream stream = File.OpenRead(inFile);
                BinaryFormatter formatter = new BinaryFormatter();
                ObservableCollection<AudioSample> OutTest = (ObservableCollection<AudioSample>)formatter.Deserialize(stream);
                stream.Close();
                if (OutTest != null)
                {
                    _AudioSamples = OutTest;
                }
                else
                {
                    Debug.WriteLine("Out is not correct");
                    
                }
                NotifyPropertyChanged("AudioSamples");
            }
        }

        protected void NotifyPropertyChanged([CallerMemberName] String PropertyName = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(PropertyName));
        }
        public event PropertyChangedEventHandler PropertyChanged;


        public List<CommandBinding> getCommandBindings()
        {
            List<CommandBinding> cb = new List<CommandBinding>();
            cb.Add(new CommandBinding(Commands.SampleCommands.ImportSamples, ImportSamples_Executed, ImportSamples_CanExecute));
            cb.Add(new CommandBinding(Commands.SampleCommands.ScanSamples, ScanSamples_Executed, ScanSamples_CanExecute));
            cb.Add(new CommandBinding(Commands.SampleCommands.UpdateDrives, UpdateDrives_Executed, UpdateDrives_CanExecute));
            cb.Add(new CommandBinding(Commands.SampleCommands.AuditionSample, Audition_Executed, Audition_CanExecute));
            cb.Add(new CommandBinding(Commands.SampleCommands.SaveLibrary, SaveLibrary_Executed, SaveLibrary_CanExecute));
            cb.Add(new CommandBinding(Commands.SampleCommands.LoadLibrary, LoadLibrary_Executed, LoadLibrary_CanExecute));
            cb.Add(new CommandBinding(Commands.SampleCommands.ScanSDCard, ScanSDCard_Executed, ScanSDCard_CanExecute));
            return cb;
        }


        //CommandBindingEventHandlers for ScanSDCard
        private void ScanSDCard_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            if (e.Parameter!=null && e.Parameter.GetType() == typeof(String))
            {
                String param = e.Parameter as String;
                if (param != String.Empty)
                {
                    e.CanExecute = true;
                }
                else
                {
                    e.CanExecute = false;
                }

            }
            else
            {
                e.CanExecute = false;
            }
        }

        private async void ScanSDCard_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            String param = e.Parameter as String;
            if (File.Exists(param + Properties.Settings.Default.OnCardSampleData))
            {
                FileScanner scanner = new FileScanner();
                await scanner.ScanAndCreateAuditFile(param, true, param + Properties.Settings.Default.OnCardSampleData);
            }
            else
            {
                MessageBoxResult result= MessageBox.Show("The data file does not exist. Would you like to create a new one?", "Data File Not On Device", MessageBoxButton.YesNo);
                if (result == MessageBoxResult.Yes)
                {
                    FileScanner scanner = new FileScanner();
                    await scanner.ScanAndCreateAuditFile(param, true, param + Properties.Settings.Default.OnCardSampleData);
                }
            }
        }


        //CommandBindingEventHandlers for LoadLibrary
        private void LoadLibrary_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            //Todo
            e.CanExecute = true;
        }

        private void LoadLibrary_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            LoadFromDisk();
            //ToDo
        }

        //CommandBindingEventHandlers for SaveLibrary
        private void SaveLibrary_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            //Todo
            e.CanExecute = true;
        }

        private async void SaveLibrary_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            await SaveToDisk();
        }

        //CommandBindingEventHandlers for Audition
        private void Audition_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            if (!isAuditioning && e.Parameter!=null)
            {
                e.CanExecute = true;
            }
            else
            {
                e.CanExecute = false;
            }
        }

        private async void Audition_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            AudioSample samp = e.Parameter as AudioSample;
            await AuditionSample(samp.LocalPath);
            //ToDo
        }


        //CommandBindingEventHandlers for UpdateDrives
        private void UpdateDrives_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            //Todo
            e.CanExecute = true;
        }

        private void UpdateDrives_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            this.UPdateSD();
        }


        //CommandBindingEventHandlers for ScanSamples
        private void ScanSamples_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            //Todo
            e.CanExecute = true;
        }

        private async void ScanSamples_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            await ScanAudioSamples();
            //ToDo
        }


        //CommandBindingEventHandlers for ImportSamples
        private void ImportSamples_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            //Todo
            e.CanExecute = true;
        }

        private async void ImportSamples_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            await this.ImportWavFiles();
            //ToDo
        }



        protected async Task ScanAudioSamples()
        {
            isUiEnabled = false;
            using (var md5 = MD5.Create())
            {
                ObservableCollection<AudioSample> workingcopy = new ObservableCollection<AudioSample>(_AudioSamples.ToList());
                await Task.Run(() =>
                {
                    workingcopy.ToList().ForEach((smp) =>
                    {
                        using (var stream = File.OpenRead(smp.LocalPath))
                        {
                            smp.Checksum= BitConverter.ToString(md5.ComputeHash(stream));
                        }

                    });
                });

                _AudioSamples = workingcopy;
                NotifyPropertyChanged("AudioSamples");
            };
            isUiEnabled = true;
        }
    }
}
