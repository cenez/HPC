#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#define ERR 1e-6

void task(int n){
	long x = 0;
	for(int i = 0; i < n; i++)
		x = i+1;
	n = x;
}

void verify(float *out, float *a, float *b, int n) {
    for(int i = 0; i < n; i++){
        assert(fabs(out[i] - a[i] - b[i]) < ERR);
    }
    printf("OK\n");
}

void vector_add(float *out, float *a, float *b, int n) {
    for(int i = 0; i < n; i++){
        out[i] = a[i] + b[i];
		task(n);
    }
}

int main(int argc, char *argv[]){
	if(argc<2) return 0;
	long N = atol(argv[1]);
	printf("############### Teste de desempenho para CPU(%ld)\n", N);

    float *a, *b, *out;

    a   = (float*)malloc(sizeof(float) * N);
    b   = (float*)malloc(sizeof(float) * N);
    out = (float*)malloc(sizeof(float) * N);

    for(int i = 0; i < N; i++){
        a[i] = i; b[i] = i;
    }

	clock_t start = clock();
    vector_add(out, a, b, N);
	clock_t end = clock();
	float seconds = (float)(end - start) / 10000000; // / CLOCKS_PER_SEC;
    printf("Time: %.5f seconds SERIAL. Verify: ", seconds);

    //vector_add(out, a, b, N);
	//out[0] = 1;
	verify(out, a, b, N);

	free(a);
    free(b);
    free(out);
}

