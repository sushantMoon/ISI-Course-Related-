/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 21 August, 2018
Program description: Possible Arrangement for the matrix formation 
Acknowledgements:
------------------------------------*/ 



#include <stdio.h>
#include <stdlib.h>
#define MALLOC(type, n) (type *)malloc(sizeof(type)*n)



int main()
{
    // Reading the data from the file

    char c[15];  // for stroing the name
    char *buffer;
    long int bsize;
    // printf("Enter the name of the file : ");
    scanf("%s", c);

    // Opening the fle in binary read mode
    FILE *fp = fopen(c, "rb");
    if (fp == NULL){
        printf("File Not Available\n");
        return 0;
    }

    // moving the pointer to the end of the file
    fseek(fp, 0, 2);

    // storing the size of the file;
    bsize = ftell(fp);

    // rewinding to the starting of the file
    rewind(fp);

    buffer = MALLOC(char, bsize);
    if (buffer == NULL){
        printf("Memory Allocation failed !!\n");
        return 0;
    }

    size_t result = fread(buffer, 1, bsize, fp);
    
    if (result != bsize) {
        printf("Reading Error !!\n");
        return 0;
    }
    fclose(fp);

    // Now all the data in sequence.txt file is stored in buffer char array
    
    // restructing the data
    int value = 0;
    int n,i,k=0,j=0;
    // fetching the size of the Array A
    while(buffer[k] != ' '){
        value = value*10 + (buffer[k] - '0');
        k++;
    }
    n = value;
    value = 0;
    k++;

    int *A;
    A = MALLOC(int, n);

    for (i=k;i<bsize;i++){
        if (buffer[i] == ' '){
            A[j] = value;
            j++;
            value = 0;
        }
        else {
            value = value*10 + (buffer[i] - '0');
        }
    }
    A[j] = value;
    
    // checking the data
    // for(i=0;i<n;i++)
    //     printf("%d ",A[i]);
    // printf("\n");

    // Logic for printing the matrices
    // printf("The Matrices are :\n");
    for(i=1;i<=n;i++){
        if (n%i == 0){
            // printf("Matrix of size %d x %d\n", i, n/i);
            int k,j;
            for (k=0;k<i;k++){
                for (j=0;j<n/i;j++){
                    printf("%d ",A[k*(n/i) +j]);
                }
                printf("\n");
            }
            printf("\n");
        }
    }
    return 0;
}
