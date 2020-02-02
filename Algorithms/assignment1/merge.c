#include "common.h"
#include "merge.h"

// void merge_inplace(lli *ary, int l, int m, int h, llu *swap_comparision){
//     int ite_i, ite_j, ite;
//     // Inplace Merge
//     ite_i = l;
//     ite_j = m+1;

//     (*swap_comparision)++;
//     if(ary[m] <= ary[ite_j]){
//         return;
//     }
//     while(ite_i <= m && ite_j <= h){
//         (*swap_comparision)++;
//         if(ary[ite_i] <= ary[ite_j]){
//             ite_i++;
//         }
//         else{
//             int value = ary[ite_j];
//             ite = ite_j;
//             while(ite != ite_i){
//                 (*swap_comparision)++;
//                 ary[ite] = ary[ite-1];
//                 ite--;
//             }
//             ary[ite_i] = value;
//             ite_i++;
//             m++;
//             ite_j++;
//         }
//     }
//     return;
// }

void merge(lli *ary, int l, int m, int h, llu *swap_comparision){
    // ary : array where we are maintaining the heap property
	// l : lowest element index that of our current window 
    // m : middle element index that of our current window
    // h : last element index that of our current window
	// swap_comparisions : counter used for counting the comparisions made
    // Output : merges the two sorted subarrays ary[l..m] ary[m+1 .. h] in ascending order
    int ite_i, ite_j, ite;
    int n_1 = m-l+1, n_2 = h-m;

    lli *L = MALLOC(lli, n_1);
    lli *R = MALLOC(lli, n_2);

    for(ite_i=0; ite_i<n_1; ite_i++){
        // (*swap_comparision)++;
        L[ite_i] = ary[l + ite_i];
    }

    for(ite_i=0; ite_i<n_2; ite_i++){
        // (*swap_comparision)++;
        R[ite_i] = ary[m + 1 + ite_i];
    }

    ite_i = 0;
    ite_j = 0;
    ite = l;

    while(ite_i < n_1 && ite_j < n_2){
        if (L[ite_i] >= R[ite_j]){
            ary[ite] = R[ite_j];
            ite_j++;
        }
        else{
            ary[ite] = L[ite_i];
            ite_i++;
        }
        (*swap_comparision) += 2;
        ite++;
    }
    
    while(ite_i < n_1){
        ary[ite] = L[ite_i];
        ite++;
        ite_i++;
    }

    while(ite_j < n_2){
        ary[ite] = R[ite_j];
        ite++;
        ite_j++;
    }
}

void merge_sort_recursive(lli *ary, int l, int h, llu *swap_comparision){
    // ary : array where we are maintaining the heap property
	// l : lowest element index that of our current window 
    // h : last element index that of our current window
	// swap_comparisions : counter used for counting the comparisions made
    // Output : merge sort in recursive manner the elements between arry[l..h]
    if(l < h){
        int m = ( l + ((h-l)/2) );
        merge_sort_recursive(ary, l, m, swap_comparision);
        merge_sort_recursive(ary, m+1, h, swap_comparision);
        merge(ary, l, m, h, swap_comparision);
    }
    // (*swap_comparision)++;
}

void merge_sort_iterative(lli *ary, int size, llu *swap_comparision){
    // ary : array where we are maintaining the heap property
	// size : size of the array we need to merge sort 
    // swap_comparisions : counter used for counting the comparisions made
    // Output : merge sort in iterative manner the elements between arry[l..h]

	// bottom up approach is taken
	int window_half; // window size is 2 time os winow half
    int l, h, m;

	for(window_half = 1; window_half < size; window_half *= 2){		// window size increases by 2 times 
		for(l = 0; l < size-1; l += (2*window_half)){		// the left element would have to be skip 2* windows size
		 	// (*swap_comparision)++;
            // middle element would be at low + window_half -1
            if (l + window_half - 1 > size -1){
                m = l + ((size-l)/2) - 1;
            }
            else{
    			m = l + window_half - 1;                
            }              
		 	// highest element would be at high + 2*window_half -1		
			h = MIN(l + (2*window_half) -1, size-1); 
			merge(ary, l, m, h, swap_comparision);		
		}
	}
}
