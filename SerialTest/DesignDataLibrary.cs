using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SerialTest.Models;
namespace SerialTest
{
    public class DesignDataLibrary:LibraryVM
    {
        public DesignDataLibrary()
        {
            this._AudioSamples.Add(
                new AudioSample()
                {
                    FileName="File01.wav",
                    LocalPath="d:\\Audio\\File01.wav"
                }
            );
            this._AudioSamples.Add(
                new AudioSample()
                {
                    FileName = "File02.wav",
                    LocalPath = "d:\\Audio\\File02.wav"
                }
            );
            this._AudioSamples.Add(
                new AudioSample()
                {
                    FileName = "File03.wav",
                    LocalPath = "d:\\Audio\\File03.wav"
                }
            );
            this._AudioSamples.Add(
                new AudioSample()
                {
                    FileName = "File04.wav",
                    LocalPath = "d:\\Audio\\File04.wav"
                }
            );
            this._AudioSamples.Add(
                new AudioSample()
                {
                    FileName = "File05.wav",
                    LocalPath = "d:\\Audio\\File05.wav"
                }
            );
            this.NotifyPropertyChanged("AudioSamples");
        }
    }
}
