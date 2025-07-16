using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace AulaMPI2 {
    public class Generator {
        /*         A   B   C    .....,   N
         * lc = [20, 8, 30, 10, ....., 6,  90]
         */

        public static uint[] Gen(String file, int N, int MIN, int MAX) {
            Random random = new Random();
            File.WriteAllText(file, "N " + N + System.Environment.NewLine);

            uint[] lc = new uint[N + 1];
            List<ulong[,]> ms = new List<ulong[,]>();

            for (int i = 0; i <= N; i++) {
                uint n = (uint)random.Next(MIN, MAX);
                lc[i] = n;
            }

            for (int k = 0; k < N; k++) {
                ulong[,] m = new ulong[lc[k], lc[k + 1]];
                ms.Add(m);
                string content = "DIM " + lc[k] + " " + lc[k + 1] + System.Environment.NewLine;
                for (int i = 0; i < lc[k]; i++) {
                    for (int j = 0; j < lc[k + 1]; j++) {
                        uint n = (uint)random.Next(0,2);//(MIN, MAX);
                        m[i, j] = n;
                        content += (n + (j + 1 == lc[k + 1] ? System.Environment.NewLine : " "));
                    }
                }
                File.AppendAllText(file, content);
                if (k % 100 == 0)
                    Console.WriteLine("Generator: " + k);
            }
            return lc;
        }

        public static List<ulong[][]> MatrixList(string file) {
            string[] lines = File.ReadAllLines(file);
            int N = Int32.Parse((lines[0].Split(' '))[1]);

            List<ulong[][]> ms = new List<ulong[][]>(N + 1);
            for (int k = 1; k < lines.Length; k++) {
                if (lines[k].Split(' ')[0].Equals("DIM")) {
                    int lin_size = Int32.Parse((lines[k].Split(' '))[1]);
                    int col_size = Int32.Parse((lines[k].Split(' '))[2]);
                    ulong[][] mm = new ulong[lin_size][];
                    for (int li = 0; li < mm.Length; li++)
                        mm[li] = new ulong[col_size];
                    ms.Add(mm);
                }
            }
            int mi = 0, l = 0, lk = 0;
            for (int k = 1; k < lines.Length; k++) {
                string s = lines[k].Split(' ')[0];
                if (!s.Equals("DIM") && !s.Equals("")) {
                    for (lk = k; lk < lines.Length; lk++) {
                        ulong[][] m = ms[mi];
                        string[] line = lines[lk].Split(' ');
                        string test = line[0].Trim();
                        if (test.Equals("DIM") || test.Equals("")) {
                            mi++;
                            l = 0;
                            break;
                        }
                        for (int j = 0; j < line.Length; j++)
                            m[l][j] = ulong.Parse(line[j]);
                        l++;
                    }
                    k = lk;
                }
            }
            return ms;
        }
    }
}
