/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 21 August, 2018
Program description: Rotating the Matrix at 45 degree angle 
Acknowledgements:
------------------------------------*/ 


#include <stdio.h>
#include <stdlib.h>
#define MALLOC(type, n) (type *)malloc(sizeof(type)*n)


int main()
{
    int n;
    // printf("Enter the n for nxn Matrix: ");
    scanf("%d", &n);
    int **A, i, j;
    A = MALLOC(int *, n);
    if (A == NULL){
        printf("Memory Allocation failed !!\n");
        return 0;
    }
    for(i=0;i<n;i++){
        A[i] = MALLOC(int, n);
        if (A[i] == NULL){
            printf("Memory Allocation failed !!\n");
            return 0;
        }
    }

    for(i = 0; i < n; i++)
    {
        for(j=0;j<n;j++){
            scanf("%d",&A[i][j]);
        }
    }
    
    // Printing the Matrix
    // printf("The Matrix is: \n");
    // for(i = 0; i < n; i++)
    // {
    //     for(j = 0; j < n; j++)
    //     {
    //         printf("%d ", A[i][j]);
    //     }
    //     printf("\n");
    // }
    
    int ROWS = 0, COLS = 1;
    int col, row;

    // printing the upper triangle
    for( i=0; i<n; i++){
        col=0;
        row=ROWS;
        ROWS++;
        for(j=0;j<n-i-1;j++){
            printf(" ");
        }
        do{
            printf("%d ", A[row][col]);
            row--;
            col++;
        } while (col >=0 && col < n && row < n && row >= 0);
        printf("\n");
    }
    
    // printing the lower triangle
    for( i=0; i<n-1; i++)
    {
        row=n-1;
        col=COLS;
        COLS++;
        for(j=0;j<=i;j++){
            printf(" ");
        }
        do{
            printf("%d ", A[row][col]);
            row--;
            col++;
        } while (col >=0 && col < n && row < n && row >= 0);
        printf("\n");
    }
    return 0;
}


