/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 14 August, 2018
Program description: Linked List of Linked List
Acknowledgements:
------------------------------------*/ 

#include <stdio.h>
#include <stdlib.h>
#define MALLOC(type, n) (type *)malloc(sizeof(type)*n)


typedef struct node{
	int data;
	struct node* next;
}Node;

typedef struct linkedlist{
    Node* list;
    struct linkedlist* next;
}LinkedList;


int main(){
	int numList;
    printf("Enter the number of elements for Linked List of Linked List : ");
	scanf("%d", &numList);
	int i = 0;
    LinkedList *listHead = NULL;
    listHead = MALLOC(LinkedList, 1);
    LinkedList *listTail;
    listHead->list = NULL;
    listHead->next = NULL;
    listTail = listHead;

    for (i=0;i<numList;i++){
	    Node *head = NULL;
        head = MALLOC(Node, 1);
        head->data = -1;
        head->next = NULL;

        if (listTail->list == NULL){
            listTail->list = head;
        }
        else{
            LinkedList *lnode;
            lnode = MALLOC(LinkedList, 1);
            lnode->list = head;
            lnode->next = NULL;
            listTail->next = lnode;
            listTail = lnode;
        }
        
        Node *tail = head;
        printf("Enter the elements for the linked list no. %d (Enter -1 to end the input for this linked list): \n", i+1);
        while(1){
            int value;
            scanf("%d", &value);
            if (value != -1){
                if (tail->data == -1){
                    tail->data = value;
                }
                else{
                    Node *t;
                    t = MALLOC(Node, 1);
                    t->data = value;
                    t->next = NULL;
                    tail->next = t;
                    tail = t;
                }
            }
            else{
                break;
            }
        }
	}

    LinkedList *lTail = listHead;
    while(lTail != NULL){
        Node *tail;
        tail = lTail->list;
        while(tail != NULL){
            printf("%d ", tail->data);
            tail = tail->next;
        }
        lTail = lTail->next;
    }
    printf("\n");
    free(listHead);
	return 0;
}