/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 27 July, 2018
Program description: Program with pointer to structure pointers
Acknowledgements:
------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define MALLOC(type, size) (type *)malloc(sizeof(type)*size)


struct item
{
    int value;
    struct item * next;
};

int main()
{

    int n,m,i,j;
    printf("Enter the number of Linked Lists that are needed :\n");
    scanf("%d", &m);

    printf("Enter the size of the %d Linked Lists :\n",m);
    scanf("%d", &n);

    struct item *linked_list[m];
    struct item *head[m];
    struct item *pointer;

    for(j=0; j<m; j++){
        printf("Enter the elements of the linked list %d one after the another:\n", j+1);
        for(i = 0; i < n; i++)
        {
            if (i==0)
                {
                    linked_list[j] = MALLOC(struct item, 1);
                    head[j] = linked_list[j];
                    pointer = linked_list[j];
                }
            else{
                (*pointer).next = MALLOC(struct item, 1);
                pointer = (*pointer).next;
            }
            scanf("%d",&((*pointer).value));
            (*pointer).next = NULL;
        }
    }
    
    for(j = 0; j < m; j++)
    {
        printf("The elements in the Linked List %d are :\n", j+1);
        linked_list[j] = head[j];
        pointer = linked_list[j];
        while(pointer != NULL)
        {
            printf("%d ", (*pointer).value);
            pointer = (*pointer).next;
        }
        printf("\n");
    }
    return 0;
}
