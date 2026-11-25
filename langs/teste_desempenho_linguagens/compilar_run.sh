#!/bin/bash
N="$1"

ROOT=$(pwd)
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" &> /dev/null && pwd)"
cd "$SCRIPT_DIR" || exit
BIN="$SCRIPT_DIR"

if [ -z "$1" ]; then
    echo "Insert the integer arg. Ex: "
	echo "$BIN/compilar_run.sh 15"
else
	gcc -O3 -march=native -funroll-loops $BIN/fiboc.c -o $BIN/fiboc
	gfortran -O3 -march=native -funroll-loops $BIN/fibof.f90 -o $BIN/fibof
	rustc -C opt-level=3 -C target-cpu=native $BIN/fiborust.rs -o $BIN/fiborust

	julia -O3 --check-bounds=no -t auto $BIN/fiboju.jl $N
	$BIN/fiboc $N
	$BIN/fibof $N
	$BIN/fiborust $N
	rm $BIN/fiboc $BIN/fibof $BIN/fiborust
	rm $BIN/cnz_str_to_int.mod $BIN/cnz_test.mod
fi
cd $ROOT

