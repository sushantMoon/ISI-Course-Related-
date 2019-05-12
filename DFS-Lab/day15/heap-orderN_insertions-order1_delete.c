/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 13 Sepetember, 2018
Program description: 

heap with insertion order N and delete order 1

MAX HEAP with Linked List with ordered insertions in order N

Command for Compilation:
```
gcc -g -Wall ../generic/linkedlist.c heap-orderN_insertions-order1_delete.c -o heap -lm
```

Acknowledgements:
------------------------------------*/


#include "../generic/common.h"
#include "../generic/linkedlist.h"

typedef struct PriorityQueue{
    LinkedList *ll;
}PriorityQueue;

PriorityQueue* initializeQueue(){
    PriorityQueue *pq = MALLOC(PriorityQueue, 1);
    pq->ll = makeLinkedList();
    return pq;
}

void printPriorityQueue(PriorityQueue *pq){
    printIntLinkedList(pq->ll);
}

void freePriorityQueue(PriorityQueue *pq){
    freeLinkedList(pq->ll);
    free(pq);
}

// routines for insertion order N delete order 1
// MAXHEAP
void insertOrderedElement(PriorityQueue *pq, int value){
    insertElementsInNonDecreasingOrder(pq->ll, &value, sizeof(int));
}

void insertElement(PriorityQueue *pq, int value){
    insertData(pq->ll, &value, sizeof(int));
}

Node *extractMax(PriorityQueue *pq){
    Node *n = pq->ll->head;
    pq->ll->head = pq->ll->head->next;
    return n;
}

int main(){
    PriorityQueue *pq, *pq2;
    pq = initializeQueue();
    pq2 = initializeQueue();
    int i;
    srand(time(NULL));
    for(i=0;i<10;i++){
        insertOrderedElement(pq, rand()%100);
        insertElement(pq2, rand()%100);
    }

    printf("Ordered Insert :\n");
    printPriorityQueue(pq);
    Node* n = extractMax(pq);
    printf("%d\n", *(int *)n->data);
    printPriorityQueue(pq);

    n = extractMax(pq);
    printf("%d\n", *(int *)n->data);
    printPriorityQueue(pq);

    // n = extractMax(pq);
    // printf("%d\n", *(int *)n->data);
    // printPriorityQueue(pq);
    // n = extractMax(pq);
    // printf("%d\n", *(int *)n->data);
    // printPriorityQueue(pq);

    // printf("Normal Insert :\n");
    // printPriorityQueue(pq2);
    // n = extractMax(pq2);
    // printf("%d\n", *(int *)n->data);
    // printPriorityQueue(pq2);

    // n = extractMax(pq2);
    // printf("%d\n", *(int *)n->data);
    // printPriorityQueue(pq2);

    // n = extractMax(pq2);
    // printf("%d\n", *(int *)n->data);
    // printPriorityQueue(pq2);
    // n = extractMax(pq2);
    // printf("%d\n", *(int *)n->data);
    // printPriorityQueue(pq2);


    freePriorityQueue(pq);
    freePriorityQueue(pq2);
    return 0;
}