#!/bin/bash
N="$1"

if [ -z "$1" ]; then
    echo "Insert the integer arg. Ex: "
	echo "./compilar_run.sh 15"
else
	gcc -O3 -march=native -funroll-loops fiboc.c -o fiboc
	gfortran -O3 -march=native -funroll-loops fibof.f90 -o fibof
	rustc -C opt-level=3 -C target-cpu=native fiborust.rs -o fiborust

	julia -O3 --check-bounds=no -t auto fiboju.jl $N
	./fiboc $N
	./fibof $N
	./fiborust $N
	./jaga_compile.sh fibo_jaga.jg ; ./fibo_jaga $N

	#rm fiboc fibof fiborust fibo_jaga
	rm cnz_str_to_int.mod cnz_test.mod
fi

