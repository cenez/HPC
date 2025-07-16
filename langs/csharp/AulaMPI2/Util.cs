using System;
using System.Collections.Generic;
using System.Text;

namespace AulaMPI2 {
    public class Util {
        public static ulong[][] multiply(ulong[][] A, ulong[][] B) {
            int a_rows = A.GetLength(0); // Linha A
            int b_cols = B.GetLength(1); // Coluna B
            int n = A.GetLength(1);// Coluna A, Linha B

            if (n != B.GetLength(0)) // Linha B!=n ?
                throw new Exception("A.columns != B.rows");

            ulong[][] C = new ulong[a_rows][];//, b_cols];
            for (int k = 0; k < a_rows; k++)
                C[k] = new ulong[b_cols];

            for (int i = 0; i < a_rows; i++) {
                for (int j = 0; j < b_cols; j++) {
                    for (int k = 0; k < n; k++) {
                        C[i][j] = C[i][j] + A[i][k] * B[k][j];
                    }
                }
            }
            return C;
        }

        public static void printMatriz(ulong[][] m) {
            Console.WriteLine("**************** " + m.Length + " x " + m[0].Length + " ****************");
            ulong maior = 0;
            for (int i = 0; i < m.Length; i++) {
                for (int j = 0; j < m[0].Length; j++) {
                    if (m[i][j] > maior)
                        maior = m[i][j];
                }
            }
            for (int i = 0; i < m.Length; i++) {
                Console.Write(" ");
                for (int j = 0; j < m[0].Length; j++) {
                    Console.Write(leftZero(m[i][j], maior) + " ");
                }
                Console.WriteLine("");
            }
        }
        public static string leftZero(ulong n, ulong len) {
            string s = "" + n;
            while ((len + "").Length > s.Length)
                s = "0" + s;
            return s;
        }
    }
}
