#!/bin/bash

if ! [ $1 ]; then
	echo "Passar o parâmetro inteiro para troco. Exemplo:"
	echo "   #> ./run_troco.sh 8"
else
	javac Troco.java
	java Troco $1
	rm *.class
fi

