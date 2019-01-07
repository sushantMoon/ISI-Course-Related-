#include "common.h"
#include "linkedlist.h"

Node *makeNode(void *data, size_t data_size){
    Node *n = MALLOC(Node, 1);
    n->data = malloc(data_size);
    n->next = NULL;
    n->data_size = data_size;
    memcpy(n->data, data, data_size);
    return n;
}

LinkedList *makeLinkedList(){
    LinkedList *ll = MALLOC(LinkedList, 1);
    ll->head = NULL;
    return ll;
}

void printIntLinkedList(LinkedList *ll){
    Node *p = ll->head;
    while(p != NULL){
        printf("%d ", *(int *)(p->data));
        p = p->next;
    }
    printf("\n");
}

void printCharLinkedList(LinkedList *ll){
    Node *p = ll->head;
    while(p != NULL){
        printf("%c ", *(char *)(p->data));
        p = p->next;
    }
    printf("\n");
}

void freeLinkedList(LinkedList *ll){
    Node* t;
    while(ll->head != NULL){
        t = ll->head;
        ll->head = ll->head->next;
        free(t);
    }
}

// this needs to be debugged
void insertElementsInNonDecreasingOrder(LinkedList *ll, void *data, size_t data_size){
    Node *n = makeNode(data, data_size);
    if (ll->head == NULL){
        ll->head = n;
    }
    else if (*(int *)(data) > *(int *)(ll->head->data)){
            n->next = ll->head; 
            ll->head = n;
        }
    else{
        Node *t = ll->head;
        while (t->next != NULL ){
            if (*(int *)(data) > *(int *)(t->next->data)){
                break;
            }
            else{
                t = t->next;
            }
        }
        n->next = t->next;
        t->next = n;
    }
}


void insertInOrder(LinkedList *ll, void *data, size_t data_size){
    // this is used for putting the nodes one after another , i.e appends the new node at the end 
    Node *n = makeNode(data, data_size);
    Node *t = ll->head;
    if (t == NULL){
        ll->head = n;
    }
    else{
        while(t->next != NULL){
            t = t->next;
        }
        t->next = n;
    }
}

void insertData(LinkedList *ll, void *data, size_t data_size){
    Node *n = makeNode(data, data_size);
    n->next = ll->head;
    ll->head = n;
}