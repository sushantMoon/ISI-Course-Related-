/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 14 August, 2018
Program description: Closest larger value from the value at ith position 
Acknowledgements:
------------------------------------*/ 


#include <stdio.h>
#include <stdlib.h>
#define MALLOC(type, n) (type *)malloc(sizeof(type)*n)


typedef struct node{
	int data;
	struct node* next;
	struct node* prev;
}Node;

Node *insertDoubleLinkedList(int value ,Node *B){
    Node* t;
    t = MALLOC(Node, 1);
    t->data = value;
    t->next = NULL;
    t->prev = NULL;
    if (B == NULL){
        return t;
    }
    else{
        Node *m;
        m = B;
        while(m->next != NULL){
            m = m->next;
        }
        m->next = t;
        t->prev = m;
    }
    return B;
}


int main()
{
    Node *B = NULL;
    int n, i, position;
    printf("Enter the Size of Linked List : ");
    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        int value = rand()%10000;
        B = insertDoubleLinkedList(value, B);
    }

    printf("Data in LinkedList: ");
    Node* tail = B;
    while(tail != NULL){
        printf("%d ", tail->data);
        tail = tail->next;
        if (tail != NULL){
            printf("<=> ");
        }
    }
    printf("\n");

    printf("Enter the ith Position (value should be less than %d): ", n);
    scanf("%d", &position);

    if (position < n){
        int j=1, value;
        Node *h=B, *prev, *next;
        while(j<position){
            h = h->next;
            j++;
        }
        value = h->data;
        prev = h;
        next = h;
        while(1){
            if ((prev != NULL) && (prev->data > value)){
                printf("The Closest larger value of %d is %d\n", value, prev->data);
                break;
            }
            if ((next != NULL) && (next->data > value)){
                printf("The Closest larger value of %d is %d\n", value, next->data);
                break;
            }
            if (next != NULL) {
                next = next->next;
            }
            if (prev != NULL) {
                prev = prev->prev;
            }
            if (next == NULL && prev == NULL){
                printf("No Larger value present!!\n");
                break;
            }
        }
    }
    else{
        printf("Invalid Positon value\n");
        return 1;
    }
    return 0;
}
