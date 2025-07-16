#include <stdio.h>
#include <stdlib.h>
#include <time.h>
long fib(long n){
	if (n==0) return 0;
	if (n==1) return 1;
	return fib(n-1)+fib(n-2);
}

int main(int argc, char **argv){
	long n = 10;
	if (argc==2){
		char *endptr;
		n = strtol(argv[1], &endptr, 10);
		if (endptr == argv[1]){ 
			printf("No conversion\n");
			exit(0);
			return 0;
		}
	}
	printf("**************************** C ****************************\n");
	clock_t begin = clock();
	printf("fib(%ld)=%ld\n", n, fib(n));
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time: %f.2 seconds\n", time_spent);
	return 0;
}
