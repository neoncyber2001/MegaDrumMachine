using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Reflection;
namespace DrumMachineDesktopApp
{
    /// <summary>
    /// Interaction logic for SampleLibrary.xaml
    /// </summary>
    public partial class SampleLibrary : UserControl
    {
        public SampleLibrary()
        {
            InitializeComponent();
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
            if(DataContext!=null && DataContext.GetType() == typeof(LibraryVM))
            {
                Commands.SampleCommands.UpdateDrives.Execute(null, this);
                LibraryVM vm = DataContext as LibraryVM;
                vm.getCommandBindings().ForEach((cb) => this.CommandBindings.Add(cb));
                Commands.SampleCommands.LoadLibrary.Execute(null, this);
            }
        }

        private void UserControl_Unloaded(object sender, RoutedEventArgs e)
        {
            Commands.SampleCommands.LoadLibrary.Execute(null, this);
        }
    }
}
