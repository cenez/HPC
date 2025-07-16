#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#define VET_SIZE 100000000
#define ERR 1e-6
#define P 20

#ifdef _OPENMP
#define ID omp_get_thread_num()
#define SIZE omp_get_num_threads()
#else
ID = 0
SIZE = 1
#endif

void task(int n){
	long x = 0;
	for(int i = 0; i < n; i++)
		x = i+1;
	n = x;
}

void verify(float *out, float *a, float *b, int n) {
    #pragma omp parallel num_threads(P)
    {
    	int idx = ID;
    	int bdim = SIZE;
    	for(int i = idx; i < n; i += bdim){
        	assert(fabs(out[i] - a[i] - b[i]) < ERR);
    	}
    }
    printf("OK\n");
}

void vector_add(float *out, float *a, float *b, int n) {
    //float v = 0; #pragma omp simd reduction(+ : v)
    #pragma omp parallel num_threads(P)
    {
    	int idx = ID;
    	int bdim = SIZE;
    	//printf("id=%d, bdim=%d\n", idx, bdim);
    	for(int i = idx; i < n; i += bdim){
    		out[i] = a[i] + b[i];
		    task(n);
    	}
    }
}

void hello() {
    #pragma omp parallel num_threads(P)
    {
	int x = SIZE;
        printf("Thread %d de %d\n", ID, x);
    }
}

int main(int argc, char *argv[]){
    if(argc<2) return 0;
    long N = atol(argv[1]);
    float *a, *b, *out;

    a   = (float*)malloc(sizeof(float) * N);
    b   = (float*)malloc(sizeof(float) * N);
    out = (float*)malloc(sizeof(float) * N);

    for(int i = 0; i < N; i++){
        a[i] = i;
        b[i] = i;
    }
    //hello();
    vector_add(out, a, b, N);
    verify(out, a, b, N);

    free(a);
    free(b);
    free(out);
}
