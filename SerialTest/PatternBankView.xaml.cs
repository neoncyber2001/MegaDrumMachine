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
    /// Interaction logic for PatternBankView.xaml
    /// </summary>
    public partial class PatternBankView : UserControl
    {
        public PatternBankVM VM { get; set; } = new PatternBankVM();

        public PatternBankView()
        {
            InitializeComponent();
            VM.OwnerView = this;
            DataContext = VM;
            VM.GetBindings().ForEach((b) => this.CommandBindings.Add(b));
        }

        public PatternBank ActiveBank
        {
            get { return VM.SelectedPatternBank; }
            set { VM.SelectedPatternBank = value; }

        }

        public PatternBank SelectedPattern
        {
            get { return (PatternBank)GetValue(SelectedPatternProperty); }
            set { SetValue(SelectedPatternProperty, value); }
        }

        // Using a DependencyProperty as the backing store for MyPattern.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty SelectedPatternProperty =
            DependencyProperty.Register("SelectedPattern", typeof(PatternBank), typeof(PatternBankView), new PropertyMetadata(null));

    }
}
