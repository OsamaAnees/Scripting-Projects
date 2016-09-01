#!/bin/bash
g++ -std=c++11 $1_timed.cpp -o time
g++ -std=c++11 $1_stats.cpp -o stat

echo "Sample Number", "Language", "Time", "Number of Partitioning Stages", "Number of Exchanges", "Number of Compares" > quicksort.csv

TIMEFORMAT=%R

for c in $(seq 1 $2); do
	touch "input"$c".txt"
	for y in $(seq 1 $3); do
		echo -e "$RANDOM" >> "input"$c".txt"
	done
done

for x in $(seq 1 $2); do
	if [ "$1" == "quicksort" ]; then
		time=$(echo -n $({ time ./time "input"$x".txt" 15; } 2>&1 | tr -d '\n'))
        	qstat="$(./stat "input"$x".txt" 15)"
		qstat=$(echo $qstat|tr -d '\n')
                arr=($qstat)
	else
		time=$(echo -n $({ time ./time "input"$x".txt"; } 2>&1 | tr -d '\n'))
        	qstat="$(./stat "input"$x".txt")"
		qstat="$(./stat "input"$x".txt" 15)"
		qstat=$(echo $qstat|tr -d '\n')
                arr=($qstat)
	fi
	finalString="$x, C++, $time, ${arr[2]}, ${arr[4]}, ${arr[6]}"
	printf "%s\\n" "$finalString" >> $1.csv
done

rm *.txt
