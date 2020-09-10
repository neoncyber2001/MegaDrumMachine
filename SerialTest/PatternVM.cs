using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using SerialTest.Models;
namespace SerialTest
{

    public class PatternVM : INotifyPropertyChanged
    {
        private void NotifyPropertyChanged([CallerMemberName] String PropertyName = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(PropertyName));
        }
        public event PropertyChangedEventHandler PropertyChanged;


        private PatternBank _bank= new PatternBank();

        public PatternBank bank
        {
            get => _bank;
            set
            {
                _bank = value;
                NotifyPropertyChanged();

            }
        }


        public ReadOnlyObservableCollection<Pattern> AvailablePatterns
        {
            get => new ReadOnlyObservableCollection<Pattern>(new ObservableCollection<Pattern>(bank.patterns));
        }


        
        public Guid BankId
        {
            get => _bank.id;
        }


        private Pattern _CurrentPattern;

        public Pattern CurrentPattern
        {
            get => _CurrentPattern;
            set
            {
                _CurrentPattern = value;
                NotifyPropertyChanged();

                NotifyPropertyChanged("AvailablePatterns");

                NotifyPropertyChanged("NextPattern");

                NotifyPropertyChanged("Steps");

                NotifyPropertyChanged("BankId");
            }
        }

        public ReadOnlyObservableCollection<PatternStep> Steps
        {
            get => new ReadOnlyObservableCollection<PatternStep>(new ObservableCollection<PatternStep>(CurrentPattern.patternSteps));
        }

        public int PatternNo { get => _CurrentPattern.PatternNumber; }

        public int NextPattern {
            get
            {
                if (CurrentPattern != null)
                {
                    return _CurrentPattern.nextPattern;
                }
                else
                {
                    return -1;
                }
            }
            set
            {
                if (CurrentPattern != null)
                {
                    _CurrentPattern.nextPattern = value;
                    NotifyPropertyChanged();
                }
            }
        }

        

    }
}
