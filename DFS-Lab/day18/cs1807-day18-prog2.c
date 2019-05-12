/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 25 Sepetember, 2018
Program description: 

Checking if the list 2 is sublist of list 1
```
gcc -g -Wall ../generic/linkedlist.c cs1807-day18-prog2.c -o prog2
```
Acknowledgements:

References
http://www.java2s.com/Code/C/Console/Usefgetstoreadstringfromstandardinput.htm
https://stackoverflow.com/questions/26718332/c-read-line-from-stdin-with-fgets-in-function
https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
https://os.mbed.com/questions/2910/Convert-string-to-int/
------------------------------------*/
#include "../generic/common.h"
#include "../generic/linkedlist.h"

#define MAX_SIZE 4096

int checkIfSubList(LinkedList *l1, LinkedList *l2){
    // l2 should be smaller than l1
    // checks if n2 is sublist of n1
    // returns -1 if false
    // return 1 if true
    Node *n1, *n2;
    n1 = l1->head;
    n2 = l2->head;
    while(1){
        if (n1 == NULL){
            return -1;
        }
        else if ( *((int *)(n1->data)) > *((int *)(n2->data)) ){
            return -1;
        }
        else if ( *((int *)(n1->data)) == *((int *)(n2->data)) ){
            break;
        }
        n1 = n1->next;
    }
    

    if( *((int *)(n1->data)) == *((int *)(n2->data)) ) {
        while( n2 != NULL ){
            // printf("%d %d\n", *((int *)(n1->data)) , *((int *)(n2->data)));
            if (n1 == NULL && n2 != NULL){
                return -1;
            }
            else if ( *((int *)(n1->data)) != *((int *)(n2->data)) ){
                return -1;
            }
            n1 = n1->next;
            n2 = n2->next;
        }
    }
    if (n2 == NULL){
       return 1;
    }
    return -1;
}

int main(){
    char *List;
    char *token;
    int length;

    LinkedList *l1 = makeLinkedList();
    LinkedList *l2 = makeLinkedList();

    printf("Enter the values of the data nodes in the list 1 starting form the head space seperated:\n");
    // This Routine reads line from stdin and breaks it using token " " gives int at the end in while loop
    List = CALLOC(char, MAX_SIZE);
    fgets(List, MAX_SIZE, stdin);
    length = strlen(List);
    if ( (length == (MAX_SIZE-1)) && (List[length-1] != '\n') )
    {
        printf("Error, line overeached buffer!\n");
        return 1;
    }
    if (List[length-1]=='\n')
    {
        List[length-1]='\0';
    }
    token = strtok(List, " ");
    while(token != NULL){
        int *k= MALLOC(int, sizeof(int));
        *k = atoi(token);
        insertInOrder(l1, k, sizeof(int));
        // printf("%d\n", atoi(token));
        token = strtok(NULL, " ");
    }
    free(List);
    
    printf("Enter the values of the data nodes in the list 2 starting form the head :\n");
    List = CALLOC(char, MAX_SIZE);
    fgets(List, MAX_SIZE, stdin);
    length = strlen(List);
    if ( (length == (MAX_SIZE-1)) && (List[length-1] != '\n') )
    {
        printf("Error, line overeached buffer!\n");
        return 1;
    }
    if (List[length-1]=='\n')
    {
        List[length-1]='\0';
    }
    token = strtok(List, " ");
    while(token != NULL){
        int *k= MALLOC(int, sizeof(int));
        *k = atoi(token);
        insertInOrder(l2, k, sizeof(int));
        // printf("%d\n", atoi(token));
        token = strtok(NULL, " ");
    }
    free(List);

    // printIntLinkedList(l1);
    // printIntLinkedList(l2);

    // checking if list 2 is sublist of list 1
    printf("List2 is %ssublist of List1\n", ((checkIfSubList(l1, l2) == 1)?"":"not "));
}