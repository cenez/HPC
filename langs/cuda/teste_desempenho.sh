#!/bin/bash
N="$1"

if [ -z "$1" ]; then
        echo "Insert the integer arg: "
	echo "./teste_desempenho.sh 100000"
else
	#echo "############### Teste de desempenho para GPU($N)"
	nvcc vector_add_threads.cu -o gpu ; ./gpu $N ; rm gpu
	
	#echo "############### Teste de desempenho para CPU($N)"
	gcc vector_add.c -o cpu ; ./cpu $N ; rm cpu

	#echo "############### Teste de desempenho para OpenMP($N)"
	gcc -o omp -fopenmp vector_add_omp.c ; ./omp $N ; rm omp
fi

