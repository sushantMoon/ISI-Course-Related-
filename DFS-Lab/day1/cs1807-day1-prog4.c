/*-----------------------------------
Name: Sushant Sharad Moon
Roll number: MTC1807
Date: 20 July, 2018
Program description: IMplementations of Union , Intersection , Powerset 
Acknowledgements:
------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

void a_union_b(int *a, int *b, int size_a, int size_b){
    int c[200];
    int k = 0;
    for(int i=0;i<size_a;i++){
        c[k] = a[i];
        k++;
    }
    for(int i=0;i<size_b;i++){
        int flag = 0;
        for(int j=0;j<k;j++){
            if (b[i]==c[j]){
                flag = 1;
                break;
            }
        }
        if (flag == 0){
            c[k] = b[i];
            k++;
        }
    }
    for(int j=0;j<k;j++){
        printf("%d ",c[j]);
    }
    printf("\n");
}

void a_intersection_b(int *a, int *b, int size_a, int size_b){
    int c[100];
    int k = 0;
    for(int i=0;i<size_a;i++){
        int flag = 0;
        for(int j=0;j<size_b;j++)
            if (a[i] == b[j]){
                flag = 1;
                break;
            }
        if (flag == 1){
            c[k] = a[i];
            k++;
        }
    }
    for(int j=0;j<k;j++){
        printf("%d ",c[j]);
    }
    printf("\n");
}

int a_subset_b(int *a, int *b, int size_a, int size_b){
    for(int i=0;i<size_a;i++){
        int flag = 0;
        for(int j=0;j<size_b;j++)
            if (a[i] == b[j]){
                flag = 1;
                break;
            }
        if (flag == 0){
            // printf("A is not a Subset of B");
            return 0;
        }
    }
    // printf("A is subset of B");
    return 1;
}

void powerset_a(int *a, int size_a){
    unsigned int size_powerset;
    if (size_a >= 1)
    {
        size_powerset = 2; 
        for(int i=0; i<size_a-1;i++){
            size_powerset = 2*size_powerset;
        }
    }
    
    for(int i = 0; i < size_powerset; i++)
    {
        int size = i;
        printf("Set : [ ");
        for(int j=0; j<size_a; j++){
            if (size%2 == 1){
                printf("%d ", a[j]);
            }
            size = size/2;
        }
        printf("]\n");
    }
}

int main()
{
    int a[100], b[100];
    int size_a, size_b;
    printf("Enter the number of elements in the array A (max is 100):\n");
    scanf("%d", &size_a);
    printf("Enter the elements of the int array A:\n");
    for(int i=0; i<size_a; i++){
        scanf("%d", &a[i]);
    }
    printf("Enter the number of elements in the array B (max is 100):\n");
    scanf("%d", &size_b);
    printf("Enter the elements of the int array B:\n");
    for(int i=0; i<size_b; i++){
        scanf("%d", &b[i]);
    }
    printf("A union B : \n");
    a_union_b(a, b, size_a, size_b);
    printf("A intersection B : \n");
    a_intersection_b(a, b, size_a, size_b);
    printf("Is A subset of B : \n");
    int value = a_subset_b(a, b, size_a, size_b);
    if (value ==1)
        printf("True\n");
    else
        printf("False\n");
    printf("PowerSet of A:\n");
    powerset_a(a, size_a);
    return 0;
}
