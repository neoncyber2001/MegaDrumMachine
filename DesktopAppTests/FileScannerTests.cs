using System;
using DrumMachineDesktopApp;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.IO;
using System.Linq;
using System.Collections.Generic;
using Microsoft.Win32;
using System.Runtime.CompilerServices;
using DrumMachineDesktopApp.Models;
using System.Threading.Tasks;
using System.Security.Cryptography.X509Certificates;
using System.Threading;
using System.Diagnostics;

namespace DesktopAppTests
{
    [TestClass]
    public class FileScannerTests
    {
        protected FileScanner scanner { get; set; }
        protected FileConverter converter{ get; set; }
        const string expectedDrive = @"E:\";
        const string drumFile=@".drumdata.dat";
        const string sampleFile =@".sampleata.dat";
        const string sampleDirectory = @"D:\MusicComposition\Samples\Drums";
        const int totalSamples = 1062;

        public List<AudioSample> SampleList;

        [TestInitialize]
        public void TestInit()
        {
            converter = new FileConverter();
            scanner = new FileScanner();
            if (!File.Exists(expectedDrive + drumFile))
            {
                FileStream FS = File.Create(expectedDrive + drumFile);
                FS.WriteByte(0x10);
                FS.Close();
            }
            if (!File.Exists(expectedDrive + sampleFile))
            {
                FileStream FS = File.Create(expectedDrive + sampleFile);
                FS.WriteByte(0x10);
                FS.Close();
            }
             
        }

        [TestMethod]
        public void LocateMachineSDCard()
        {
            String DrumMachineSDResult = scanner.LocateDrumDataSD();
            Assert.IsFalse(String.IsNullOrEmpty(DrumMachineSDResult));
            Assert.IsTrue(String.Equals(DrumMachineSDResult, expectedDrive));
        }

        [TestMethod]
        public void LocateSampleSDCard()
        {
            String SampleSDResult = scanner.LocateSampleDataSD();
            Assert.IsFalse(String.IsNullOrEmpty(SampleSDResult));
            Assert.IsTrue(String.Equals(SampleSDResult, expectedDrive));
        }

        [TestMethod]
        public async Task ReadScanDirectory()
        {
            SampleList = await scanner.ScanDirectoryForSamples(sampleDirectory, true);
            Assert.AreEqual(totalSamples, SampleList.Count);
            SampleList.ForEach((aud) => Assert.IsTrue(File.Exists(aud.LocalPath)));
            
        }

        [TestMethod]
        public async Task ConversionTest()
        {
            if (SampleList == null)
            {
                await ReadScanDirectory();
            }
            Assert.IsFalse(converter.isRunning);
            converter.BatchConvertBackground(SampleList);
            Assert.IsTrue(converter.isRunning);
            Assert.IsFalse(String.IsNullOrEmpty(converter.Status));
            while (converter.isRunning)
            {
                Thread.Sleep(100);
                Debug.WriteLine(converter.Status);
                Debug.WriteLine(converter.Progress);
            }
            Assert.IsNotNull(converter.Result);
            Assert.IsTrue(converter.Result.Count > 0);
            Assert.AreNotEqual(SampleList, converter.Result);
            converter.Result.ForEach((smp) => Assert.IsTrue(File.Exists(smp.LocalPath)));
        }
    }
}
