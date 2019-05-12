#include "common.h"
#include "stack.h"
#include "linkedlist.h"

int main()
{
    int k;

    // INT
    printf("Stack for int\n");
    Stack *intStack = newStack(sizeof(int));
    int m;
    printf("Pushing ");
    for(k=0;k<8;k++){
        push(intStack, &k);
        printf("%d ", k);
    }
    printf("\n");
    printf("Is stack empty : %s\n", isEmpty(intStack)?"yes":"no");
    
    printf("Poping ");
    for(k=0;k<8;k++){
        pop(intStack, &m);
        printf("%d ", (int)m);
    }
    printf("\n");
    printf("Is stack empty : %s\n", isEmpty(intStack)?"yes":"no");
    freeStack(&intStack);

    // Nodes
    printf("Nodes as defined in linkedlist.h in the Stack\n");
    Stack *nodeStack = newStack(sizeof(Node));
    
    printf("Pushing \n");
    for(k=0;k<20;k++){
        Node i;
        i.data = MALLOC(int, 1);
        *(int *)(i.data) = k;
        push(nodeStack, &i);
        // printf("Pushed : %d\n", *(int *)i.data);
        printf("%d ", *(int *)i.data);
    }
    printf("\n");
    printf("Is stack empty : %s\n", isEmpty(nodeStack)?"yes":"no");
    

    printf("Poping \n");
    while((int)nodeStack->num_elements != 0){
        Node i;
        pop(nodeStack, &i);
        // printf("Poped : %d\n", *(int *)(i.data));
        printf("%d ", *(int *)(i.data));
    }

    printf("\n");
    printf("Is stack empty : %s\n", isEmpty(nodeStack)?"yes":"no");
    freeStack(&nodeStack);


    return 0;
}