/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 20 September, 2018
Program description:

Non-Recursive :
1. PreOrder
2. InOrder
3. PostOrder

Using Alternative implementation of BinaryTree and Stacks

Compile Using => `gcc -g -Wall cs1807-test2-prog2.c stack.c -o prog2`
Acknowledgements:
------------------------------------*/


#include "common.h"
#include "stack.h"

typedef struct treeNode{
    int d;
    int leftChild, rightChild;
    int parent;
    int visited;
}BTNODE;
// -1 at any value in the BTNODE signifies NULL

// Preorder Routine
// Routine 1
void printNodeAndGoLeft(Stack *s, int index, BTNODE* root){
    while(index != -1){
        printf("%d ", root[index].d);
        int *i = MALLOC(int, 1);
        i[0] = index;
        push(s, i);
        index = root[index].leftChild;
    }
}

// InOrder Routine
// Routine 2
void goLeft(Stack *s, int index, BTNODE* root){
    while(index != -1){
        int *i = MALLOC(int, 1);
        i[0] = index;
        push(s, i);
        index = root[index].leftChild;
    }
}
// Routine 3
void printNodeRightAndGoLeft(Stack *s, int index, BTNODE* root){
    printf("%d ", root[index].d);
    index = root[index].rightChild;
    goLeft(s, index, root);
}

int main()
{
    int totalNodes,i;
    scanf("%d", &totalNodes);
    
    BTNODE *root = MALLOC(BTNODE, totalNodes);
    // Numbering for the nodes are done based on level order, starting from left
    for(i=0; i<totalNodes ;i++){
        int d, l, r;
        scanf("%d %d %d", &d, &l, &r);
        root[i].d = d;
        if (l != -1){
            l -= 2;
            root[l].parent = i;
        }
        if (r != -1){
            r -= 2;
            root[r].parent = i;
        }
        root[i].leftChild = l;
        root[i].rightChild = r;
        root[i].visited = 0; 
    }
    
    // Routine For PreOrder
    Stack *nstack = newStack(sizeof(int));
    printNodeAndGoLeft(nstack, 0, root);
    while(isEmpty(nstack) != 1){
        int value;
        pop(nstack, &value);
        value = root[(int)value].rightChild;
        printNodeAndGoLeft(nstack, value, root);
    }
    printf("\n");
    freeStack(&nstack);

    //Routine for InOrder
    nstack = newStack(sizeof(int));
    goLeft(nstack, 0, root);
    while(isEmpty(nstack) != 1){
        int index;
        pop(nstack, &index);
        printNodeRightAndGoLeft(nstack, (int)index, root);
    }
    printf("\n");
    freeStack(&nstack);

    //Routine for PostOrder
    nstack = newStack(sizeof(int));
    goLeft(nstack, 0, root);
    while(isEmpty(nstack) != 1){
        int index;
        pop(nstack, &index);
        index = (int)index;
        if ( root[index].visited == 1 ){
            printf("%d ", root[index].d);
        }
        else if (root[index].rightChild != -1){
            int *i = MALLOC(int, 1);
            i[0] = index;
            push(nstack, i);
            root[index].visited = 1;
            goLeft(nstack, root[index].rightChild, root);
        }
        else{
            printf("%d ", root[index].d);
        }
    }
    printf("\n");
    freeStack(&nstack);
    // free(root);
    return 0;
}
