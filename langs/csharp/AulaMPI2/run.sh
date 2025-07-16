#!/bin/bash
N=$1

if [ -z "$N" ]
then
	echo "##################################################################"
        echo "Digitar './run.sh N', para N o número de processos!" # Com ou sem extensao
	echo "##################################################################"
else
	cd bin/
	mpirun -np $N mono AulaMPI2.exe
	cd ../
fi





