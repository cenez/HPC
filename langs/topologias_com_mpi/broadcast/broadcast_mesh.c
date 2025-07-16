#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

// #define SIZE 10

int main(int argc, char *argv[]) {
    int SIZE = atoi(argv[1]);
    MPI_Status status;
    MPI_Comm comm_2d;
    int rank, p;
    int dims[2], periods[2], coords[2];
    dims[0] = dims[1] = periods[0] = periods[1] = 0;
    int i;
    int *b;
    int *my_b = (int *) malloc(SIZE * sizeof(int));

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    // Start the vector that is broadcast.
    if (rank == 0){
        b = (int *) malloc(SIZE * sizeof(int));
        for (i = 0; i < SIZE; i++) b[i] = i;
    }

    // Create the mesh.
    MPI_Dims_create(p, 2, dims);
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &comm_2d);

    // Load the coordinates.
    MPI_Cart_coords(comm_2d, rank, 2, coords);

    // The first column will start the broadcast along the rows.
    double start = MPI_Wtime();
    int dim_0_succ, dim_0_pred, dim_1_succ, dim_1_pred;
    dim_0_succ = dim_0_pred = dim_1_succ = dim_1_pred = 0;
    MPI_Cart_shift(comm_2d, 0, 1, &dim_0_pred, &dim_0_succ);
    MPI_Cart_shift(comm_2d, 1, 1, &dim_1_pred, &dim_1_succ);

    if (coords[0] == 0 && coords[1] == 0) {
        MPI_Send(b, SIZE, MPI_INT, dim_0_succ, 0, MPI_COMM_WORLD);
        MPI_Send(b, SIZE, MPI_INT, dim_1_succ, 0, MPI_COMM_WORLD);
    }
   
    if (coords[1] == 0) {
        MPI_Recv(my_b, SIZE, MPI_INT, dim_0_pred, 0, MPI_COMM_WORLD, &status);
        MPI_Send(my_b, SIZE, MPI_INT, dim_0_succ, 0, MPI_COMM_WORLD);
        MPI_Send(my_b, SIZE, MPI_INT, dim_1_succ, 0, MPI_COMM_WORLD);
    } else {  
        MPI_Recv(my_b, SIZE, MPI_INT, dim_1_pred, 0, MPI_COMM_WORLD, &status);
        MPI_Send(my_b, SIZE, MPI_INT, dim_1_succ, 0, MPI_COMM_WORLD);
    }
    double end = MPI_Wtime();
 
    if (rank == 0) printf("%d %f\n", SIZE, end - start);
     
    MPI_Finalize();
}
