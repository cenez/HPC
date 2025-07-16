#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

/*
  The total number of processes is not a cousin number, and is divisible by 2, 3 or 5.
  The total number of processes is above 10.
  The maximum divisor of the number of processes between 2 and 5 is my x-dimension. The y-dimension is the division.
*/


int main (int argc, char *argv[]){
   int my_rank, p;
   int i;   
   MPI_Status status;
   MPI_Request send_request, recv_request;  
 
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
   MPI_Comm_size(MPI_COMM_WORLD, &p);

   int dims[2], periods[2];
   dims[0] = dims[1] = 0; 
   periods[0] = periods[1] = 1;
   MPI_Comm comm_2d;

   // Create 2d Torus.
   MPI_Dims_create(p, 2, dims);
   if (my_rank == 0) {  
      printf("Grid %d %d\n", dims[0], dims[1]);
   }
   MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &comm_2d);

   // Load the coordinates on coords.
   int coords[2];
   MPI_Cart_coords(comm_2d, my_rank, 2, coords);

   // Discover the neighbors on each dimension. 			
   int dimension_0_succ, dimension_0_pred, dimension_1_succ, dimension_1_pred;
   dimension_0_succ = dimension_0_pred = dimension_1_succ = dimension_0_pred = 0;
   MPI_Cart_shift(comm_2d, 0, 1, &dimension_0_pred, &dimension_0_succ);
   MPI_Cart_shift(comm_2d, 1, 1, &dimension_1_pred, &dimension_1_succ);

   printf("Process:%d Coordinates:(%d,%d) Dim0Pred:%d Dim0Succ:%d Dim1Pred:%d Dim1Succ:%d.\n", my_rank, coords[0], coords[1], dimension_0_pred, dimension_0_succ, dimension_1_pred, dimension_1_succ);
   MPI_Barrier(MPI_COMM_WORLD); 

   // y vector contains the received data.
   float *y;
   y = (float *) malloc(p*sizeof(float));
   for (i = 0; i < p; i++)
      if (i == my_rank)
         y[i] = my_rank;
      else
         y[i] = 0;
   printf("Before Process %d :", my_rank);
   for (i = 0; i < p; i++) printf("%.2f ", y[i]);
   printf("\n");
   MPI_Barrier(MPI_COMM_WORLD);

   // Exchange Data
 
   // X-dimension
   int start = (my_rank / dims[1])*dims[1];
   int my_new_rank = my_rank - start;
   int send_offset, recv_offset;
   send_offset = ((my_new_rank + dims[1]) % dims[1]) + start;
   recv_offset = ((my_new_rank - 1 + dims[1]) % dims[1]) + start;
 
   for (i = 1 ; i < dims[1] ; i++) {
      MPI_Isend(y + send_offset, 1, MPI_FLOAT, dimension_1_succ, 0, MPI_COMM_WORLD, &send_request);
      MPI_Irecv(y + recv_offset, 1, MPI_FLOAT, dimension_1_pred, 0, MPI_COMM_WORLD, &recv_request);
     
      send_offset = ((my_new_rank - i + dims[1]) % dims[1]) + start;
      recv_offset = ((my_new_rank - i - 1 + dims[1]) % dims[1]) + start;
   
      MPI_Wait(&send_request, &status);
      MPI_Wait(&recv_request, &status);
   }

   // Y-dimension
   send_offset = my_rank; 
   if (send_offset < 0) send_offset = send_offset + p;
   send_offset = (send_offset / dims[1]) * dims[1];

   recv_offset = my_rank - dims[1];
   if (recv_offset < 0) recv_offset = recv_offset + p;
   recv_offset = (recv_offset / dims[1]) * dims[1];

   for (i = 0; i < dims[0] ; i++) {
      MPI_Isend(y + send_offset, dims[1], MPI_FLOAT, dimension_0_succ, 0, MPI_COMM_WORLD, &send_request);
      MPI_Irecv(y + recv_offset, dims[1], MPI_FLOAT, dimension_0_pred, 0, MPI_COMM_WORLD, &recv_request);
  
      send_offset = my_rank - i * dims[1]; 
      if (send_offset < 0) send_offset = send_offset + p;
      send_offset = (send_offset / dims[1]) * dims[1];
      recv_offset = my_rank - (i + 1) * dims[1];
      if (recv_offset < 0) recv_offset = recv_offset + p;
      recv_offset = (recv_offset / dims[1]) * dims[1];

      MPI_Wait(&send_request, &status);
      MPI_Wait(&recv_request, &status);
   }
   
   printf("After Process %d :", my_rank);
   for (i = 0; i < p; i++) printf("%.2f ", y[i]);
   printf("\n");
   MPI_Barrier(MPI_COMM_WORLD);

   MPI_Finalize();
}
