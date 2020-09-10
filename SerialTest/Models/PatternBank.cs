using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SerialTest.Models
{
    [Serializable]
    public class PatternBank
    {
        [NonSerialized]
        private bool isSelected1;

        public PatternBank()
        {
            for (int i = 0; i < 16; i++)
            {
                patterns.Add(new Pattern() { PatternNumber=i, nextPattern = i });
            }
            id = Guid.NewGuid();
        }

        public PatternBank(List<Pattern> pats, Guid ident)
        {
            if (pats?.Count == 16)
            {
                patterns = pats;
            }
            else
            {
                throw new ArgumentException("pats is either null or incomplete");
            }
            id = ident;
        }
        public Guid id { get; set; }
        public List<Pattern> patterns { get; set; } = new List<Pattern>(16);
        public String name { get; set; } = string.Empty;
        public bool isSelected { get => isSelected1; set => isSelected1 = value; }
    }
}
