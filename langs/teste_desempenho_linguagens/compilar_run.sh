#!/bin/bash
N="$1"

if [ -z "$1" ]; then
        echo "Insert the integer arg: "
	echo "./compilar_run.sh 15"
else
	gcc -O3 -march=native -funroll-loops fiboc.c -o fiboc
	gfortran -O3 -march=native -funroll-loops fibof.f90 -o fibof
	rustc -C opt-level=3 -C target-cpu=native fiborust.rs -o fiborust

	julia fiboju.jl $N
	./fiboc $N
	./fibof $N
	./fiborust $N

	rm fiboc fibof fiborust
	rm cnz_str_to_int.mod cnz_test.mod
fi

