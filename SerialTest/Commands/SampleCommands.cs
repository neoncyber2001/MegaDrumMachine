using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace SerialTest.Commands
{
    public static class SampleCommands
    {

        ///ToDo: Custom Command AddSamples
        public static readonly RoutedUICommand ImportSamples = new RoutedUICommand("Impoprt Samples", "ImportSamples", typeof(SampleCommands)); 
        public static readonly RoutedUICommand ImportDirectory = new RoutedUICommand("Impoprt Directory", "ImportDirectory", typeof(SampleCommands));
        public static readonly RoutedUICommand ScanSamples = new RoutedUICommand("Scan Sample Library", "ScanSamples", typeof(SampleCommands));
        public static readonly RoutedUICommand UpdateDrives = new RoutedUICommand("Update Removable Drives", "UpdateDrives", typeof(SampleCommands));
        public static readonly RoutedUICommand AuditionSample = new RoutedUICommand("Audition Audio Sample", "AuditionSample", typeof(SampleCommands));
        public static readonly RoutedUICommand SaveLibrary = new RoutedUICommand("Save Sample Library", "SaveLibrary", typeof(SampleCommands));
        public static readonly RoutedUICommand LoadLibrary = new RoutedUICommand("Load Sample Library", "LoadLibrary", typeof(SampleCommands));
        public static readonly RoutedUICommand ScanSDCard = new RoutedUICommand("Scan SD Card", "ScanSDCard", typeof(SampleCommands));
    }
}
