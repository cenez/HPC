#include "mpi.h"
#include <stdio.h>

int main (int argc, char *argv[]) {
   int rank, p, size = 8, tag = 0;
   int left, right;
   char send_buffer1[8], recv_buffer1[8];
   char send_buffer2[8], recv_buffer2[8];
   MPI_Status status;

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &p);
   left = (rank-1 + p) % p;
   right = (rank + 1) %p;

   sprintf(send_buffer1, "N:%d\n", rank);   
   sprintf(send_buffer2, "N:%d\n", rank);   

   MPI_Sendrecv(send_buffer1, size, MPI_CHAR, left, tag, recv_buffer1, size, MPI_CHAR, right, tag, MPI_COMM_WORLD, &status);
   MPI_Sendrecv(send_buffer2, size, MPI_CHAR, right, tag, recv_buffer2, size, MPI_CHAR, left, tag, MPI_COMM_WORLD, &status);

   printf("-------------------------\n");
   printf("Processo %s", send_buffer1);
   printf("Vizinho Direita %s", recv_buffer1);
   printf("Vizinho Esquerda %s", recv_buffer2);
   printf("-------------------------\n");

   MPI_Finalize();
   return 0;
}
