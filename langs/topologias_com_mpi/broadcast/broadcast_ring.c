#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

//#define SIZE 10

int main(int argc, char *argv[]){
    int SIZE = atoi(argv[1]);
    int rank, size;
    MPI_Status status;
    int i;
    int *my_b = (int *) malloc(SIZE * sizeof(int));
    int *b;


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int sr_count = 0;
    sr_count = size / 2;
    if (2 * sr_count < size)
        sr_count++;
    sr_count = sr_count - 1;

    double start = MPI_Wtime();

    if (rank == 0) {
        b = (int *) malloc(SIZE * sizeof(int));
        for (i = 0; i < SIZE; i++) my_b[i] = b[i] = i;
        MPI_Send(b, SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(b, SIZE, MPI_INT, size - 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        MPI_Recv(my_b, SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    } else if (rank == size - 1) {
        MPI_Recv(my_b, SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }
 
    for (i = 0 ; i < sr_count; i++) {
        if (rank == i + 1) 
            MPI_Send(my_b, SIZE, MPI_INT, i + 2, 0, MPI_COMM_WORLD);   
        else if (rank == i + 2)
            MPI_Recv(my_b, SIZE, MPI_INT, i + 1, 0, MPI_COMM_WORLD, &status);

        if (rank == size - (i + 1))
            MPI_Send(my_b, SIZE, MPI_INT, size - (i + 1) - 1, 0, MPI_COMM_WORLD);
        else if (rank == size - (i + 1) - 1)
            MPI_Recv(my_b, SIZE, MPI_INT, size - (i + 1), 0, MPI_COMM_WORLD, &status);
    }
    double end = MPI_Wtime();

    if (rank == 0) printf("%d %f\n", SIZE, end - start);

    MPI_Finalize();
}
