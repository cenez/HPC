#include "mpi.h"
#include <stdio.h>

int main (int argc, char *argv[]) {
   int rank, p, size = 8, tag = 0;
   int left, right;
   char send_buffer1[8], recv_buffer1[8];
   char send_buffer2[8], recv_buffer2[8];
   MPI_Status status;
   MPI_Request send_request1, send_request2, recv_request1, recv_request2;

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &p);
   left = (rank-1 + p) % p;
   right = (rank + 1) %p;

   sprintf(send_buffer1, "N:%d\n", rank);   
   sprintf(send_buffer2, "N:%d\n", rank);   

   MPI_Isend(send_buffer1, size, MPI_CHAR, left, tag, MPI_COMM_WORLD, &send_request1);
   MPI_Irecv(recv_buffer1, size, MPI_CHAR, right, tag, MPI_COMM_WORLD, &recv_request1);
   
   MPI_Isend(send_buffer2, size, MPI_CHAR, right, tag, MPI_COMM_WORLD, &send_request2);
   MPI_Irecv(recv_buffer2, size, MPI_CHAR, left, tag, MPI_COMM_WORLD, &recv_request2);

   MPI_Wait(&send_request1, &status);
   MPI_Wait(&recv_request1, &status);
   MPI_Wait(&send_request2, &status);
   MPI_Wait(&recv_request2, &status);


   printf("-------------------------\n");
   printf("Processo %s", send_buffer1);
   printf("Vizinho Direita %s", recv_buffer1);
   printf("Vizinho Esquerda %s", recv_buffer2);
   printf("-------------------------\n");

   MPI_Finalize();
   return 0;
}
