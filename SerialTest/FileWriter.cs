using DrumMachineDesktopApp.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.ComponentModel;
using System.Runtime.Remoting.Messaging;

namespace DrumMachineDesktopApp
{
    public class FileWriter
    {
        public FileWriter()
        {

        }
        public async void WriteBankFileAsync(String FilePath, PatternBank Bank)
        {
            String Header = Properties.Settings.Default.BankFileHeader;
            String Verstr = Properties.Settings.Default.VersionString;
            Task tsk = new Task(() =>
            {
                if (File.Exists(FilePath))
                {
                    File.Delete(FilePath);
                }
                FileStream fs = File.OpenWrite(FilePath);
                fs.Write(Encoding.ASCII.GetBytes(Header), 0, 16);
                fs.Write(Encoding.ASCII.GetBytes(Verstr), 0, 16);
                for (int i = 0; i < 16; i++)
                {
                    fs.WriteByte(0x00);
                }
                for(int i=0; i<16; i++)
                {
                    foreach(PatternStep p in Bank.patterns[i].patternSteps)
                    {
                        fs.WriteByte(p.ByteValue);
                    }
                    fs.WriteByte(Convert.ToByte(Bank.patterns[i].nextPattern));
                }
                fs.Close();
            });
            await tsk;
        }
    }
}
