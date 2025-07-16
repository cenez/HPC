#!/bin/sh

gcc vector_add.c -o cpu
echo "***************************** CPU *****************************"
time ./cpu $N

nvcc vector_add_threads.cu -o gpu
echo "***************************** GPU *****************************"
time ./gpu $N
#nvprof ./gpu $N


