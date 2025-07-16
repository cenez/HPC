using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace AulaMPI2 {
    public class Tempo {
        private static Stopwatch time = new Stopwatch();

        public static void start() {
            time.Start();
        }
        public static void stop() {
            time.Stop();
        }
        public static string Time() {
            return $"Tempo de execucao: {time.ElapsedMilliseconds} ms";
        }
    }
}
