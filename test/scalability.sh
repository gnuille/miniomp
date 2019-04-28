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
i=2
MAX=25

prog1=$1
prog2=$2

rm plotdata 2>&1 > /dev/null | true
tseq1=0
tseq2=0
cnt=0
cnt1=0
cnt2=0
export OMP_NUM_THREADS=1
while (test $cnt -lt $N)
	do
		tseq1=`./$prog1 | grep time | awk '{ print $NF }' | cut -c 1-8` 
		tseq2=`./$prog2 | grep time | awk '{ print $NF }' | cut -c 1-8` 
		cnt1=`echo $cnt1 + $tseq1|bc`
		cnt2=`echo $cnt2 + $tseq2|bc`
		
		cnt=`expr $cnt + 1`
	done

tseq1=`echo $cnt1/$N|bc -l`
tseq2=`echo $cnt2/$N|bc -l`
echo -e -n "1\t$tseq1\t$tseq2\t1\t1\n" >> plotdata

while (test $i -lt $MAX)
	do
		export OMP_NUM_THREADS=$i
		echo -n -e "$i\t" >> plotdata;
		cnt=0
		cnt1=0
		cnt2=0
		echo "Running iteration $i"
		while (test $cnt -lt $N)
			do
				echo "$cnt run"
				t1=`./$prog1 | grep time | awk '{ print $NF }' | cut -c 1-8` 
				t2=`./$prog2 | grep time | awk '{ print $NF }' | cut -c 1-8` 
				cnt1=`echo $cnt1 + $t1|bc`
				cnt2=`echo $cnt2 + $t2|bc`
				
				cnt=`expr $cnt + 1`
			done
		cnt1=`echo $cnt1/$N|bc -l`
		cnt2=`echo $cnt2/$N|bc -l`
		s1=`echo $tseq1/$cnt1|bc -l`	
		s2=`echo $tseq2/$cnt2|bc -l`	
		echo -e -n "$cnt1\t$cnt2\t$s1\t$s2\n" >> plotdata	
		i=`expr $i + 2`
	done

cat > plotscript << EOF
set terminal png size 800,600 enhanced font "Helvetica,12"
set output 'output.png'


set multiplot layout 1,2

f(x) = x
set size ratio 1
set xrange [1:24]
set xtics 2
set xlabel "OMP #threads"
set ylabel "Time (s)"
set title "Average elapsed execution time"
plot 'plotdata' using 1:2 with lines lw 2 title "miniomp", 'plotdata' using 1:3 with lines lw 2 title "openmp"
set yrange [1:24]
set size ratio -1
set xlabel "OMP #threads"
set ylabel "Speed-up"
set title "Speed-up  wrt sequential time"
plot 'plotdata' using 1:4 with lines lw 2 title "miniomp", 'plotdata' using 1:5 with lines lw 2 title "openmp", f(x) notitle

unset multiplot 
EOF
gnuplot plotscript
rm plotscript
