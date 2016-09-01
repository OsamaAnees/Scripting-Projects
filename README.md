# Scripting-Projects
These are Bash Scripts I wrote for an ECS class to compare sorting algorithms.

This bash script was designed to compare the run time and statistics of the quicksort and mergesort algorithms. 
The script creates text files of random integer outputs to be sorted. 

The sanity_check script runs the "verbose" versions of a mergesort and quicksort implemenation. This script runs the algorithms on sample inputs and compares the outputs to make sure the algorithms are sorting the same way.

The pipeline script times the algorithms and takes statistics such as the partitioning stages and variable swaps and puts them into a csv file for comparison.

In order for the script to run the mergesort and quicksort algorithms must be included within the file and all 3 versions of the algorithms(verbose,timed,statistics) must be present.

