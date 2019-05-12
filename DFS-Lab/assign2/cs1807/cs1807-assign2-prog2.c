/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 30 September, 2018
Program description: 
Comparision between sorting distinct int's using qsort library function and k-heap sort (implemented)

Compiling using : gcc -g -Wall cs1807-assign2-prog2.c heap.c -o prog2 -lm
This code accepts command line argument

Run the code using `./prog2 {k} [k distinct elements]`
Eg : 
`./prog2 2 1 4 5 2 3 7 8 6 10 9`
`./prog2 3 3 4 1 2 5`

Note : 0 Based indexing

Acknowledgements:
------------------------------------*/

#include "heap.h"
#include <sys/time.h>
#include <sys/resource.h>

#define DURATION(start, end) ((end.tv_usec - start.tv_usec) + (end.tv_sec - start.tv_sec) * 1000000)

// #define CLOCKS_PER_MILLISEC (CLOCKS_PER_SEC/1000)
#define LOOPCOUNT 10000

int compartor_int(void *A, size_t a, size_t b){
    if (((int *)A)[(int)a] < ((int *)A)[(int)b]){
        return 1;
    }
    return 0;
}

int comparator_qsort(const void *a, const void *b){
    return *(int *)a - *(int *)b;
}

void comparing_qsort_heap(int *A, int size, int k){
    int i,j,l;
    Heap *h;
    printf("Comparing the runtime for sorting...\n");

    struct rusage usageInfo;
    struct timeval startUser, startSys, endUser, endSys;
    long long int timetaken = 0;

    for(l=0; l<LOOPCOUNT; l++){
        h = newHeap(sizeof(int), &compartor_int);
        for(i=0; i<k; i++){
            int *value = MALLOC(int, 1);
            *value = A[i];
            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            startUser = usageInfo.ru_utime;
            startSys = usageInfo.ru_stime;
            minHeapInsert(h, value);
            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            endUser = usageInfo.ru_utime;
            endSys = usageInfo.ru_stime;
            timetaken += (DURATION(startUser, endUser) + DURATION(startSys, endSys));
        }
        j = k;
        while(h->num_elements > 0){
            int *out = MALLOC(int, 1);
            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            startUser = usageInfo.ru_utime;
            startSys = usageInfo.ru_stime;
            extractMin(h, out);
            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            endUser = usageInfo.ru_utime;
            endSys = usageInfo.ru_stime;
            timetaken += (DURATION(startUser, endUser) + DURATION(startSys, endSys));
            if (j < size){
                int *input = MALLOC(int, 1);
                *input = A[j];
                if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                    perror("getrusage: ");
                startUser = usageInfo.ru_utime;
                startSys = usageInfo.ru_stime;
                minHeapInsert(h, input);
                if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                    perror("getrusage: ");
                endUser = usageInfo.ru_utime;
                endSys = usageInfo.ru_stime;
                timetaken += (DURATION(startUser, endUser) + DURATION(startSys, endSys));
                j++;
            }
        }
        freeHeap(h);
    }
    printf("Avg. Sorting time taken by k-sorted array using HEAP in %d repeatitions : %LF ms\n", LOOPCOUNT, (long double) (timetaken/LOOPCOUNT));
    
    timetaken = 0;
    int *B;
    for(l=0; l<LOOPCOUNT; l++){
        B = MALLOC(int, size);
        memcpy(B, A, sizeof(int)*size);
        if (0 != getrusage(RUSAGE_SELF, &usageInfo))
            perror("getrusage: ");
        startUser = usageInfo.ru_utime;
        startSys = usageInfo.ru_stime;
        qsort(B, size, sizeof(int), comparator_qsort);
        if (0 != getrusage(RUSAGE_SELF, &usageInfo))
            perror("getrusage: ");
        endUser = usageInfo.ru_utime;
        endSys = usageInfo.ru_stime;
        timetaken += (DURATION(startUser, endUser) + DURATION(startSys, endSys));
        free(B);
    }
    
    printf("Avg. Sorting time taken by k-sorted array using QSORT in %d repeatitions : %LF ms\n", LOOPCOUNT, (long double) (timetaken/LOOPCOUNT));
}

int main(int argc, char const *argv[]){
    int i,j;
    int size = (int)argc - 2;
    int k = (int)atoi(argv[1]);
    k += 1;
    int *A = MALLOC(int, size);
    for(i=0; (i+2)<argc; i++){
        A[i] = (int)atoi(argv[i+2]);
    }

    Heap *h = newHeap(sizeof(int), &compartor_int);
    for(i=0; i<k; i++){
        int *value = MALLOC(int, 1);
        *value = A[i];
        minHeapInsert(h, value);
    }

    // printf("Values :\n");
    // for(i=0;i<(int)h->num_elements;i++){
    //     printf("%d ", ((int *)h->elements)[i]);
    // }
    // printf("\n");
    j = k;
    while(h->num_elements > 0){
        int *out = MALLOC(int, 1);
        extractMin(h, out);
        printf("%d ", *out);
        // printf("Ejected Value : %d\n", *out);
        // printf("After Extract Heap :\n");
        // for(i=0;i<(int)h->num_elements;i++){
        //     printf("%d ", ((int *)h->elements)[i]);
        // }
        // printf("\n");
        if (j < size){
            int *input = MALLOC(int, 1);
            *input = A[j];
            minHeapInsert(h, input);
            j++;
        }
        // printf("After Insert Heap :\n");
        // for(i=0;i<(int)h->num_elements;i++){
        //     printf("%d ", ((int *)h->elements)[i]);
        // }
        // printf("\n");
    }
    printf("\n");
    freeHeap(h);

    // comparing_qsort_heap(A, size, k);

    return 0;
}
