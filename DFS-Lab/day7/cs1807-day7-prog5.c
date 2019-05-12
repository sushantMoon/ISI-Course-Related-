/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 10 August, 2018
Program description: Subset Sum (part1 is done part 2 and part 3 questions are not clear hence left)
Acknowledgements:
------------------------------------*/  

#include <stdio.h>
#include <stdlib.h>
#define MALLOC(type, size) (type *)malloc(sizeof(type)*size)


int fill(int *A){
    int n,i;
    printf("What is the size of A: ");
    scanf("%d", &n);
    A = MALLOC(int, n);
    printf("Enter the elements of A one after the other (press enter after each element): \n");
    for(i=0;i<n;i++){
        scanf("%d", &A[i]);
    }
    return n;
}

void custom_algo_subset_sum(int *A, int n, int s){
    int i;
    int limit = 1<<(n-1);
    for (i=0;i<=limit;i++){
        // printf("%d \n", i);
        if ((s & i) > 0 ){
            s -= i;
            if (s == 0){
                printf("Subset Sum is possible using the custom algo!!\n");
                break;
            }
        }
        if (s <= 0){
            break;
        }
        // printf("S = %d\n", s);
    }
    if (s>0){
        printf("Subset Sum is not possible using the custom algo!!\n");
    }
}


int main()
{
    int *A = NULL;
    int n,s;
    n = fill(A);
    printf("Enter the number (required to check for subset) : ");
    scanf("%d", &s);
    custom_algo_subset_sum(A, n, s);

    return 0;
}

