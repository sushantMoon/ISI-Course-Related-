#include "min-max-heap.h"

// #define DEBUG
// Note : The functions are written considering 1 Based Indexing


MinMaxHeap *newMinMaxHeap(size_t element_size, int (*comparator)(void*, size_t, size_t)){
    MinMaxHeap *h = MALLOC(MinMaxHeap, 1);
    h->element_size = element_size;
    h->num_elements = 0;
    h->max_elements = _INIT_MAX_ELEMENTS_HEAP_;
    h->elements = malloc(element_size*h->max_elements);
    h->comparator = comparator;
    if (h->elements == NULL){
        printf("newMinMaxHeap : Failed to allot heap memory when initialising");
        // return NULL;
        exit(-1);
    }
    return h;
}


// Position Heap operations 
static size_t parent(MinMaxHeap *h, size_t position){
    size_t value = position/2;
    if (value >= 1 && h->num_elements != 0){
        return value;
    }
    else{
        #if defined(DEBUG)
        printf("Parent: parent[%d] is not Available\n", position);
        #endif // DEBUG
    }
    return 0;
}

static size_t rightChild(MinMaxHeap *h, size_t position){
    size_t value = (2*position) + 1;
    if (value > h->num_elements){
        #if defined(DEBUG)
        printf("RighChild : rightchild[%d] is not available\n", position);
        #endif // DEBUG 
    }
    return value;
}

static size_t leftChild(MinMaxHeap *h, size_t position){
    size_t value = (2*position);
    if (value > h->num_elements){
        #if defined(DEBUG)
        printf("LeftChild : leftchild[%d] is not available\n", position);
        #endif // DEBUG
    }
    return value;
}

static size_t level(size_t position){
    // even return value means minimum level
    // odd return value means maximum level
	return (size_t)(log(position)/log(2));
}

static size_t rightLeftGrandChild(MinMaxHeap *h, size_t position){
    size_t value = leftChild(h, rightChild(h, position));
    if (value > h->num_elements){
        #if defined(DEBUG)
        printf("rightLeftGrandChild : rightLeftGrandChild[%d] is not available\n", position);
        #endif // DEBUG 
    }
    return value;
}

static size_t rightRightGrandChild(MinMaxHeap *h, size_t position){
    size_t value = rightChild(h, rightChild(h, position));
    if (value > h->num_elements){
        #if defined(DEBUG)
        printf("rightRightGrandChild : rightRightGrandChild[%d] is not available\n", position);
        #endif // DEBUG 
    }
    return value;
}

static size_t leftRightGrandChild(MinMaxHeap *h, size_t position){
    size_t value = rightChild(h, leftChild(h, position));
    if (value > h->num_elements){
        #if defined(DEBUG)
        printf("leftRightGrandChild : leftRightGrandChild[%d] is not available\n", position);
        #endif // DEBUG
    }
    return value;
}

static size_t leftLeftGrandChild(MinMaxHeap *h, size_t position){
    size_t value = leftChild(h, leftChild(h, position));
    if (value > h->num_elements){
        #if defined(DEBUG)
        printf("leftLeftGrandChild : leftLeftGrandChild[%d] is not available\n", position);
        #endif // DEBUG
    }
    return value;
}

static size_t grandParent(MinMaxHeap *h, size_t position){
    size_t value = parent(h, parent(h, position));
    if (value >= 1 && h->num_elements != 0){
        return value;
    }
    else{
        #if defined(DEBUG)
        printf("GrandParent: grandParent[%d] is not Available\n", position);
        #endif // DEBUG
    }
    return 0;
}

// Basic Functionalities 
static void swap(MinMaxHeap *h, size_t i, size_t j){
    // using the 0th position for the swapping
    void *l1 = h->elements + (i*h->element_size);
    void *l2 = h->elements + (j*h->element_size);

    memcpy(h->elements, l1, h->element_size);
    memcpy(l1, l2, h->element_size);
    memcpy(l2, h->elements, h->element_size);
}

static void reduceMinMaxHeap(MinMaxHeap *h){
    h->max_elements = h->max_elements / 2;
    h->elements = realloc(h->elements,(h->element_size*h->max_elements));
    if (h->elements == NULL){
        printf("reduceMinMaxHeap : Failed memory allocation with MinMaxHeap resizing.\n");
        exit(0);
    }
}

static void growMinMaxHeap(MinMaxHeap *h){
    h->max_elements = h->max_elements * 2;
    h->elements = realloc(h->elements, (h->element_size*h->max_elements));
    if (h->elements == NULL){
        printf("growMinMaxHeap : Failed memory allocation with MinMaxHeap resizing.\n");
        exit(0);
    }
}

void freeMinMaxHeap(MinMaxHeap *h){
    free(h->elements);
    free(h);
}

//MinMaxHeap routines
static void TrickleDownMin(MinMaxHeap *h, size_t position){
    size_t minimum_position, t_pos;

    // Finding the position of the minimum value

    if (leftChild(h, position) > h->num_elements){return;}
    minimum_position = leftChild(h, position);

    t_pos = rightChild(h, position);
    if (t_pos < h->num_elements){
        if (h->comparator(h->elements, t_pos, minimum_position) < 0){
            minimum_position = t_pos;
        }
    }

    t_pos = leftLeftGrandChild(h, position);
    if (t_pos < h->num_elements){
        if (h->comparator(h->elements, t_pos, minimum_position) < 0){
            minimum_position = t_pos;
        }
    }

    t_pos = leftRightGrandChild(h, position);
    if (t_pos < h->num_elements){
        if (h->comparator(h->elements, t_pos, minimum_position) < 0){
            minimum_position = t_pos;
        }
    }

    t_pos = rightLeftGrandChild(h, position);
    if (t_pos < h->num_elements){
        if (h->comparator(h->elements, t_pos, minimum_position) < 0){
            minimum_position = t_pos;
        }
    }

    t_pos = rightRightGrandChild(h, position);
    if (t_pos < h->num_elements){
        if (h->comparator(h->elements, t_pos, minimum_position) < 0){
            minimum_position = t_pos;
        }
    }

    if (parent(h, minimum_position) == position){
        // minimum is among the childern
        if (h->comparator(h->elements, minimum_position, position) < 0) {
            swap(h, minimum_position, position);
        }
    }
    else{
        // minimum is among the grand childern
        if (h->comparator(h->elements, minimum_position, position) < 0) {
            swap(h, minimum_position, position);
            if (h->comparator(h->elements, minimum_position, parent(h, minimum_position)) > 0) {
                swap(h, minimum_position, parent(h, minimum_position));
            }
            TrickleDownMin(h, minimum_position);
        }
    }
}

static void TrickleDownMax(MinMaxHeap *h, size_t position){
    size_t maximum_position, t_pos;

    // Finding the position of the maximum value

    if (leftChild(h, position) > h->num_elements){return;}
    maximum_position = leftChild(h, position);

    t_pos = rightChild(h, position);
    if (t_pos < h->num_elements){
        if (h->comparator(h->elements, t_pos, maximum_position) > 0){
            maximum_position = t_pos;
        }
    }

    t_pos = leftLeftGrandChild(h, position);
    if (t_pos < h->num_elements){
        if (h->comparator(h->elements, t_pos, maximum_position) > 0){
            maximum_position = t_pos;
        }
    }

    t_pos = leftRightGrandChild(h, position);
    if (t_pos < h->num_elements){
        if (h->comparator(h->elements, t_pos, maximum_position) > 0){
            maximum_position = t_pos;
        }
    }

    t_pos = rightLeftGrandChild(h, position);
    if (t_pos < h->num_elements){
        if (h->comparator(h->elements, t_pos, maximum_position) > 0){
            maximum_position = t_pos;
        }
    }

    t_pos = rightRightGrandChild(h, position);
    if (t_pos < h->num_elements){
        if (h->comparator(h->elements, t_pos, maximum_position) > 0){
            maximum_position = t_pos;
        }
    }

    if (parent(h, maximum_position) == position){
        // maximum is among the childern
        if (h->comparator(h->elements, maximum_position, position) > 0) {
            swap(h, maximum_position, position);
        }
    }
    else{
        // maximum is among the grand childern
        if (h->comparator(h->elements, maximum_position, position) > 0) {
            swap(h, maximum_position, position);
            if (h->comparator(h->elements, maximum_position, parent(h, maximum_position)) < 0) {
                swap(h, maximum_position, parent(h, maximum_position));
            }
            TrickleDownMax(h, maximum_position);
        }
    }
}

static void TrickleDown(MinMaxHeap *h, size_t position){
    if (level(position)%2 == 0) {
        TrickleDownMin(h, position);
    }
    else{
        TrickleDownMax(h, position);
    }
}

static void BubbleUpMin(MinMaxHeap *h, size_t position){
    if (grandParent(h, position) > 0) {
        if (h->comparator(h->elements, position, grandParent(h, position)) < 0) {
            swap(h, position, grandParent(h, position));
            BubbleUpMin(h, grandParent(h, position));
        }
    }
}

static void BubbleUpMax(MinMaxHeap *h, size_t position){
    if (grandParent(h, position) > 0) {
        if (h->comparator(h->elements, position, grandParent(h, position)) > 0) {
            swap(h, position, grandParent(h, position));
            BubbleUpMax(h, grandParent(h, position));
        }
    }
}

static void BubbleUp(MinMaxHeap *h, size_t position){
    if (level(position)%2 == 0) {
        if ( (parent(h, position) > 0) && (h->comparator(h->elements, position, parent(h, position)) > 0) ) {
            swap(h, position, parent(h, position));
            BubbleUpMax(h, parent(h, position));
        }
        else {
            BubbleUpMin(h, position);
        }
    }
    else {
        if ( (parent(h, position) > 0) && (h->comparator(h->elements, position, parent(h, position)) < 0) ) {
            swap(h, position, parent(h, position));
            BubbleUpMin(h, parent(h, position));
        }
        else {
            BubbleUpMax(h, position);
        }
    }
}

void MinMaxHeapInsert(MinMaxHeap *h, const void *inputptr){
    // inputptr needs to already have been MALLOC'ed and initialised with the data 
    // that is going to be copied there
    if (h->num_elements + 1 == h->max_elements){
        growMinMaxHeap(h);
    }
    h->num_elements += 1;
    void *inputAddress = h->elements + (h->num_elements * h->element_size);
    memcpy(inputAddress, inputptr, h->element_size);
    BubbleUp(h, h->num_elements);
}

void MinMaxHeapExtractMin(MinMaxHeap *h, void *outputptr){
    // outputptr needs to already have been MALLOC'ed with the the size 
    // that is going to be copied there
    if(h->num_elements == 0){
        printf("No Elements Present in the MinMaxHeap\n");
        return;
    }

    if (h->num_elements + 1 <= (h->max_elements/4)) {
        reduceMinMaxHeap(h);
    }
    memcpy(outputptr, h->elements + h->element_size, h->element_size);
    swap(h, 1, h->num_elements);
    h->num_elements -= 1;
    TrickleDown(h, 1);
}

void MinMaxHeapExtractMax(MinMaxHeap *h, void *outputptr){
    // outputptr needs to already have been MALLOC'ed with the the size 
    // that is going to be copied there
    if(h->num_elements == 0){
        printf("No Elements Present in the MinMaxHeap\n");
        return;
    }

    if (h->num_elements + 1 <= (h->max_elements/4)) {
        reduceMinMaxHeap(h);
    }
    
    if (h->num_elements == 1) {
        memcpy(outputptr, h->elements + h->element_size, h->element_size);
        h->num_elements -= 1;
    }
    else if(h->num_elements == 2) {
        memcpy(outputptr, h->elements + (2 * h->element_size), h->element_size);
        h->num_elements -= 1;
    }
    else {
        if (h->comparator(h->elements, 2, 3) >= 0) {
            memcpy(outputptr, h->elements + (2 * h->element_size), h->element_size);
            swap(h, 2, h->num_elements);
            h->num_elements -= 1;
            TrickleDown(h, 2);
        }
        else {
            memcpy(outputptr, h->elements + (3 * h->element_size), h->element_size);
            swap(h, 3, h->num_elements);
            h->num_elements -= 1;
            TrickleDown(h, 3);
        }
    }
}

// Sample Comparators
int integer_comparator(void* array, size_t i, size_t j){
    return ( ((int *)array)[i] - ((int *)array)[j] );
}

float float_comparator(void* array, size_t i, size_t j){
    return ( ((float *)array)[i] - ((float *)array)[j] );
}