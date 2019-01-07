/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 24 July, 2018
Program description: Spearman's Rank Corelation Coefficient
Acknowledgements:  
------------------------------------*/


#include <stdio.h>
#include <stdlib.h>

int rank(float a, float *b, int N){
    // Calculates the rank of an element in an array
    int count = 0;
    
    for(int i = 0; i < N; i++)
    {
        if (b[i] > a){
            count += 1;
        }
    }
    return count+1;
}

int main(){
    int n;
    printf("Enter the size of sets:");
    scanf("%d",&n);

    float *a;
    a = (float*)malloc(sizeof(float)*n);
    printf("Enter %d elements in set A:\n",n);
    for(int i = 0; i < n; i++)
    {
        scanf("%f",&a[i]);
    }
    
    float *b;
    b = (float*)malloc(sizeof(int)*n);
    printf("Enter %d elements in set B:\n",n);
    for(int i = 0; i < n; i++)
    {
        scanf("%f",&b[i]);
    }

    float delta_square = 0;
    for(int i = 0; i < n; i++)
    {
        int diff = rank(a[i],a, n) - rank(b[i], b, n);
        delta_square += (diff*diff);
    }
    // printf("%f\n",delta_square);
    // printf("%d\n",n*(n*n -1));
    // printf("%f\n",(6*delta_square) / (n*(n*n -1)));
    
    float coefficient = 1 - ( (6*delta_square) / (n*(n*n -1)) );

    printf("Spearman's Rank Corelation Coefficient = %f\n", coefficient);
    return 0;
}