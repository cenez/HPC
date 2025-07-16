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

	// Trocar entre si informações sobre o tamanho de cada bloco.
        for (i = 0; i < p - 1; i++) {
           send_offset = ((my_rank - i + p) % p);
           recv_offset = ((my_rank - i - 1 + p) % p);

           MPI_Send(blocksize + send_offset, 1, MPI_INT, succ, 0, MPI_COMM_WORLD);
           MPI_Recv(blocksize + recv_offset, 1, MPI_INT, pred, 0, MPI_COMM_WORLD, &status);
        }
        
        // printf("blocksize: Processo %d: ", my_rank);
        // for (i = 0; i < p; i++)
            // printf(" %d ", blocksize[i]);
        // printf("\n");
        // MPI_Barrier (MPI_COMM_WORLD);  

        // y irá guardar o total acumulado.
        int total_size = 0;
        for (i = 0; i < p ; i++) 
            total_size += blocksize[i];
        y = (float *) malloc(total_size * sizeof(float));  
        for (i = 0; i < total_size; i++) y[i] = 0;

        // my_start é onde, no vetor y, cada processo irá começar a colocar seus valores.
        int my_start = 0;
        for (i = 0; i < my_rank; i++) my_start += blocksize[i];
        for (i = my_start; i < blocksize[my_rank] + my_start; i++) y[i] = my_rank;
         
        // printf("y: Processo %d :", my_rank);
        // for (i = 0; i < total_size; i++) printf("%.2f ", y[i]);
        // printf("\n");  
        // MPI_Barrier (MPI_COMM_WORLD);  

	// Aqui ocorre o verdadeiro Gather. 
        for (i = 0; i < p - 1; i++) {
           int j;
           send_offset = recv_offset = 0;
           for (j = 0; j < ((my_rank - i + p) % p); j++) send_offset += blocksize[j];
           for (j = 0; j < ((my_rank - i - 1 + p) % p); j++) recv_offset += blocksize[j];

           MPI_Send(y + send_offset, blocksize[(my_rank - i + p) % p], MPI_FLOAT, succ, 0, MPI_COMM_WORLD);
           MPI_Recv(y + recv_offset, blocksize[(my_rank - i - 1 + p) % p], MPI_FLOAT, pred, 0, MPI_COMM_WORLD, &status);
        }
        
        // printf("y': Processo %d :", my_rank);
        // for (i = 0; i < total_size; i++) printf("%.2f ", y[i]);
        // printf("\n");  

	MPI_Finalize();
}
