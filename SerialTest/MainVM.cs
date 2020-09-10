using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Diagnostics;
using System.Windows.Input;
using System.Windows.Controls;
using System.IO;
using SerialTest.Models;
namespace SerialTest
{

    public class MainVM : INotifyPropertyChanged
    {
        private MainWindow owner1;
        public MainWindow owner
        {
            get => owner1;
            set
            {
                if (owner1 != null)
                {
                    owner1.bnkView.VM.EditPattern -= BankVM_EditPattern;
                }
                owner1 = value;
                owner1.bnkView.VM.EditPattern += BankVM_EditPattern;
            }
        }
        private PatternBank _CurrentBank;

        public PatternBank CurrentBank
        {
            get => _CurrentBank;
            set
            {
                _CurrentBank = value;
                NotifyPropertyChanged();
            }
        }

        protected void NotifyPropertyChanged([CallerMemberName] String PropertyName = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(PropertyName));
        }
        public event PropertyChangedEventHandler PropertyChanged;

        private SerialPort SerialConnection;


        private LibraryVM _AudioSamples = new LibraryVM();

        public LibraryVM AudioSamples
        {
            get => _AudioSamples;
            set
            {
                _AudioSamples = value;
                NotifyPropertyChanged();
            }
        }

        private PatternBankVM _PatternBankVM;

        public PatternBankVM BankVM
        {
            get => _PatternBankVM;
            set
            {
                _PatternBankVM = value;
                NotifyPropertyChanged();
            }
        }



        protected ObservableCollection<String> _SerialPortNames = new ObservableCollection<String>();
        public ReadOnlyObservableCollection<String> SerialPortNames
        {
            get => new ReadOnlyObservableCollection<String>(_SerialPortNames);
        }
        public void RefreshSerialPorts()
        {
            _SerialPortNames.Clear();
            foreach (String sname in SerialPort.GetPortNames())
            {
                _SerialPortNames.Add(sname);
            }
            NotifyPropertyChanged("SerialPortNames");
        }


        protected String _SelectedPortName = "";

        public String SelectedPortName
        {
            get => _SelectedPortName;
            set
            {
                _SelectedPortName = value;
                NotifyPropertyChanged();
            }
        }


        private int _SerialBaud = 9600;

        public int SerialBaud
        {
            get => _SerialBaud;
            set
            {
                _SerialBaud = value;
                NotifyPropertyChanged();
            }
        }

        virtual public bool isConnected
        {
            get
            {
                if (SerialConnection != null && SerialConnection.IsOpen)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }

        void Connect()
        {
            if (!isConnected)
            {
                Debug.WriteLine("Connecting");
                RawDataLog += "Connect at " + DateTime.Now.ToString() + " Port:" + SelectedPortName + " Baud:" + SerialBaud + "\n";
                if (SerialConnection == null)
                {
                    SerialConnection = new SerialPort(_SelectedPortName, _SerialBaud);
                }
                if (!SerialConnection.IsOpen)
                {
                    SerialConnection.ReceivedBytesThreshold = 1;
                    SerialConnection.DtrEnable = true;
                    SerialConnection.DataReceived += SerialConnection_DataReceived;
                    SerialConnection.Open();

                }
            }
        }

        void Disconnect()
        {
            if (isConnected)
            {
                Debug.WriteLine("Disconnecting");
                RawDataLog += "Disconnect\n";
                SerialConnection.Close();
                SerialConnection.DataReceived -= SerialConnection_DataReceived;
                SerialConnection.Dispose();
                SerialConnection = null;
            }
        }

        private String _RawDataLog = "";

        public String RawDataLog
        {
            get => _RawDataLog;
            set
            {
                _RawDataLog = value;
                NotifyPropertyChanged();
            }
        }


        private String InputCommand;
        private int InputMode = 0;
        private void SerialConnection_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {

            Debug.WriteLine("Incoming Serial Data");
            var prt = sender as SerialPort;

            if (InputMode == 0)
            {
                while (prt.BytesToRead > 0)
                {
                    int inputByte = prt.ReadByte();
                    this.RawDataLog += "0x" + Convert.ToString(inputByte, 16) + " ";
                    if (inputByte == 0x1B)
                    {
                        Debug.WriteLine("Escape Recieved");
                        ProcessCommand(InputCommand);
                        InputCommand = string.Empty;
                        RawDataLog += "\n";
                    }
                    else if (inputByte == '@')
                    {
                        RawDataLog += "Synchronus Idle\n";
                    }
                    else
                    {
                        InputCommand += (char)inputByte;
                    }
                }
            }
            else if (InputMode == 1)
            { // Save Data
            }
            else if (InputMode == 2)
            { // Save Other Data 
            }
            else
            {
                //something else
            }
        }

        protected void ProcessCommand(String inputstr)
        {
            Debug.WriteLine("Parsing " + inputstr);
            if (inputstr[0] == 0x10)
            {
                Debug.WriteLine("DLE");
                RawDataLog += "DEBUG: " + inputstr.Substring(1) + '\n';
            }

        }
        public List<CommandBinding> GetCommandBindings()
        {
            List<CommandBinding> outlst = new List<CommandBinding>();
            outlst.Add(new CommandBinding(CustomCommands.RefreshSerialNames, Refresh_Executed, Refresh_CanExecute));
            outlst.Add(new CommandBinding(CustomCommands.ConnectDisconnect, ConnectDisconnect_Executed, ConnectDisconnect_CanExecute));
            return outlst;
        }

        //CommandBindingEventHandlers for Refresh
        private void Refresh_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            //Todo
            e.CanExecute = true;
        }

        private void Refresh_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            this.RefreshSerialPorts();
            this.RefreshDrives();
            //ToDo
        }

        //CommandBindingEventHandlers for ConnectDisconnect
        private void ConnectDisconnect_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            //Todo
            e.CanExecute = true;
        }

        private void ConnectDisconnect_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            //Button btn = sender as Button;
            if (isConnected)
            {
                //btn.Content = new TextBlock() { Text = "Connect" };
                this.Disconnect();
            }
            else
            {
                //btn.Content = new TextBlock() { Text = "Disconnect" };
                this.Connect();
            }
            //ToDo
        }

        private ObservableCollection<RoutedUICommand> _SendCommands = new ObservableCollection<RoutedUICommand>() { CustomCommands.SendKitToSlotA, CustomCommands.SendKitToSlotB, CustomCommands.SendBank };
        public ReadOnlyObservableCollection<RoutedUICommand> SendCommands { get => new ReadOnlyObservableCollection<RoutedUICommand>(_SendCommands); }

        public void RefreshDrives()
        {
            _Drives.Clear();
            DriveInfo.GetDrives().ToList().ForEach((d) => _Drives.Add(d));
            NotifyPropertyChanged("Drives");
        }
        private ObservableCollection<DriveInfo> _Drives = new ObservableCollection<DriveInfo>();

        public MainVM()
        {
            BankVM = new PatternBankVM();
            BankVM.EditPattern += BankVM_EditPattern;
        }

        private void BankVM_EditPattern(object sender, PatternBank e)
        {
            CurrentBank = e;
            owner.patview.VM.bank = CurrentBank;
        }

        public ReadOnlyObservableCollection<DriveInfo> Drives
        {
            get => new ReadOnlyObservableCollection<DriveInfo>(_Drives);
        }



    }
}
