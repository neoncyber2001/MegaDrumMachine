using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SerialTest
{
    public class SampleVM:MainVM
    {
        SampleVM()
        {
            _SerialPortNames.Add("NONE");
            _SerialPortNames.Add("Com1");
        }
    }
}
