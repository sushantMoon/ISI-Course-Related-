/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 14 August, 2018
Program description: insert in (array(done)/linkedlist(done)/array implementation of linkedlist(not done)) sorted order
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

int *insertInArray(int value, int *A, int size){
    int i;
    if (A[0] == -1){
        A[0] = value;
        return A;
    }
    for(i = 0; i < size; i++)
    {
        if (A[i] == -1){
            A[i] = value;
            break;
        }
        else if (A[i] > value){
            int j = size-1;
            while(j>i){
                A[j] = A[j-1];
                j--;
            }
            A[i] = value;
            break;
        } 
    }
    return A;
}

Node *insertInLinkedList(int value, Node *B){
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

int main(int argc, char *argv[]){
    int n = atoi(argv[1]);
    int *A;
    int i;
    A = MALLOC(int, n);
    
    for(i = 0; i < n; i++)
        A[i] = -1;
    
    Node *B = NULL;

    clock_t start = clock();
    for(i = 0; i < n; i++)
    {
        int value = rand()%10000;
        A = insertInArray(value, A, n);
    }
    clock_t end = clock();
    
    printf("Data in array: ");
    for(i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\t Total time Taken : %lf\n",((double)(end - start)) / CLOCKS_PER_SEC);

    start = clock();
    for(i = 0; i < n; i++)
    {
        int value = rand()%10000;
        B = insertInLinkedList(value, B);
    }
    end = clock();

    printf("Data in LinkedList: ");
    Node* tail = B;
    while(tail != NULL){
        printf("%d ", tail->data);
        tail = tail->next;
    }
    printf("\t Total time Taken : %lf\n",((double)(end - start)) / CLOCKS_PER_SEC);
    return 0;
}