#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

int main (int argc, char *argv[]) {
	int i, my_rank, p, tag = 0, succ, pred;
	int send_offset, recv_offset;
        float *y;
	MPI_Status status;
  
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
 
        succ = (my_rank + 1) % p;
	pred = (my_rank - 1 + p) % p;

        // blocksize é um vetor que para cada processo i indica quantos blocos o processo contribui. 
        int *blocksize = (int *) malloc(p * sizeof(int));
        blocksize[my_rank] = my_rank + 1;
        // printf("Processo %d tem blocksize de :%d\n", my_rank, blocksize[my_rank]);
        // MPI_Barrier (MPI_COMM_WORLD);       

	// blocks[i] apontar para um vetor com blocksize[i] posições float.
        float **blocks = (float **) malloc(p * sizeof(float *));
        blocks[my_rank] = (float *) malloc(blocksize[my_rank] * sizeof(float));
        for (i = 0; i < blocksize[my_rank]; i++) blocks[my_rank][i] = my_rank;

	// Aqui ocorre o verdadeiro Gather. 
        int max_size = 1000;
        float *numbers_in = (float *) malloc(max_size * sizeof(float));
        for (i = 0; i < p - 1; i++) {
           MPI_Send(blocks[(my_rank - i + p) % p], blocksize[(my_rank - i + p) % p], MPI_FLOAT, succ, 0, MPI_COMM_WORLD);
           MPI_Recv(numbers_in, max_size, MPI_FLOAT, pred, 0, MPI_COMM_WORLD, &status);
           int number_amount = 0;
           MPI_Get_count(&status, MPI_FLOAT, &number_amount);
           blocksize[(my_rank - i - 1 + p) % p] = number_amount;
           blocks[(my_rank - i - 1 + p) % p] = (float *) malloc(number_amount * sizeof(float));
           int j;
           for (j = 0; j < number_amount; j++) blocks[(my_rank - i - 1 + p) % p][j] = numbers_in[j];
        }
        
        int j;
        // printf("y: Processo %d :", my_rank);
        // for (i = 0; i < p; i++)
           // for (j = 0; j < blocksize[i]; j++) 
               // printf("%.2f ", blocks[i][j]);
        // printf("\n");  
        
	MPI_Finalize();
}
