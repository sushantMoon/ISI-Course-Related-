#include "common.h"
#include "quick.h"

void pivot_partition(lli *ary, int l, int *pivot, int h, llu *swap_comparision){
	// ary : array where we are maintaining the heap property
	// l : index of the lowest element in the array 
	// h : index of the highest element in the array 
    // swap_comparisions : counter used for counting the comparisions made
    // Output : For the elements between arry[l..h] ,based on the pivot,
	//  elements > pivot are moved after pivot  
	//  elements < pivot are moved before pivot
	// everything inplace

    int itr_i, itr_j;
    //pivot to the end 
    swap(ary, (*pivot), h);
	// (*swap_comparision)++;
    (*pivot) = h;
    itr_i = l-1;

    for(itr_j = l; itr_j < h; itr_j++){
        if (ary[itr_j] <= ary[(*pivot)]){
            itr_i += 1;
            swap(ary, itr_i, itr_j);
			(*swap_comparision)++;
        }
		(*swap_comparision)++;
    }
    swap(ary, itr_i+1, (*pivot));
	// (*swap_comparision)++;
    (*pivot) = itr_i + 1;
}

void quick_sort_iterative(lli *ary, int l, int h, llu *swap_comparision){
	// ary : array where we are maintaining the heap property
	// l : index of the lowest element in the array 
	// h : index of the highest element in the array 
    // swap_comparisions : counter used for counting the comparisions made
    // Output : Iteratively sort the elements between arry[l..h], based on the random pivot.
	int *index_ary = MALLOC(int, h-l+1);
	int counter = -1;
	
	counter += 1;	
	index_ary[counter] = l;
	counter += 1;
	index_ary[counter] = h;
	
	while(counter >= 0){
	 	int high = index_ary[counter];
		counter -= 1;
		int low = index_ary[counter];
		counter -= 1;

		//selecting pivot randomly
		int pivot = low + rand()%(high-low+1);

		pivot_partition(ary, low, &pivot, high, swap_comparision);
	
		if (pivot-1 > low){
			counter += 1;
			index_ary[counter] = low;
			counter += 1;
			index_ary[counter] = pivot-1;
		}
		(*swap_comparision)++;

		if (high > pivot+1){
			counter += 1;
			index_ary[counter] = pivot+1;
			counter += 1;
			index_ary[counter] = high;
		}
		(*swap_comparision)++; 
	}
}

void quick_sort_recursive(lli *ary, int l, int h, llu *swap_comparision){
	// ary : array where we are maintaining the heap property
	// l : index of the lowest element in the array 
	// h : index of the highest element in the array 
    // swap_comparisions : counter used for counting the comparisions made
    // Output : Recursively sort the elements between arry[l..h], based on the random pivot.

    if (l < h) {
		//selecting pivot randomly
		int pivot = l + rand()%(h-l+1);
		pivot_partition(ary, l, &pivot, h, swap_comparision);

        quick_sort_recursive(ary, l, pivot-1, swap_comparision);
        quick_sort_recursive(ary, pivot+1, h, swap_comparision);
    }
	(*swap_comparision)++;
}