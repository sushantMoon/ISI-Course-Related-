#ifndef _G_LINKEDLIST_H_
#define _G_LINKEDLIST_H_

typedef struct Node{
    void *data;
    size_t data_size;
    struct Node *next;
}Node;

typedef struct LinkedList{
    Node *head;
}LinkedList;

Node *makeNode(void *data, size_t data_size);
LinkedList *makeLinkedList();
void printIntLinkedList(LinkedList *ll);
void printCharLinkedList(LinkedList *ll);
void freeLinkedList(LinkedList *ll);
void insertElementsInNonDecreasingOrder(LinkedList *ll, void *data, size_t data_size);
void insertData(LinkedList *ll, void *data, size_t data_size);
void insertInOrder(LinkedList *ll, void *data, size_t data_size);

#endif  // _G_LINKEDLIST_H_


