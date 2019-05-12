/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 18 September, 2018
Program description: 

Given Pre Order, Post Order find the binary tree 
Assumptions : all the nodes are unique, all nodes are positive integers
(Sequential Binary Tree used)

Sample Input :
9
6 2 1 4 3 7 10 9 11
1 3 4 2 9 11 10 7 6

Sample Output:
Root : 6
Left child of 6 : 2
Right child of 6 : 7
Left child of 2 : 1
Right child of 2 : 4
Left child of 4 : 3
Left child of 7 : 10
Left child of 10 : 9
Right child of 10 : 11

Acknowledgements:
------------------------------------*/

#include "../generic/common.h"

void markVisited(int *pre, int* visited, int size, int value){
    // printf("Marking %d as visited\n", value);
    int i = 0;
    for (i=0;i<size;i++){
        if (pre[i] == value){
            visited[i] = 1;
            break;
        }
    }
}

int getParentForNextLevel(int *pre, int *visited, int size){
    int i;
    for (i=0;i<size;i++){
        if (visited[i] == 0){
            return pre[i-1];
        }
    }
    return -1;
}

int leftChild(int vparent, int *pre, int *visited, int size){
    int i=0;
    for(i=0;i<size;i++){
        if (pre[i] == vparent){
            if (visited[i+1] == 0)
                return pre[i+1];
        }
    }
    return -1;
}
int checkVisited(int *pre, int *visited, int value, int size){
    int i;
    for(i = 0; i < size; i++)
    {
        if (pre[i] == value)
            return visited[i];
    }
    return 1;
}

int rightChild(int vparent, int *post, int *pre, int *visited, int size){
    int i=0;
    for(i=0;i<size;i++){
        if (post[i] == vparent){
            if (checkVisited(pre, visited, post[i-1], size) == 0)
                return post[i-1];
        }
    }
    return -1;
}

int main()
{
    int size, i, flag = 0;
    int *pre, *post, *visited;
    printf("Enter the total number of nodes:\n");
    scanf("%d", &size);
    pre = MALLOC(int, size);
    post = MALLOC(int, size);
    visited = CALLOC(int, size);
    printf("Enter the nodes in pre order :\n");
    for(i = 0; i < size; i++)
    {
        scanf("%d", &pre[i]);
    }
    printf("Enter the nodes in post order :\n");
    for(i = 0; i < size; i++)
    {
        scanf("%d", &post[i]);
    }

    printf("Root : %d\n", pre[0]);
    markVisited(pre, visited, size, pre[0]);
    while(flag != 1){
        int vparent = getParentForNextLevel(pre, visited, size);
        if (vparent == -1){
            flag = 1;
            break;
        }
        else{
            int lchild = leftChild(vparent, pre, visited, size);
            if (lchild != -1){
                printf("Left child of %d : %d\n", vparent, lchild);
                markVisited(pre, visited, size, lchild);
            }
            int rchild = rightChild(vparent, post, pre, visited, size);
            if (rchild != -1){
                printf("Right child of %d : %d\n", vparent, rchild);
                markVisited(pre, visited, size, rchild);
            }
        }
        int count = 0;
        for(i=0;i<size;i++){
            count += visited[i];
        }
        if (count == size){
            flag = 1;
            break;
        }
    }
    return 0;
}
