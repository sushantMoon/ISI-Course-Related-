#ifndef __COMMON_H__ 
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <sys/time.h>
#include <sys/resource.h>

#define DURATION(start, end) ((end.tv_usec - start.tv_usec) + (end.tv_sec - start.tv_sec) * 1000000)

#define MALLOC(type, n) (type *)malloc(sizeof(type)*n)
#define MIN(a, b) (a>b)?b:a
#define MAX(a, b) (a>b)?a:b
#define lli long long int
#define llu unsigned long long int

#define repetition 5  // repeatitions sorts
#define LOOPCOUNT 1    // for RUsage Time Measurement

#define MODULO 1000000   // getting random numbers within some range
//#define MaxNumElements 31151588
#define MaxNumElements 4102268
void swap(lli *ary, int i, int j);
lli *copy_ary(lli *ary, int size);
void check_increasing_sequence(lli *ary, int size);
#endif // __COMMON_H__


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


// zero based indexing
#ifndef __HEAP__
#define __HEAP__
#define PARENT(index) (int)((index-1)/2) 
#define LC(index) (int)((2*index)+1)
#define RC(index) (int)((2*index) + 2)
#endif // __HEAP__

void heap_sort_iterative(lli *ary, int size, llu *swap_comparision);
void arrange_in_asecending(lli *ary, int size, llu *swap_comparision); 
void push_down_max_heap_iterative(lli *ary, int index, int size, llu *swap_comparision);

void heap_sort_recursive(lli *ary, int size, llu *swap_comparision);
void push_down_max_heap_recursive(lli *ary, int index, int size, llu *swap_comparision);


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


void merge(lli *ary, int l, int m, int h, llu *swap_comparision);
void merge_sort_iterative(lli *ary, int size, llu *swap_comparision);
void merge_sort_recursive(lli *ary, int l, int h, llu *swap_comparision);

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


void pivot_partition(lli *ary, int l, int *pivot, int , llu *swap_comparision);
void quick_sort_recursive(lli *ary, int l, int h, llu *swap_comparision);
void quick_sort_iterative(lli *ary, int l, int h, llu *swap_comparision);

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

int main(){

    struct rusage usageInfo;
    struct timeval startUser, startSys, endUser, endSys;
    lli time_taken_q_r = 0;
    lli time_taken_m_r = 0;
    lli time_taken_h_r = 0;
    lli time_taken_q_i = 0;
    lli time_taken_m_i = 0;
    lli time_taken_h_i = 0;
    llu swap_comparision_h=0, swap_comparision_q=0, swap_comparision_m=0;
    int n;

    printf("####################Recursive Routines####################\n");
    printf("N,\tQuick Sort,\tMerge Sort,\tHeap Sort\n");
    printf("#N,\tQ. Time,\tQ. Swap_Comparsion,\tM. Time,\tM. Swap_Comparsion,\tH. Time,\tH. Swap_Comparsion\n");

    for(n = 10; n < MaxNumElements; n += n/2){

        lli *ary, *ary_copy;
        int ite_i;
        
        // seeding random 
        srand(time(0));
        
        ary = MALLOC(lli, n);
        for(ite_i=0; ite_i<n; ite_i++){
            ary[ite_i] = rand()%MODULO;
        }

        ite_i = repetition;
        while(ite_i > 0){
            ary_copy = copy_ary(ary, n);
            llu swap_comparision_temp = 0;

            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            startUser = usageInfo.ru_utime;
            startSys = usageInfo.ru_stime;

            quick_sort_recursive(ary_copy, 0, n-1, &swap_comparision_temp);

            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            endUser = usageInfo.ru_utime;
            endSys = usageInfo.ru_stime;

            time_taken_q_r += (DURATION(startUser, endUser) + DURATION(startSys, endSys));
            ite_i -= 1;
            free(ary_copy);                        	
            swap_comparision_q += (swap_comparision_temp/repetition);
        }
        
        ite_i = repetition;
        while(ite_i > 0){
            ary_copy = copy_ary(ary, n);	
            llu swap_comparision_temp = 0;

            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            startUser = usageInfo.ru_utime;
            startSys = usageInfo.ru_stime;

            merge_sort_recursive(ary_copy, 0, n-1, &swap_comparision_temp);

            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            endUser = usageInfo.ru_utime;
            endSys = usageInfo.ru_stime;

            time_taken_m_r += (DURATION(startUser, endUser) + DURATION(startSys, endSys));
            ite_i -= 1;
            free(ary_copy);

            swap_comparision_m += (swap_comparision_temp/repetition);

        }
        
        ite_i = repetition;
        while(ite_i > 0){
            ary_copy = copy_ary(ary, n);	
            llu swap_comparision_temp = 0;

            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            startUser = usageInfo.ru_utime;
            startSys = usageInfo.ru_stime;

            heap_sort_recursive(ary_copy, n, &swap_comparision_temp);

            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            endUser = usageInfo.ru_utime;
            endSys = usageInfo.ru_stime;

            time_taken_h_r += (DURATION(startUser, endUser) + DURATION(startSys, endSys));
            ite_i -= 1;
            free(ary_copy);
            swap_comparision_h += (swap_comparision_temp/repetition);
        }
        
        free(ary);

        printf(
            "%d,\t%.0LF,\t%llu,\t%.0LF,\t%llu,\t%.0LF,\t%llu\n", 
            n,
            (long double)((long double)time_taken_q_r/(long double)(LOOPCOUNT*repetition)),
            swap_comparision_q,
            (long double)((long double)time_taken_m_r/(long double)(LOOPCOUNT*repetition)),
            swap_comparision_m,
            (long double)((long double)time_taken_h_r/(long double)(LOOPCOUNT*repetition)), 
            swap_comparision_h
        );
    }



    printf("##########################################################\n");    
    swap_comparision_h=0, swap_comparision_q=0, swap_comparision_m=0;

    printf("####################Iterative Routines####################\n");
    printf("N,\tQuick Sort,\tMerge Sort,\tHeap Sort\n");
    printf("#N,\tQ. Time,\tQ. Swap_Comparsion,\tM. Time,\tM. Swap_Comparsion,\tH. Time,\tH. Swap_Comparsion\n");

    for(n = 10; n < MaxNumElements; n += n/2){

        lli *ary, *ary_copy;
        int ite_i;
        
        // seeding random 
        srand(time(0));
        
        ary = MALLOC(lli, n);
        for(ite_i=0; ite_i<n; ite_i++){
            ary[ite_i] = rand()%MODULO;
        }

        ite_i = repetition;
        while(ite_i > 0){
            ary_copy = copy_ary(ary, n);
            llu swap_comparision_temp = 0;

            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            startUser = usageInfo.ru_utime;
            startSys = usageInfo.ru_stime;

            quick_sort_iterative(ary_copy, 0, n-1, &swap_comparision_temp);

            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            endUser = usageInfo.ru_utime;
            endSys = usageInfo.ru_stime;

            time_taken_q_i += (DURATION(startUser, endUser) + DURATION(startSys, endSys));
            ite_i -= 1;
            free(ary_copy);                        	
            swap_comparision_q += (swap_comparision_temp/repetition);
        }
        
        ite_i = repetition;
        while(ite_i > 0){
            ary_copy = copy_ary(ary, n);	
            llu swap_comparision_temp = 0;

            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            startUser = usageInfo.ru_utime;
            startSys = usageInfo.ru_stime;

        	merge_sort_iterative(ary_copy, n, &swap_comparision_temp);

            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            endUser = usageInfo.ru_utime;
            endSys = usageInfo.ru_stime;

            time_taken_m_i += (DURATION(startUser, endUser) + DURATION(startSys, endSys));
            ite_i -= 1;
            free(ary_copy);

            swap_comparision_m += (swap_comparision_temp/repetition);

        }
        
        ite_i = repetition;
        while(ite_i > 0){
            ary_copy = copy_ary(ary, n);	
            llu swap_comparision_temp = 0;

            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            startUser = usageInfo.ru_utime;
            startSys = usageInfo.ru_stime;

            heap_sort_iterative(ary_copy, n, &swap_comparision_temp);    

            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            endUser = usageInfo.ru_utime;
            endSys = usageInfo.ru_stime;

            time_taken_h_i += (DURATION(startUser, endUser) + DURATION(startSys, endSys));
            ite_i -= 1;
            free(ary_copy);
            swap_comparision_h += (swap_comparision_temp/repetition);
        }
        
        free(ary);

        printf(
            "%d,\t%.0LF,\t%llu,\t%.0LF,\t%llu,\t%.0LF,\t%llu\n", 
            n,
            (long double)((long double)time_taken_q_i/(long double)(LOOPCOUNT*repetition)),
            swap_comparision_q,
            (long double)((long double)time_taken_m_i/(long double)(LOOPCOUNT*repetition)),
            swap_comparision_m,
            (long double)((long double)time_taken_h_i/(long double)(LOOPCOUNT*repetition)), 
            swap_comparision_h
        );
    }
    printf("##########################################################\n");

	return 0;
}