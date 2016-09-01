#!/bin/bash
g++ -std=c++11 mergesort_verbose.cpp -o merge
g++ -std=c++11 quicksort_verbose.cpp -o quick
RANDOM=$$
#echo "input"$c".txt"
# touch "input"$c".txt"
# echo -e "$RANDOM" >> "input"$c".txt"
# echo "$RANDOM" >> "input"$c".txt"
for c in {1..20}; do
	touch "input"$c".txt"
	for y in {1..500}; do
		echo -e "$RANDOM" >> "input"$c".txt"
	done
done

for x in {1..20}; do
	./quick "input"$x".txt" 15 > "qoutput"$x".txt"
    ./merge "input"$x".txt" > "moutput"$x".txt"
done

z=0
for x in {1..10}; do
	result=$(diff "qoutput"$x".txt" "moutput"$x".txt")
    if [ $? -eq 0 ]; then
    	rm "qoutput"$x".txt"
    	rm "moutput"$x".txt"
	else
   	    z=$((z+1))
   	    echo $result >> "quicksort_failed_test_"$x".txt"
   	    echo $result >> "mergesort_failed_test_"$x".txt"
	fi

done

if [ $z != 0 ]; then
	echo $z" tests failed"
else
	echo "All tests passed"
fi

#rm input*.txt
#rm moutput*.txt
#rm qoutput*.txt
