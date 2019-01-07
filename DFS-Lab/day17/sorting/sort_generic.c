#include<malloc.h>
#include<string.h>

void swapemp(void *a, void *b, int elemSize) {
    void *tmp = malloc(sizeof(elemSize));
    memcpy(tmp, a, elemSize); //blind memory copy
    memcpy(a, b, elemSize);
    memcpy(b, tmp, elemSize);
    free(tmp);
}

//bubble sort
void inPlaceSort(void *arr, int elemCount, int elemSize, int (*comparator) (void *, void *)) {
    int i,j;
    int swapped = 0;
    for(i = 0; i < elemCount-1; i++) {
        for(j = 0; j < elemCount-i-1; j++) {
            if(comparator((arr + j*elemSize), (arr +(j+1)*elemSize)) > 0) { //ascending order
                swapemp((arr + j*elemSize), (arr +(j+1)*elemSize), elemSize);
                swapped = 1;
            }
        }
        if(! swapped) break;
    }
}
