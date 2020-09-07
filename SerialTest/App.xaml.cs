using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace SerialTest
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        private void Application_Startup(object sender, StartupEventArgs e)
        {
            MainVM vm = new MainVM();
            vm.RefreshSerialPorts();
            Window window = new MainWindow();
            vm.GetCommandBindings().ForEach((cb) => window.CommandBindings.Add(cb));
            window.DataContext = vm;
            window.Show();
        }
    }
}
