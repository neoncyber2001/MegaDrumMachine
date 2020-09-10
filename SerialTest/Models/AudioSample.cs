using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace DrumMachineDesktopApp.Models
{
    [Serializable]
    public class AudioSample
    {
        public int? SampleNumber { get; set; }
        public String FileName { get; set; }
        public String LocalPath { get; set; }
        public String Checksum { get; set; }
        public SampleTypes AudioType { get; set; }
        public long? size { get; set; }
        public int? depth { get; set; }
        public int? speed { get; set; }
        public int? channels { get; set; }
        public String NameOnCard { get; set; }
        public bool isScanned { get; set; } = false;
        public bool isOnCardInfoAvailable { get; set; } = false;
        public bool isTranscoded { get; set; } = false;
        public bool isTransfered { get; set; } = false;
        public bool isExcluded { get; set; } = false;
    }
}
