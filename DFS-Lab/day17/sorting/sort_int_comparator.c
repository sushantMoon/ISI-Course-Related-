#include<stdio.h>

int intComparator(int *a, int *b) {
    return *a - *b;
}

void swapInt(int *elem1, int *elem2) {
    int tmp;
    tmp = *elem1;
    *elem1 = *elem2;
    *elem2 = tmp;
}

//bubble sort
void inPlaceSort(int *arr, int elemCount,  int (*comparator) (int *, int *)) {
    int i,j;
    int swapped = 0;
    for(i = 0; i < elemCount-1; i++) {
        for(j = 0; j < elemCount-i-1; j++) {
            if(comparator(&arr[j], &arr[j+1]) > 1) { //ascending order
                swapInt(&arr[j], &arr[j+1]);
                swapped = 1;
            }
        }
        if(! swapped) break;
    }
}

void printArray(int *arr, int n) {
    int i;
    for(i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

int main() {
    int array[] = {32, 23, 24, 46, 57, 26, 75}; //7 elements
    
    inPlaceSort(array, 7, intComparator);

    printArray(array, 7);
    return 0;
}
