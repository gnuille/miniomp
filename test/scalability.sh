#!/bin/bash

USAGE="\n USAGE: ./run-extrae.sh prog num_threads\n
        prog1 -> miniomp program name\n
        prog2 -> omp program name\n"

if (test $# -lt 2 || test $# -gt 2)
then
        echo -e $USAGE
        exit 0
fi

N=3
i=1
MAX=24

prog1=$1
prog2=$2


while (test $i -lt $MAX)
	do
		echo -n -e "$i\t" >> plotdata;
		cnt=0
		cnt1=0
		cnt2=0
		while (test $cnt -lt $N)
			do
				t1=`./$1 | grep time | awk '{ print $NF }' | cut -c 1-8` 
				t2=`./$2 | grep time | awk '{ print $NF }' | cut -c 1-8` 
				cnt1=`echo $cnt1 + $t1|bc`
				cnt2=`echo $cnt2 + $t2|bc`
				
				cnt=`expr $cnt + 1`
			done
		cnt1=`echo $cnt1/$N|bc -l`
		cnt2=`echo $cnt2/$N|bc -l`
		
		echo -e -n "$cnt1\t$cnt2\n" >> plotdata	
		i=`expr $i + 1`
	done


