/*-----------------------------------
Name: Sushant Sharad Moon
Roll number: MTC1807
Date: 20 July, 2018
Program description: from the list of numbers, if the list if non decreasing the print the number of distinct numbers, else print -1
Acknowledgements:
------------------------------------*/
#include <stdio.h>

int uniquify(int *a, int size){
    int distinct, prev;
    if (size==0){
        return 0;
    }
    else{
        distinct = 0;
    }
    for(int i=0;i<size;i++){
        if (i==0)
            prev = a[0],distinct++;
        if (prev > a[i])
            return -1;
        if (prev < a[i])
            distinct += 1;
        prev = a[i];
    }
    return distinct;
}

int main()
{
    int a[100];
    int size;
    printf("Enter the number of elements in the array(max is 100):\n");
    scanf("%d", &size);
    printf("Enter the elements of the int array:\n");
    for(int i=0; i<size; i++){
        scanf("%d", &a[i]);
    }
    printf("Number of distinct numbers are: %d\n",uniquify(a, size));
    return 0;
}
