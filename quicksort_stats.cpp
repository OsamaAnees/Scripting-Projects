#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace std;

int partition =0;
int exchange = 0;
int comparisons = 0;
void quicksort(int a[], int lo, int hi){
	if (hi <= lo) return;
	srand (time(NULL));
	int index = lo + rand() % (hi - lo + 1);
	int buf = a[index];
	a[index] = a[hi];
	a[hi] = buf;
	int i = lo-1, j = hi;
	int t, v = a[hi];
	while (true)
	{
		partition++;
		while (a[++i] < v){
		  comparisons++;
		}
		while (v < a[--j]){
		  comparisons++;
                  if (j == lo) 
	            break;
                }
		if (i >= j) break;
		t = a[i]; a[i] = a[j]; a[j] = t;
		exchange++;
	}
	t= a[i]; a[i] = a[hi]; a[hi] = t;
	exchange++;
	quicksort(a, lo, i-1);
	quicksort(a, i+1, hi);
}

void insertionsort(int a[], int N){
	for (int i = 1; i < N; i++)
		for (int j = i; j >= 1 && a[j-1] > a[j]; j--){
			swap(a[j], a[j-1]);
			comparisons++;
			exchange++;
		}
}

int main(int argc, char** argv) {
    int k = atoi(argv[2]);
    string name = argv[1];
    ifstream in;
    int size =0;
    string buf;
    in.open(name);
    while(!in.eof()){
	in >> buf;
	size++;
    }
    //check if the end of the line is blank and adjust size
    in.seekg(-1,ios_base::end);
    char c;
    in >> c;
    if(c == '\0')
      size=size-1;
    in.close();
    int*a = new int[size];
    in.open(name);
    int i = 0;
    while(i!=size){
	in >> buf;
	if(buf.empty())
	  continue;
	a[i++] = stoi(buf);
    }
    in.close();
    srand(time(NULL));
    if(size <=k)
	insertionsort(a,size);
    else
    	quicksort(a, 0 ,size-1);
    cout << "Partitioning Stages: " << partition <<endl;
    cout << "Exchanges: " << exchange << endl;
    cout << "Compares: " << comparisons << endl;
    int min = a[0];
    delete[] a;
    return min;
}