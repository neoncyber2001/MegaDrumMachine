using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace DrumMachineDesktopApp.Commands
{
    public static class BankCommands
    {

        ///ToDo: Custom Command Name
        public static readonly RoutedUICommand EditPatternBank = new RoutedUICommand("EditPatternBank", "Edit Pattern Bank", typeof(BankCommands));

        public static readonly RoutedUICommand NewPatternBank = new RoutedUICommand("NewPatternBank", "New Pattern Bank", typeof(BankCommands));

    }
}
