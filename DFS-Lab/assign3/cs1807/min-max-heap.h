#include "common.h"

#ifndef _G_COMMON_H_
#define _G_COMMON_H_
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#endif


#if !defined(__G_MIN_MAX_HEAP__)
#define __G_MIN_MAX_HEAP__

#define _INIT_MAX_ELEMENTS_HEAP_ 8

typedef struct MinMaxHeap{
    // Array Implementation
    // 1 based indexing (to make life easier with level function)
    void *elements;
    size_t element_size;
    // size of the type of element stored in the heap
    size_t num_elements;
    // total elements in the heap
    size_t max_elements;
    // maximum number of elemes at the heap can handle
    int (*comparator)(void*, size_t, size_t);
    //comparator function (for custom checking of which node is greater than the other)
    // first argument of comarator is the array
    // second argument is the first postion value in the array we need to compare
    // third argument is the second postion value in the array we need to compare
    // the comparator should return  value > 0 if the value at the position give by second 
    // argument is more than third argument else < 0, and if they are equal then 0
}MinMaxHeap;



MinMaxHeap *newMinMaxHeap(size_t element_size, int (*comparator)(void*, size_t, size_t));

// Position MinMaxHeap operations 
// static size_t parent(MinMaxHeap *h, size_t position);            //  Static functions (iternal routines)
// static size_t rightChild(MinMaxHeap *h, size_t position);            //  Static functions (iternal routines)
// static size_t leftChild(MinMaxHeap *h, size_t position);         //  Static functions (iternal routines)
// static size_t level(size_t position);            //  Static functions (iternal routines)

// Basic Functionalities 
// static void swap(MinMaxHeap *h, size_t i, size_t j);         //  Static functions (iternal routines)
// static void reduceMinMaxHeap(MinMaxHeap *h);         //  Static functions (iternal routines)
// static void growMinMaxHeap(MinMaxHeap *h);           //  Static functions (iternal routines)
void freeMinMaxHeap(MinMaxHeap *h);


//MinMaxHeap routines
// static void TrickleDown(MinMaxHeap *h, size_t position);         //  Static functions (iternal routines)
// static void TrickleDownMin(MinMaxHeap *h, size_t position);          //  Static functions (iternal routines)
// static void TrickleDownMax(MinMaxHeap *h, size_t position);          //  Static functions (iternal routines)

// static void BubbleUp(MinMaxHeap *h, size_t position);            //  Static functions (iternal routines)
// static void BubbleUpMin(MinMaxHeap *h, size_t position);         //  Static functions (iternal routines)
// static void BubbleUpMax(MinMaxHeap *h, size_t position);         //  Static functions (iternal routines)

void MinMaxHeapInsert(MinMaxHeap *h, const void *inputptr);
void MinMaxHeapExtractMin(MinMaxHeap *h, void *outputptr);
void MinMaxHeapExtractMax(MinMaxHeap *h, void *outputptr);


// Sample Comparators
int integer_comparator(void* array, size_t i, size_t j);
float float_comparator(void* array, size_t i, size_t j);

#endif // __G_MIN_MAX_HEAP__
