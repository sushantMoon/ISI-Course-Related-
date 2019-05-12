/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 14 August, 2018
Program description: Merge two sorted Linked List as generted by prog1 
Acknowledgements:
------------------------------------*/ 


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MALLOC(type, n) (type *)malloc(sizeof(type)*n)


typedef struct node{
	int data;
	struct node* next;
}Node;


Node *insertInSortedOrderInLinkedList(int value, Node *B){
    Node *n = MALLOC(Node, 1);
    n->data = value;
    n->next = NULL;
    Node *t = B;
    if (B == NULL){
        return n;
    }
    else if(t->next == NULL){
        if (t->data > value){
            n->next = t;
            B = n;
            return B;
        }
        else{
            t->next = n;
            return B;
        }
    }
    while(t->next != NULL){
        if (B->data > value){
            n->next = B;
            B = n;
            return B;
        }
        else if ((t->data < value) && (t->next->data > value)){
            Node *p;
            p = t->next;
            t->next = n;
            n->next = p;
            return B;
        }
        t = t->next;
    }
    t->next = n;
    return B;
}

Node *merge(Node *B, Node* C){
    Node *l1 = B, *l2 = C, *l3 = NULL;
    while(l1 != NULL){
        l3 = insertInSortedOrderInLinkedList(l1->data, l3);
        l1 = l1->next;
    }
    while(l2 != NULL){
        l3 = insertInSortedOrderInLinkedList(l2->data, l3);
        l2 = l2->next;
    }
    return l3;
}

int main(){
    int n1, n2,i;
    printf("Enter the Size of First Linked List : ");
    scanf("%d", &n1);
    printf("Enter the Size of Second Linked List : ");
    scanf("%d", &n2);    
    Node *B = NULL;
    Node *C = NULL;
    Node *D = NULL;

    for(i = 0; i < n1; i++)
    {
        int value = rand()%10000;
        B = insertInSortedOrderInLinkedList(value, B);
    }
    for(i = 0; i < n2; i++)
    {
        int value = rand()%10000;
        C = insertInSortedOrderInLinkedList(value, C);
    }

    D = merge(B,C);
    printf("Data in First LinkedList: ");
    Node* tail = B;
    while(tail != NULL){
        printf("%d ", tail->data);
        tail = tail->next;
    }
    printf("\n");
    
    printf("Data in Second LinkedList: ");
    tail = C;
    while(tail != NULL){
        printf("%d ", tail->data);
        tail = tail->next;
    }
    printf("\n");

    printf("Data in Merged LinkedList: ");
    tail = D;
    while(tail != NULL){
        printf("%d ", tail->data);
        tail = tail->next;
    }
    printf("\n");
    return 0;
}