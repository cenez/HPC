#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define M 10
#define N 10

void print_matrix(long int *A, int m, int n);
void print_vector(long int *b, int n);

int main(int argc, char *argv[]){
    int rank, size;
    long int i,j;
    long int *A, *local_A, *b, *c, *local_c;
    MPI_Init(&argc, &argv);	
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);	
    MPI_Comm_size(MPI_COMM_WORLD, &size);	

    b = (long int *) malloc(N * sizeof(long int));
    c = (long int *) malloc(N * sizeof(long int));
    
    // Process 0 creates the Matrix and the Vectors.
    if (rank == 0) {
        A = (long int *) malloc(M * N * sizeof(long int));
        for (i = 0; i < M * N; i++) A[i] = i;
        for (i = 0; i < N; i++) b[i] = i;
    }

    // Broadcast the Vector to everyone. 
    MPI_Bcast(b, N, MPI_LONG, 0, MPI_COMM_WORLD);

    // Scatter the Matrix.
    local_A = (long int *) malloc(M * (N / size) * sizeof(long int));
    for (i = 0; i < M; i++)
        MPI_Scatter(A + i * N, N / size, MPI_LONG, local_A + i * (N / size),  N / size, MPI_LONG, 0, MPI_COMM_WORLD);
 
    // Computes the local portion of c.
    local_c = (long int *) malloc(M * sizeof(long int));
    for(i = 0; i < M; i++) local_c[i] = 0;
    
    for(i = 0; i < M; i++)
        for(j = 0; j < N / size; j++)
            local_c[i] += local_A[i * (N / size) + j] * b[j + rank * (N / size)]; 

    // Reduce the final result on c.
    MPI_Reduce(local_c, c, M, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);  
  
    if (rank == 0 ) print_vector(c, M);
    MPI_Finalize();
}

void print_matrix(long int *A, int m, int n){
    long int i, j;
    printf("Matrix:\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++)
             printf("%.2ld ", A[i*n + j]);
        printf("\n");
    }
}

void print_vector(long int *b, int n){
    long int i;
    printf("Vector:\n");
    for (i = 0; i < n; i++)
        printf("%ld ", b[i]);
    printf("\n");
}


