using DrumMachineDesktopApp.Models;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace DrumMachineDesktopApp
{

    public class PatternBankVM : INotifyPropertyChanged
    {

        private PatternBankView _OwnerView;

        public PatternBankView OwnerView
        {
            get => _OwnerView;
            set
            {
                _OwnerView = value;
                NotifyPropertyChanged();
            }
        }

        public PatternBankVM()
        {

        }
        private ObservableCollection<PatternBank> _PatternBanks = new ObservableCollection<PatternBank>();
        public ReadOnlyObservableCollection<PatternBank> PatternBanks
        {
            get => new ReadOnlyObservableCollection<PatternBank>(_PatternBanks);
        }
        public void Add_PatternBanks(PatternBank value)
        {
            _PatternBanks.Add(value);
            NotifyPropertyChanged("PatternBanks");
        }
        public void Remove_PatternBanks(PatternBank value)
        {
            _PatternBanks.Remove(value);
            NotifyPropertyChanged("PatternBanks");
        }
        private void NotifyPropertyChanged([CallerMemberName] String PropertyName = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(PropertyName));
        }
        public event PropertyChangedEventHandler PropertyChanged;

        public event EventHandler<PatternBank> EditPattern;

        private PatternBank _SelectedPatternBank;

        public PatternBank SelectedPatternBank
        {
            get => _SelectedPatternBank;
            set
            {
                _SelectedPatternBank = value;
                NotifyPropertyChanged();
            }
        }
        public List<CommandBinding> GetBindings()
        {
            List<CommandBinding> bindinglist = new List<CommandBinding>();
            bindinglist.Add(new CommandBinding(Commands.BankCommands.EditPatternBank, EditPatternBank_Executed, EditPatternBank_CanExecute));
            return bindinglist;
        }

        //CommandBindingEventHandlers for EditPatternBank
        private void EditPatternBank_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            //Todo
            if (e.Parameter == null)
            {
                e.CanExecute = false;
            }
            else
            {
                if (e.Parameter.GetType() == typeof(PatternBank))
                {
                    e.CanExecute = true;
                }
                else
                {

                    e.CanExecute = false;
                }
            }
        }

        private void EditPatternBank_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            //ToDo
            PatternBank bank = e.Parameter as PatternBank;
            OwnerView.SelectedPattern = bank;
            EditPattern?.Invoke(this, (PatternBank)e.Parameter);
        }
    }

}
