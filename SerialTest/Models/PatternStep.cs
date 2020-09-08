using System;
using System.Collections;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SerialTest.Models
{
    [Serializable]
    public class PatternStep
    {
        public PatternStep()
        {            
            m_backing = new BitArray(8, false);
        }
        public PatternStep(byte binstep)
        {
            m_backing = new BitArray(binstep);
        }
        
        private BitArray m_backing;
        
        public bool Track1 { 
            get => m_backing[0]; 
            set { m_backing[0] = value; }
        }

        public bool Track2
        {
            get => m_backing[1];
            set { m_backing[1] = value; }
        }

        public bool Track3
        {
            get => m_backing[2];
            set { m_backing[2] = value; }
        }

        public bool Track4
        {
            get => m_backing[3];
            set { m_backing[3] = value; }
        }

        public bool Track5
        {
            get => m_backing[4];
            set { m_backing[4] = value; }
        }

        public bool Track6
        {
            get => m_backing[5];
            set { m_backing[5] = value; }
        }

        public bool Track7
        {
            get => m_backing[6];
            set { m_backing[6] = value; }
        }

        public bool Track8
        {
            get => m_backing[7];
            set { m_backing[7] = value; }
        }
        
        public byte ByteValue { 
            get =>Convert.ToByte(m_backing);
            set { m_backing = new BitArray(value); }
        }
    }
}
