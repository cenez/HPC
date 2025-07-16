#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define M 10
#define N 10

void print_matrix(int *A, int m, int n);
void print_vector(long int *b, int n);

int main(int argc, char *argv[]){
    int rank, size;
    long int i,j;
    long int *A, *local_A, *b, *c, *local_c;
    MPI_Init(&argc, &argv);	
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);	
    MPI_Comm_size(MPI_COMM_WORLD, &size);	

    b = (long int *) malloc(N * sizeof(long int));
    c = (long int *) malloc(M * sizeof(long int));
    
    // Process 0 creates the Matrix and the Vectors.
    if (rank == 0) {
        A = (long int *) malloc(M * N * sizeof(long int));
        for (i = 0; i < M * N; i++) A[i] = i;
        for (i = 0; i < N; i++) b[i] = i;

        // print_matrix(A, M, N);
        // print_vector(b, N);
    }

    // Broadcast the Vector to everyone. 
    MPI_Bcast(b, N, MPI_LONG, 0, MPI_COMM_WORLD);
    // printf("Process %d.\n", rank);
    // print_vector(b, N);     

    // Scatter the Matrix.
    local_A = (long int *) malloc(((M * N) / size) * sizeof(long int));
    MPI_Scatter(A, (M * N) / size, MPI_LONG, local_A, (M * N) / size, MPI_LONG, 0, MPI_COMM_WORLD);
 
    // printf("Process %d:\n", rank);
    // print_matrix(local_A, M / size, N);
    // MPI_Barrier(MPI_COMM_WORLD);

    // Computes the local portion of c.
    local_c = (long int *) malloc((M / size) * sizeof(long int));
    for(i = 0; i < M / size; i++) local_c[i] = 0;
    
    for(i = 0; i < M / size; i++)
        for(j = 0; j < N; j++)
            local_c[i] += local_A[i * N + j] * b[j]; 

    // Multi-broadcast the final result to everyone.
    MPI_Allgather(local_c, M / size, MPI_LONG, c, M / size, MPI_LONG, MPI_COMM_WORLD);
    
    print_vector(c, M);
    MPI_Finalize();
}

void print_matrix(int *A, int m, int n){
    int i, j;
    printf("Matrix:\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++)
             printf("%.2d ", A[i*n + j]);
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


