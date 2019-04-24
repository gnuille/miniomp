#!/bin/bash

USAGE="\n USAGE: ./run-omp.sh prog num_threads\n
        prog        -> omp program name\n
	num_threads -> number of threads\n"

if (test $# -lt 2 || test $# -gt 2)
then
	echo -e $USAGE
        exit 0
fi

i=1
MAX=24
N=3

while (test $i -le $MAX)
do
	echo -e -n "$i\t"
	export OMP_NUM_THREADS=$i
	elapsed1=0
	elapsed2=0
	it=0
	while (test $it -lt $N)
	do
		./$1 | grep time | a
