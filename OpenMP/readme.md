#!/bin/sh

#export OMP_NUM_THREADS=8

gcc -o a -fopenmp open_mp.c
time ./a $1

gcc -o b -fopenmp vector_add.c
time ./b $1

#rm a b

#nvcc hello.cu -o a ; ./a

