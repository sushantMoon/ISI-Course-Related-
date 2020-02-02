#include "common.h"
#include "heap.h"

void push_down_max_heap_recursive(lli *ary, int index, int size, llu *swap_comparision){
	// ary : array where we are maintaining the heap property 
	// index : positions where are checking the heap property 
	// size : size of heap
	// swap_comparisions : counter used for counting the comparisions made
	// output : compares index position element with its childern ; swaps with larger child 
	// and recursively calls the function again
	int largest = index;
	int leftc = LC(index);
    int rightc = RC(index);

	(*swap_comparision)++;
    if ((leftc < size) && (ary[leftc] > ary[largest])){
		(*swap_comparision)++;
		largest = leftc;
    }
	(*swap_comparision)++;
    if ((rightc < size) && (ary[rightc] > ary[largest])){
		(*swap_comparision)++;
		largest = rightc;
    }
	(*swap_comparision)++;
	if (largest != index){
		swap(ary, largest, index);
		(*swap_comparision)++;
        push_down_max_heap_recursive(ary, largest, size, swap_comparision);
	}
}


void heap_sort_recursive(lli *ary, int size, llu *swap_comparision){
	// ary : array where we are maintaining the heap property
	// size : size of heap
	// swap_comparisions : counter used for counting the comparisions made
	// Output: sorts the elements using recursive heap routines
    int ite_i = 0;
	for(ite_i = size/2 -1; ite_i > -1; ite_i--){
		push_down_max_heap_recursive(ary, ite_i, size, swap_comparision);
    }
	for(ite_i=size-1; ite_i>-1; ite_i--){
		swap(ary, 0, ite_i);
		(*swap_comparision)++;
        push_down_max_heap_recursive(ary, 0, ite_i, swap_comparision);
	}
}

// void max_heapify(lli *ary, int index, llu *swap_comparision){
// 	int parent = PARENT(index);
// 	while(ary[parent] < ary[index]){
// 		(*swap_comparision)++;
// 		swap(ary, parent, index);
// 		(*swap_comparision)++;
// 		index = parent;
// 		parent = PARENT(parent);
// 	}
// }

void arrange_in_asecending(lli *ary, int size, llu *swap_comparision){
	// ary : array where we are maintaining the heap property
	// size : size of heap
	// swap_comparisions : counter used for counting the comparisions made
	// Output: arranges the elements in ascending order, as first element is 
	// guarenteed to be the largest we swap it with the last element and interatively push 
	// the new first element down in its correct position 
    swap(ary, size-1, 0);
	(*swap_comparision)++;
	size -= 1;
	if (size <= 2){
		if(ary[1]<ary[0]){
			(*swap_comparision)++;
			swap(ary, 1, 0);
			(*swap_comparision)++;
		}
		return ;
	}

	push_down_max_heap_iterative(ary, 0, size, swap_comparision);
}

void push_down_max_heap_iterative(lli *ary, int index, int size, llu *swap_comparision){
	// ary : array where we are maintaining the heap property
	// index : position of the element which we are checking the heap property
	// size : size of heap
	// swap_comparisions : counter used for counting the comparisions made
	// Output: pushes the element down in the heap tree by iteratively comparing it with its
	//  childern as we swap it down the tree is the element in question is less than its childern
	//  till its correct position is found

	int max_index = (ary[LC(index)] < ary[RC(index)])?RC(index):LC(index);
	(*swap_comparision)++;
	
	while((max_index != -1) && (max_index < size)){
		if (ary[max_index] > ary[index]){
			(*swap_comparision)++;
			swap(ary, max_index, index);
			(*swap_comparision)++;
			index = max_index;
			if (( RC(index) < size ) && ( LC(index) < size )){
				(*swap_comparision)++;
				if (ary[RC(index)] < ary[LC(index)]){
					max_index = LC(index);
				}
				else{
					max_index = RC(index);
				}
				(*swap_comparision)++;
			}
			else if (RC(index) < size){
				(*swap_comparision)++;
				max_index = RC(index);
			}
			else if (LC(index) < size){
				(*swap_comparision)++;
				max_index = LC(index);
			}
			else{
				(*swap_comparision)++;
				break;
			}
		}
		else{
			(*swap_comparision)++;
			break;
		}
	}
}

void heap_sort_iterative(lli *ary, int size, llu *swap_comparision){
	// ary : array where we are maintaining the heap property
	// size : size of heap
	// swap_comparisions : counter used for counting the comparisions made
	// Output: sorts the element using iterative heap sort routines

    int ite_i = 0;

    for(ite_i = size/2 - 1; ite_i > -1; ite_i--){
		push_down_max_heap_iterative(ary, ite_i, size, swap_comparision);
    }

    while(size > 0){
        arrange_in_asecending(ary, size, swap_comparision);
		size--;
    }
}
