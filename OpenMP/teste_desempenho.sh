#!/bin/bash
N="$1"

if [ -z "$1" ]; then
        echo "Insert the integer arg: "
	echo "./teste_desempenho.sh 100000"
else
	echo "Teste de desempenho para OpenMP($N)"
	gcc -o omp -fopenmp vector_add_omp.c ; time ./omp $N ; rm omp
fi

