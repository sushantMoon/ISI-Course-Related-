#include "common.h"

// zero based indexing
#ifndef __HEAP__
#define __HEAP__
#define PARENT(index) (int)((index-1)/2) 
#define LC(index) (int)((2*index)+1)
#define RC(index) (int)((2*index) + 2)
#endif // __HEAP__

void heap_sort_iterative(lli *ary, int size, llu *swap_comparision);
void arrange_in_asecending(lli *ary, int size, llu *swap_comparision); 
// void max_heapify(lli *ary, int index, llu *swap_comparision);
void push_down_max_heap_iterative(lli *ary, int index, int size, llu *swap_comparision);

void heap_sort_recursive(lli *ary, int size, llu *swap_comparision);
void push_down_max_heap_recursive(lli *ary, int index, int size, llu *swap_comparision);