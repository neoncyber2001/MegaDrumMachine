using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.CompilerServices;
using System.Timers;
using System.Collections.Concurrent;
using System.IO;

namespace SerialTest
{
    public static class RawDatalogger
    {
        public static void Initialize(bool timestamp)
        {
            isTimestamped = timestamp;
            isInitialized = true;
        }
        public static void Initialize(bool timestamp, string logPath, int logUpdateFreq = 1000)
        {
            isTimestamped = timestamp;
            isLogFileWritten = true;
            logFilePath = logFilePath;
            LogTimer.Elapsed += LogTimer_Elapsed;
            LogTimer.Interval = logUpdateFreq;
            LogTimer.Start();
            isInitialized = true;
        }

        private static void LogTimer_Elapsed(object sender, ElapsedEventArgs e)
        {
            LogWriteOut();
        }

        private static Timer LogTimer { get; set; }
        private static ConcurrentQueue<string> LogCue { get; set; } = new ConcurrentQueue<string>();
        public static string logFilePath { get; private set; } = string.Empty;
        public static bool isInitialized { get; private set; } = false;
        public static bool isLogFileWritten { get; private set; } = false;
        public static bool isTimestamped { get; set; } = false;
        public static EventHandler<string> DataRecieved;
        private static void ReportDataRecieved(string data, object sender)
        {
            DataRecieved?.Invoke(sender, data);
        }
        private static void LogWriteOut()
        {
            if (LogCue.Count > 0)
            {
                using (var logStream = File.Open(logFilePath,FileMode.Append))
                {
                    while (LogCue.Count > 0)
                    {
                        string entry;
                        if (LogCue.TryDequeue(out entry))
                        {
                            logStream.Write(Encoding.UTF8.GetBytes(entry),0,entry.Length);
                        }
                    }
                }
            }
        }
        public static void WriteEntry(string line, object sender)
        {
            String fullEntry = string.Empty;
            if (isTimestamped)
            {
                fullEntry = "[" + DateTime.Now.ToString() + "]: ";
            }
            fullEntry += line + Environment.NewLine;
            if (isLogFileWritten)
            {
                LogCue.Enqueue(fullEntry);
            }
            ReportDataRecieved(fullEntry, sender);
        }
    }
}
