#!/bin/bash

if ! [ $1 ]; then
	echo "Passar o par�metro inteiro para troco. Exemplo:"
	echo "   #> ./run_troco.sh 8"
else
	python Troco.py $1
fi

