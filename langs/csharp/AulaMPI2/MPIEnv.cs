using System;
using System.Collections.Generic;
using System.Text;
using MPI;

namespace AulaMPI2 {
    public class MPIEnv {
        public static MPI.Environment Mpi { get; set; }
        public static Intracommunicator Comm_world { get; set; }
        public static int Root { get { return 0; } } // Gerente distribui e ajuda os trabalhadores
        public static int Rank { get; set; }
        public static int Size { get; set; }

        public static void mpi_start() {
            string[] args = System.Environment.GetCommandLineArgs();
            Mpi = new MPI.Environment(ref args);
            Comm_world = Communicator.world;

            Rank = Comm_world.Rank;
            Size = Comm_world.Size;
        }
        public static void mpi_stop() { Mpi.Dispose(); }

        public static void reduce() {
            Console.WriteLine("Meu id é: " + Rank + " size: " + Size);

            int valor = Rank + 1;
            valor = Comm_world.Reduce<int>(valor, Operation<int>.Add, Root);
            if (Rank == Root) {
                Console.WriteLine("Eu sou o node " + Rank + "!!! O valor é: " + valor);
            }
            Comm_world.Barrier(); // Tarefas vao aguardar aqui
        }

        public static void allReduce() {
            int n = 10;
            var data = new ulong[n];
            Random r = new Random();
            for (int i = 0; i < n; i++) {
                data[i] = (ulong)r.Next(1, 1000);
            }

            var resultado = new ulong[n];
            Comm_world.Allreduce<ulong>(data, Operation<ulong>.Min, ref resultado);

            if (Rank == Root) {
                foreach (var d in resultado)
                    Console.Write(d + " ");
            }
            Comm_world.Barrier();
        }
        public static void immediateSendReceive() {
            int tag = 0;
            Request[] requests = new Request[2];
            RequestList bag_requests = new RequestList();

            int dest = (Rank + 1) == Size ? 0 : Rank + 1;
            int source = (Rank - 1) < 0 ? Size - 1 : Rank - 1;

            ulong[] matriz = { (ulong)Rank, (ulong)Rank, (ulong)Rank, (ulong)Rank };

            var tmp = new ulong[matriz.Length];
            requests[0] = Comm_world.ImmediateSend<ulong>(matriz, dest, tag);
            requests[1] = Comm_world.ImmediateReceive<ulong>(source, tag, tmp);

            foreach (Request r in requests)
                bag_requests.Add(r);

            bag_requests.WaitAll();

            string s = "\nnode" + Rank + "recebeu: " + " ";
            foreach (var a in tmp)
                s = s + a + " ";

            s = s + "\nnode" + Rank + " enviou: ";
            foreach (var a in matriz)
                s = s + a + " ";

            s = s + "\n";
            Console.WriteLine(s);

        }
        public static void broadcast(int n) {
            double[] valores = new double[n];// ROOT={0, 10, 20, 30, 40}, demais={0,0,0,0,0}
            if (MPIEnv.Rank == MPIEnv.Root) {
                for (int i = 0; i < valores.Length; i++)
                    valores[i] = i * 10;
            }
            MPIEnv.Comm_world.Broadcast<double[]>(ref valores, MPIEnv.Root);
            MPIEnv.Comm_world.Barrier();

            string s = "node" + MPIEnv.Rank + " ";
            for (int i = 0; i < valores.Length; i++)
                s += valores[i] + " ";
            Console.WriteLine(s);

        }
        public static void scatter() {
            int[] values = new int[MPIEnv.Size]; // {0, 0, 0, 0}
            if (MPIEnv.Rank == MPIEnv.Root) {
                for (int i = 0; i < values.Length; i++) {
                    values[i] = (i + 1) * 10; // {10,20,30,40}
                }
            }
            int valor = MPIEnv.Comm_world.Scatter<int>(values, MPIEnv.Root);
            MPIEnv.Comm_world.Barrier();

            string s = "scatter: node " + MPIEnv.Rank + " -> ";
            for (int i = 0; i < values.Length; i++)
                s += values[i] + " ";
            Console.WriteLine(s + " valor: " + valor);

        }

        public static void allGather() {
            int[] vals = new int[MPIEnv.Size];
            MPIEnv.Comm_world.Allgather<int>(MPIEnv.Rank, ref vals); // 0, 10, 20, 30, para 4 nodes
            MPIEnv.Comm_world.Barrier();

            string s = "allGather: node " + MPIEnv.Rank + " -> ";

            for (int i = 0; i < vals.Length; i++)
                s = s + vals[i] + " ";

            Console.WriteLine(s);
        }
        public static void allToAll() {
            int[] values = new int[MPIEnv.Size];
            for (int i = 0; i < values.Length; i++)
                values[i] = MPIEnv.Rank; // 0,0,0,0 -> 1,1,1,1 -> 2,2,2,2 -> 3,3,3,3

            int[] new_vals = MPIEnv.Comm_world.Alltoall<int>(values);
            MPIEnv.Comm_world.Barrier();

            string s = "allToal: node " + MPIEnv.Rank + " -> ";
            for (int i = 0; i < new_vals.Length; i++)
                s = s + values[i] + ":" + new_vals[i] + " ";// antes:depois

            Console.WriteLine(s);
        }
        public static void WaitBarrier(){
            MPIEnv.Comm_world.Barrier();
        }
    }
}
