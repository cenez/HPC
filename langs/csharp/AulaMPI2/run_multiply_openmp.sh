#!/bin/bash

#./compile.sh 4
cp bin/matrix16.txt matrix_multiply_openmp/
cd matrix_multiply_openmp/
gcc -fopenmp *.h *.c -o main
./main 16
cd ../


