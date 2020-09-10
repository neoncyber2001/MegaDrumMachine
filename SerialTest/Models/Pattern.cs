using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DrumMachineDesktopApp.Models
{
    [Serializable]
    public class Pattern
    {
        private int patternNumber;

        public int PatternNumber { get => patternNumber; set => patternNumber = value; }
        public Pattern()
        {
            patternSteps = new List<PatternStep>(16);
            for (int i = 0; i < 16; i++)
            {
                patternSteps.Add(new PatternStep());
            }
        }
        public Pattern(List<PatternStep> steps, int next)
        {
            if (steps?.Count == 16)
            {
                patternSteps = steps;
            }
            else
            {
                throw new ArgumentException("steps is either null or incomplete");
            }
            nextPattern = next;
        }
        public List<PatternStep> patternSteps { get; set; }

        public int nextPattern { get; set; }
    }
}
