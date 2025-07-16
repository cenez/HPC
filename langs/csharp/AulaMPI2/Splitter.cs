using System;
using System.Collections.Generic;
using System.Text;
using MPI;

namespace AulaMPI2 {
    public class Splitter {
        public List<object> Splitting(List<object> lista) {
            int num_nodes = MPIEnv.Size;
            int len_partition = lista.Count / num_nodes;
            RequestList bag = new RequestList();
            if (MPIEnv.Rank == MPIEnv.Root) { // Quem entra aqui é o nó gerente!!!
                if (lista.Count == 0 || (lista.Count % num_nodes != 0)) {
                    string msn = "Lista vazia, ou lista.Count nao é divisível perfeitamente por N processos!!!";
                    Console.WriteLine(msn);
                    throw new Exception(msn);
                }

                List<object> tmp = new List<object>(len_partition + 2);
                tmp.Add(lista[0]);

                int id_processo = 0;
                for (int i = 1; i <= lista.Count; i++) {

                    Console.WriteLine("i%len_partition: " + i % len_partition);
                    if (i % len_partition != 0) {
                        tmp.Add(lista[i]);
                    }
                    else {
                        int dest = id_processo++;
                        Console.WriteLine("Send to rank " + dest);
                        bag.Add(MPIEnv.Comm_world.ImmediateSend<object>(tmp, dest, TAGs.DIST_GERAL));
                        tmp = new List<object>(len_partition + 2);
                        if (i == lista.Count) break;
                        tmp.Add(lista[i]);
                    }
                }
            }

            object r = MPIEnv.Comm_world.Receive<object>(MPIEnv.Root, TAGs.DIST_GERAL);
            bag.WaitAll();
            return (List<object>)r;
        }
    }
}
