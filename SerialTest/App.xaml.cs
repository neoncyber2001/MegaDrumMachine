using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace DrumMachineDesktopApp
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        private void Application_Startup(object sender, StartupEventArgs e)
        {
            //TESTING
            Debug.WriteLine("BEGIN TESTING OF FILE SCANNER");
            FileScanner fs = new FileScanner();
            string fssd = fs.LocateDrumDataSD();
            if (!String.IsNullOrEmpty(fssd))
            {
                Debug.WriteLine(fssd);
            }

            Debug.WriteLine("One of these days i'll write a real unit test.");
            //
            MainVM vm = new MainVM();
            vm.RefreshSerialPorts();
            MainWindow window = new MainWindow();
            vm.GetCommandBindings().ForEach((cb) => window.CommandBindings.Add(cb));
            window.DataContext = vm;
            vm.owner = (MainWindow)window;
            window.Show();
        }
    }
}
