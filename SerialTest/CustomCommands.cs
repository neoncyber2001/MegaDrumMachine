using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace SerialTest
{
    public static class CustomCommands
    {

        ///ToDo: Custom Command Name
        public static readonly RoutedUICommand RefreshSerialNames = new RoutedUICommand("Refresh Serial Ports", "RefreshSerialNames", typeof(CustomCommands));
        public static readonly RoutedUICommand ConnectDisconnect = new RoutedUICommand("Connect / Disconnect", "ConnectDisconnect", typeof(CustomCommands));

        public static readonly RoutedUICommand SendKitToSlotA = new RoutedUICommand("Kit to Slot A", "SendKitToSlotA", typeof(CustomCommands));
        public static readonly RoutedUICommand SendKitToSlotB = new RoutedUICommand("Kit to Slot B", "SendKitToSlotB", typeof(CustomCommands));
        public static readonly RoutedUICommand SendBank = new RoutedUICommand("Send Bank", "SendBank", typeof(CustomCommands));
        public static readonly RoutedUICommand GetBank = new RoutedUICommand("Connect / Disconnect", "ConnectDisconnect", typeof(CustomCommands));

        /*public static readonly RoutedUICommand RefreshSerialNames = new RoutedUICommand("Refresh Serial Ports", "RefreshSerialNames", typeof(CustomCommands));
        public static readonly RoutedUICommand RefreshSerialNames = new RoutedUICommand("Refresh Serial Ports", "RefreshSerialNames", typeof(CustomCommands));
        public static readonly RoutedUICommand RefreshSerialNames = new RoutedUICommand("Refresh Serial Ports", "RefreshSerialNames", typeof(CustomCommands));
        public static readonly RoutedUICommand RefreshSerialNames = new RoutedUICommand("Refresh Serial Ports", "RefreshSerialNames", typeof(CustomCommands));
        */

        
    }
}
