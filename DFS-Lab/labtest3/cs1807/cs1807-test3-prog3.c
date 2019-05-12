/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 9 October, 2018
Program description: Planetory Transition

Compile using :
```
gcc -g -Wall cs1807-test3-prog3.c heap.c -o prog3 -lm
```

Acknowledgements:
------------------------------------*/

#include "heap.h"

typedef struct dim{
    int position; // array position
    double brightness; // brightness
}DIM;

int comparator_brightness(void *A, size_t a, size_t b){
    if ( ((DIM *)A)[(int)a].brightness < ((DIM *)A)[(int)b].brightness ){
        return 1;
    }
    return 0;
}

int comparator_positon(const void *a, const void *b){
    return ((DIM *)a)->position - ((DIM *)b)->position;
}

int main(){
    int m, k, i, j = 0;
    double b = -2;
    scanf("%d %d", &m, &k);
    Heap *minh = newHeap(sizeof(DIM), &comparator_brightness);
    while(b != -1){
        scanf("%lf", &b);
        if (b < 0){
            break;
        }
        DIM *ip = MALLOC(DIM, 1);
        ip->position = j;
        ip->brightness = b;
        minHeapInsert(minh, ip);
        j++;
    }
    DIM *minDim = MALLOC(DIM, m);
    for(i=0; i<m; i++){
        DIM *op = MALLOC(DIM, 1);
        extractMin(minh, op);
        minDim[i] = *op;
        // printf("%lf ", minDim[i].brightness);
    }
    // printf("/n");
    qsort(minDim, m, sizeof(DIM), comparator_positon);

    // int count = 1;
    // int index = minDim[0].position;
    // for(i=1; i<m; i++){
    //     if( index+1 == minDim[i].position ){
    //         index += 1;
    //         count++;
    //     }
    //     else{
    //         break;
    //     }
    // }
    // if (count >= k){
    //     printf("TRUE\n");
    // }
    // else{
    //     printf("FALSE\n");
    // }
    
    // for multiple groups
    int flag = 0;
    int count = 0;
    int *groups = CALLOC(int , m);

    for(i=0;i<m;i++){
        groups[i] = -1; // base values for uninitialized flags
    }

    for(i=0;i<m;i++){
        if (i+1 == m){
            if (minDim[i].position - minDim[i-1].position == 1){
                groups[flag] += 1;
            }
            else{
                count = 1;
                groups[flag] = count;
            }
        }
        if (minDim[i+1].position - minDim[i].position == 1){
            count++;
            groups[flag] = count;
        }
        else{
            count++;
            groups[flag] = count;
            count = 0;
            flag++;
        }
    }
    for(i=0;i<=flag;i++){
        if (groups[i] >= k){
            printf("TRUE\n");
            free(groups);
            free(minDim);
            freeHeap(minh);
            return 0;
        }
    }
    printf("FALSE\n");
    free(groups);
    free(minDim);
    freeHeap(minh);
    return 0;
}