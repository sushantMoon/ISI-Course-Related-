/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 18 September, 2018
Program description: 

1. Complete Binary Tree With Array with 0 based indexing
2. PreOrder Traversal of the Binary Tree
(Sequential Binary Tree used)

Acknowledgements:
------------------------------------*/

#include "../generic/common.h"

int parentID(int index){
    return (index-1)/2;
}

int rightChildID(int index){
    return 2*(index + 1);
}

int leftChildID(int index){
    return (2*index) + 1;
}

void preOrderTraversal(int *bt, int index, int size){
    if (index >= 0 && index < size){
        printf("%d ", bt[index]);
        preOrderTraversal(bt, leftChildID(index), size);
        preOrderTraversal(bt, rightChildID(index), size);
    }
}

int main()
{
    printf("Enter the total nodes: ");
    int size, i;
    scanf("%d", &size);
    int *bt = MALLOC(int, size);
    printf("Enter the elements of the array:\n");
    for(i=0;i<size;i++){
        scanf("%d", &bt[i]);
    }
    printf("Printing the Array as Binary Pre-Order Traversal\n");
    preOrderTraversal(bt, 0, size);
    printf("\n");
    return 0;
}
