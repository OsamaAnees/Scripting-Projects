#include <limits>
#include <string>
#include <utility>
#include <iostream>
#include <stdio.h>
#include <fstream>

#define INFTY std::numeric_limits<int>::max()

using namespace std;

int recursive = 0;
int transitions = 0;
int compare = 0;

void mergesort(int* a, int lo, int hi, std::string indent) {
    //std::cout << indent << "Mergesorting a[" << lo << ", " << hi <<  "]\n";
    if (hi <= lo) return;
    // Split array into two (roughly) equal sized subarrays
    int part = lo + (hi - lo) / 3;
    // Sort recursively
    int mid = lo + ((hi-lo)*(2))/3 ;
    mergesort(a, lo, part, indent + " ");
    recursive++;
    mergesort(a, part + 1, mid, indent + " ");
    recursive++;
    mergesort(a, mid + 1, hi, indent + " ");
    recursive++;
    // Copy sorted subarrays to buffers
    int sizeb = 0;
    if(lo <= part){
    	sizeb = (part-lo)+2;
    }
    int* b = new int[sizeb];
    int sizec = 0;
    if((part + 1) <= mid){
	sizec = (mid - part) + 1;
    }
    int* c = new int[sizec];
    int sized =0;
    if((mid+1) <= hi) {
    	sized = (hi - mid) + 1;
    }
    int* d = new int[sized];
    //std::cout << indent << "Sorted a[" << lo << "," << mid << "]: ";
    for (int k = lo; k <= part; k++) {
        b[k-lo] = a[k];
	compare++;
        //std::cout << b[k-lo] << " ";
    }
    //std::cout << indent << "Sorted a[" << mid + 1 << "," << hi << "]: ";
    for (int k = part+1; k <= mid; k++) {
        c[k-part-1] = a[k];
	compare++;
        //std::cout << c[k-part-1] << " ";
    }
    for (int k = mid+1; k <= hi; k++) {
        d[k-mid-1] = a[k];
	compare++;
        //std::cout << d[k-mid-1] << " ";
    }
    // Sentinel values for ease of merge implementation
    if(sizeb == 0)
	b[0] = INFTY;
    else
	b[part-lo+1] = INFTY;
    if(sizec == 0)
	c[0] = INFTY;
    else
	c[mid - part] = INFTY;
    if(sized == 0)
	d[0] = INFTY;
    else
	d[hi - mid] = INFTY;
    int i = 0, j = 0, l = 0;
    // Merge step
    //std::cout << indent << "Merged a: ";
    for (int k = lo; k <= hi; k++) {
        if (c[j] < b[i] && c[j] < d[l]){
          a[k] = c[j++];
	  transitions++;
	}
	else if(d[l] < b[i] && d[l] < c[j]){
	  a[k] = d[l++];
	  transitions++;
	}
        else{
             a[k] = b[i++];
	     transitions++;
	}
        //std::cout << a[k] << " ";
    }
    //std::cout << "\n";
    delete[] b;
    delete[] c;
    delete[] d;
}

int main(int argc, char** argv) {
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
    mergesort(a, 0, size - 1, "");
    cout << "Recursive Calls: " << recursive << endl;
    cout << "Transitions: " << transitions << endl;
    cout << "Compares: " << compare << endl;
    int min = a[0];
    delete[] a;
    return min;
}
