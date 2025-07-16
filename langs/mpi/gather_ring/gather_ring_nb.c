#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mpi.h"

#define SIZE 10
#define BLOCKSIZE 1

int main (int argc, char *argv[]) {
	int i, my_rank, p, tag = 0, succ, pred ;
	int send_offset, recv_offset;
	MPI_Status status;
	MPI_Request send_request, recv_request;
	float *y;
	y = (float *) malloc(SIZE*sizeof(float));

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
        for (i = 0; i < BLOCKSIZE; i++)	
		y[i + my_rank * BLOCKSIZE] = my_rank;

	printf("Before Process %d :", my_rank);
	for (i = 0; i < SIZE; i++) printf("%.2f ", y[i]);
	printf("\n");

	succ = (my_rank + 1) % p;
	pred = (my_rank - 1 + p) % p;

	send_offset = my_rank * BLOCKSIZE;
	recv_offset = ((my_rank -1 + p) % p) * BLOCKSIZE;

	for (i = 0; i < p - 1; i++){
		MPI_Isend(y + send_offset, BLOCKSIZE, MPI_FLOAT, succ, 0, MPI_COMM_WORLD, &send_request);
		MPI_Irecv(y + recv_offset, BLOCKSIZE, MPI_FLOAT, pred, 0, MPI_COMM_WORLD, &recv_request);

		send_offset = ((my_rank - i - 1 + p) % p) * BLOCKSIZE;
		recv_offset = ((my_rank - i - 2 + p) % p) * BLOCKSIZE;
		
		MPI_Wait(&send_request, &status);
		MPI_Wait(&recv_request, &status);
	}

	printf("After Process %d :", my_rank);
	for (i = 0; i < SIZE; i++) printf("%.2f ", y[i]);
	printf("\n");

	MPI_Finalize();
	free(y);
}
