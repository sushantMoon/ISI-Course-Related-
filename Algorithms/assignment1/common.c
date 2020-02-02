#include "common.h"

void swap(lli *ary, int i, int j){
	// swaps the elements from ith and jth position in the ary
    lli temp = ary[i];
    ary[i] = ary[j];
    ary[j] = temp;
}

lli *copy_ary(lli *ary, int size){
	// creates the copy of array supplied
    lli *copy = MALLOC(lli, size);
    memcpy(copy, ary, sizeof(lli)*size);
    return copy;
}


void check_increasing_sequence(lli *ary, int size){
	// checks output form the sorting algorithms
	int ite_i = 0;
	int flag = 0;
	for(ite_i=1; ite_i < size; ite_i++){
		if(ary[ite_i-1] > ary[ite_i]){
			flag = 1;
		}
	}
	if (flag == 1){
		printf("The Result isnot sorted in increasing order!!\n");
	}
	else{
		printf("The Result is in ascending order!!\n");
	}
}
