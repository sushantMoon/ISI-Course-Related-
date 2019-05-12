/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 19 September, 2018
Program description: 

1. Lowest Common Ancestor of two int nodes
(Alternative Implemetation of Binary Tree used)

Acknowledgements:
------------------------------------*/

#include "../generic/common.h"

typedef struct treeNode{
    int d;
    int leftChild, rightChild;
    int parent; 
}BTNODE;
// -1 at any value in the BTNODE signifies NULL

int main()
{
    printf("Enter the number of nodes in the tree: \n");
    int totalNodes,i, j;
    scanf("%d", &totalNodes);
    
    BTNODE *root = MALLOC(BTNODE, totalNodes);
    // Numbering for the nodes are done based on level order, starting from left
    printf("Enter the data Nodes\n");
    for(i=0; i<totalNodes ;i++){
        int d, l, r;
        printf("Enter the data for Node %d:", i);
        scanf("%d", &d);
        printf("Enter the LeftNode Number for Node %d (enter -1 for NULL):", i);
        scanf("%d", &l);
        printf("Enter the RightNode Number for Node %d (enter -1 for NULL):", i);
        scanf("%d", &r);
        root[i].d = d;
        root[i].leftChild = l;
        root[i].rightChild = r;
        root[l].parent = i;
        root[r].parent = i;
    }
    int t = 0;
    
    while(t != -1){
        printf("Enter the two indices for which lowest common ancestor is needed:\n");
        int index1, index2, index;
        printf("Enter the first index:\n");
        scanf("%d", &index1);
        printf("Enter the second index:\n");
        scanf("%d", &index2);


        // Finding the lowest common ancestor 
        int *path1 = CALLOC(int, totalNodes);
        int *path2 = CALLOC(int, totalNodes);

        // populating path of first index to root
        index = index1;
        i = 0;
        while(index != 0){
            path1[i] = index;
            index = root[index].parent;
            i++;
        }

        // populating path of second index to root
        index = index2;
        i = 0;
        while(index != 0){
            path2[i] = index;
            index = root[index].parent;
            i++;
        }

        index = 0;
        for(i = 0; i < totalNodes; i++){
            for(j = 0; j < totalNodes; j++){
                if (path1[i] == path2[j]){
                    index = i;
                    break;
                }
            }
            if (path1[i] == path2[j]){
                index = i;
                break;
            }
        }
        
        printf("Common Ancestor Node is for Node %d and Node %d is Node %d\n", index1, index2, path1[index]);
        printf("Enter -1 to end, else 0 to continue: ");
        scanf("%d", &t);
        free(path1);
        free(path2);
    }
    free(root);
    // this is causing the problem ...check with sir
    return 0;
}
