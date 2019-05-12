/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 9 October, 2018
Program description:

Largest Element of the matrix
Compile using : ``` gcc -g -Wall cs1807-test3-prog1.c -o prog1 -lm ```

Acknowledgements:
------------------------------------*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MALLOC(type, n) (type *)malloc(sizeof(type)*n)
#define CALLOC(type, n) (type *)calloc(sizeof(type), n)
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define INTMIN -2147483648

int comparator_qsort(const void *a, const void *b){
    return *(int *)a - *(int *)b;
}

void largestInRow(int *d, int low, int high, int *output, int r, int c){
    if (low <= high){
        int mid = (int)((low+high)/2);
        if (mid == low){
            *output = d[mid];
        }
        else if (high - low == 1){
            *output = MAX(d[low], d[high]);
        }
        else if (high - low == 2){
            *output = MAX(d[low], MAX(d[low+1], d[high]));
        }
        else if ((d[mid] > d[mid-1]) && (d[mid] > d[mid+1])){
            *output = d[mid];
        }
        else{
            if ( (d[mid] > d[mid-1]) && (d[mid] < d[mid+1]) ){
                // mid is in between increasing sequence
                largestInRow(d, mid, high, output, r, c);
            }
            else if ( (d[mid] < d[mid-1]) && (d[mid] > d[mid+1]) ){
                // mid is in between decreasing sequence
                largestInRow(d, low, mid, output, r, c);
            }
        }
    }
}

int getLargestInMatrix(int **d, int r, int c){
    int i;
    int *RC = CALLOC(int, r);
    for(i=0;i<r;i++){
        largestInRow(d[i], 0, c-1, RC+i, r, c);
        printf("%d ", RC[i]);    
    }
    qsort(RC, r, sizeof(int), comparator_qsort);
    // for(i=0;i<r;i++){
    //     printf("%d ", RC[i]);    
    // }
    // printf("\n");
    return RC[r-1];
}



int main(int argc, char const *argv[])
{
    int r,c;
    scanf("%d %d", &r, &c);
    int i, j, k;

    int **m = CALLOC(int *, r);
    for(i = 0; i < r; i++){
        m[i] = CALLOC(int, c);
    }
    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
        {
            scanf("%d", &k);
            m[i][j] = k;
        }   
    }

    printf("\n%d\n", getLargestInMatrix(m, r, c));   // Order (R * (LOG(c) + LOG(r)) 
    return 0;
}
