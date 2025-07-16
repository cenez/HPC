#!/bin/bash

N=$1

if [ -z "$N" ]
then
	echo "##################################################################"
        echo "Digitar './compile_run.sh.sh N', para N o número de processos!"
	echo "##################################################################"
else
	./compile.sh
	./run.sh $N
fi


