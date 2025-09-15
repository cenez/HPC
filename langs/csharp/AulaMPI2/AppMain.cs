using System;
using System.Collections;
using System.Collections.Generic;
using System.Reflection.Emit;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Reflection;

namespace AulaMPI2 {
    public class AppMain {
        // Gerador de matriz:
        public static readonly int N = 16; // Nro de matrizes para multiplicar
        public static int MIN = 5;
        public static int MAX = 10;
        public static string file = "matrix" + N + ".txt";

        public static void Main(string[] args) {
            Console.WriteLine("IP: " + GetLocalIPAddress());
            MPIEnv.mpi_start();
            if (MPIEnv.Rank == 0){
                //Serial_GenerateMatrixFile();
            }
            MPIEnv.WaitBarrier();
            RunMPI_Tests();
            MPIEnv.mpi_stop();
        }
        public static string GetLocalIPAddress() {
            var host = Dns.GetHostEntry(Dns.GetHostName());
            foreach (var ip in host.AddressList) {
                if (ip.AddressFamily == AddressFamily.InterNetwork) {
                    return ip.ToString();
                }
            }
            throw new Exception("No network adapters with an IPv4 address in the system!");
        }
        public static void RunMPI_Tests(){
            test1();
            //test2();
        }
        public static void test2() {
            List<object> lista = new List<object>();
            Splitter splitter = new Splitter();
            List<ulong[][]> ms = Generator.MatrixList(file);


            if (MPIEnv.Rank == MPIEnv.Root) {
                for (int i = 0; i < ms.Count; i++)
                    lista.Add(ms[i]);
            }
            List<object> bloco = splitter.Splitting(lista);
            if (bloco != null) {
                Console.WriteLine("Rank" + MPIEnv.Rank + ":\n" + printMatrix(bloco));
            }
        }
        public static string printMatrix(List<object> lista) {
            string s = "";
            foreach (object o in lista) {
                ulong[][] ms = (ulong[][])o;
                s += ms.Length + " x " + ms[0].Length + "\n";
                foreach (var a in ms) {
                    foreach (var b in a) {
                        s = s + b + " ";
                    }
                    s = s + "\n";
                }
            }
            return s;
        }
        /* // Aula anterior
        */
        public static void test1() {
            //MPIEnv.reduce();
            //MPIEnv.allReduce();
            //MPIEnv.immediateSendReceive();
            //MPIEnv.broadcast(10);
            //MPIEnv.scatter();
            //MPIEnv.allGather();
            MPIEnv.allToAll();
        }
        public static void Serial_GenerateMatrixFile(){
            var lc = Generator.Gen(file, N, MIN, MAX);
        }
    }
}
