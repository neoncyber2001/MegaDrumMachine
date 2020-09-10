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
using DrumMachineDesktopApp.Models;
namespace DrumMachineDesktopApp
{
    /// <summary>
    /// Interaction logic for PatternView.xaml
    /// </summary>
    public partial class PatternView : UserControl
    {

        public PatternVM VM = new PatternVM();
        public PatternView()
        {
            InitializeComponent();
            DataContext = VM;
        }

       

        public PatternBank SetPattern
        {
            get { return (PatternBank)GetValue(SetPatternProperty); }
            set { 
                SetValue(SetPatternProperty, value);
                VM.bank = value;
            }
        }

        // Using a DependencyProperty as the backing store for SetPattern.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty SetPatternProperty =
            DependencyProperty.Register("SetPattern", typeof(PatternBank), typeof(PatternView), new PropertyMetadata(null));
        }
}
