#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <cuda.h>
#include <cuda_runtime.h>

#define ERR 1e-6

void verify(float *out, float *a, float *b, int n) {
    for(int i = 0; i < n; i++){
        assert(fabs(out[i] - a[i] - b[i]) < ERR);
    }
    printf("OK\n");
}
__device__ void task(int n){
	long x = 0;
	for(int i = 0; i < n; i++)
		x = i+1;
	n = x;
}

__global__ void vector_add(float *out, float *a, float *b, int n) {
	int idx = threadIdx.x;
	int bdim = blockDim.x; 
	//printf("id=%d, bdim=%d\n", idx, bdim);

    for(int i = idx; i < n; i += bdim){
        out[i] = a[i] + b[i];
		task(n);
    }
}

int main(int argc, char *argv[]){
	if(argc<2) return 0;
	long N = atol(argv[1]);
	printf("############### Teste de desempenho para GPU(%ld)\n", N);

    float *a, *b, *out; float *d_a, *d_b, *d_out;
    
	a   = (float*)malloc(sizeof(float) * N);
    b   = (float*)malloc(sizeof(float) * N);
    out = (float*)malloc(sizeof(float) * N);
    
	for(int i = 0; i < N; i++){ a[i] = i; b[i] = i; }
	
	clock_t start = clock();

	cudaMalloc((void**)&d_a, sizeof(float) * N);
    cudaMalloc((void**)&d_b, sizeof(float) * N);
    cudaMalloc((void**)&d_out, sizeof(float) * N);

    cudaMemcpy(d_a, a, sizeof(float) * N, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, sizeof(float) * N, cudaMemcpyHostToDevice);
	
	vector_add<<<1,256>>>(d_out, d_a, d_b, N);
	cudaMemcpy(out, d_out, sizeof(float) * N, cudaMemcpyDeviceToHost);
	
	cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_out);

	clock_t end = clock();
	float seconds = (float)(end - start) / 10000000; // / CLOCKS_PER_SEC;
    printf("Time: %.5f seconds CUDA. Verify: ", seconds);

	verify(out, a, b, N);
	
	free(a);
    free(b);
    free(out);
}

