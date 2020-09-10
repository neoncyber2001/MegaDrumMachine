using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace SerialTest.Commands
{
    public static class BankCommands
    {

        ///ToDo: Custom Command Name
        public static readonly RoutedUICommand EditPatternBank = new RoutedUICommand("EditPatternBank", "Edit Pattern Bank", typeof(BankCommands));

    }
}
