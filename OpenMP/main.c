#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <math.h>
#define VET_SIZE 100000000

#ifdef _OPENMP
#define ID omp_get_thread_num()
#define SIZE omp_get_num_threads()
#else
ID = 0
SIZE = 1
#endif

void teste_for() {
    int i;
    #pragma omp parallel for private(i)
    for(i = 0; i < SIZE*2; i++){
        printf("ID: %d de %d\n", omp_get_thread_num(), SIZE);
    }
}

void tempo() {
    int i, nthreads;
    clock_t clock_timer;
    double wall_timer;
    double *x;
    x = (double*) malloc(VET_SIZE * sizeof(double));

    for(nthreads = 1; nthreads <= 8; ++nthreads){
        clock_timer = clock();
        wall_timer = omp_get_wtime();
        #pragma omp parallel for private(i) num_threads(nthreads)
        for(i = 0; i < VET_SIZE; i++){
            x[i] = sqrt(i*4 + i*2 + i);
        }
        printf("ID: %d\ttime on clock(): %f\ttime on wall: %f\n",
                 nthreads,
                 ((double) (clock() - clock_timer)) / ((double) CLOCKS_PER_SEC),
                 omp_get_wtime() - wall_timer
               );
    }
}

void hello2() {
    int id = ID;
    int nthreads;
    #pragma omp parallel private(nthreads, id)
    {
        printf("Sou o processo leve %d\n", ID);
        if(ID==0){
            nthreads = omp_get_num_threads();
            printf("Numero de Threads: %d\n", nthreads);
        }
    }
}

void hello() {
    #pragma omp parallel num_threads(8)
    {
        printf("Thread id = %d\n", ID);
    }
}

int main(){
    //hello();
    //hello2();
    teste_for();
    //tempo();
    return 0;
}
