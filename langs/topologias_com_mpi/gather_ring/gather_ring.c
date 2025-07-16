#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mpi.h"

#define BLOCKSIZE 1

int main (int argc, char *argv[]) {
	int i, my_rank, p, tag = 0, succ, pred ;
	int send_offset, recv_offset;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
	float *y;
	y = (float *) malloc(p*sizeof(float));
        for (i = 0; i < p; i++)	
            if (i == my_rank * BLOCKSIZE)
                y[i] = my_rank;
            else
		y[i] = 0;

	printf("Before Process %d :", my_rank);
	for (i = 0; i < p; i++) printf("%.2f ", y[i]);
	printf("\n");
        MPI_Barrier(MPI_COMM_WORLD);
       
	succ = (my_rank + 1) % p;
	pred = (my_rank - 1 + p) % p;

	for (i = 0; i < p - 1; i++){
		send_offset = ((my_rank - i + p) % p) * BLOCKSIZE;
		recv_offset = ((my_rank - i - 1 + p) % p) * BLOCKSIZE;
		
 		if (my_rank % 2 == 0) {
 			MPI_Send(y + send_offset, BLOCKSIZE, MPI_FLOAT, succ, 0, MPI_COMM_WORLD);
			MPI_Recv(y + recv_offset, BLOCKSIZE, MPI_FLOAT, pred, 0, MPI_COMM_WORLD, &status);
                } else {
			MPI_Recv(y + recv_offset, BLOCKSIZE, MPI_FLOAT, pred, 0, MPI_COMM_WORLD, &status);
			MPI_Send(y + send_offset, BLOCKSIZE, MPI_FLOAT, succ, 0, MPI_COMM_WORLD);
                }
	}

	printf("After Process %d :", my_rank);
	for (i = 0; i < p; i++) printf("%.2f ", y[i]);
	printf("\n");
        MPI_Barrier(MPI_COMM_WORLD);

	MPI_Finalize();
}
