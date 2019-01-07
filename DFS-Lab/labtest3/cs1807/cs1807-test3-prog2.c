/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 9 October, 2018
Program description: 

Compile using :
```
gcc -g -Wall cs1807-test3-prog2.c -o prog2 -lm
```

Acknowledgements:
------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#define MALLOC(type, size) (type *)malloc(sizeof(type)*size)
#define CALLOC(type, size) (type *)calloc(sizeof(type), size)

typedef struct {
    int d;
    int eldest_child, next_sibling, parent_index, level;
}TREENODE;

void findParent(TREENODE *tree, int index, int* parent, int n){
    int j = 0;
    parent[j] = index;
    j++;
    while(tree[index].parent_index != 0){
        parent[j] = tree[index].parent_index;
        j++;
        index = tree[index].parent_index;
    }
}

void findLowestCommonParent(int *parent1, int *parent2, int n){
    int i = 0, j = 0;
    
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if (parent1[i] == parent2[j]){
                printf("%d\n", parent1[i]);
                return;
            }
        }
    }
    printf("0\n");
}

int main(int argc, char const *argv[])
{
    //  write for input intake and output printing
    if (argc < 5){
        printf("Format Should be : ./prog2 <input_filename> <output_filename> n1 n2\n");
    }
    FILE *ip, *op;
    ip = fopen(argv[1], "r");
    if (ip == NULL){
        printf("Input File Not Available\n");
        return 0;
    }
    op = fopen(argv[2], "w"); // to clear out the file if any present
    fclose(op);
    op = fopen(argv[2], "a");
    if (op == NULL){
        printf("Input File Not Available\n");
        return 0;
    }

    int n;
    int i, d, l, r;
    fscanf(ip, "%d", &n);
    TREENODE *tree = CALLOC(TREENODE, n);
    for(i=0;i<n;i++){
        tree[i].eldest_child = -1;
        tree[i].next_sibling = -1;
        tree[i].level = -1;
        tree[i].parent_index = -1;
    }
    for(i=0;i<n;i++){
        fscanf(ip, "%d %d %d", &d, &l, &r);
        tree[i].d = d;
        if (i == 0){
            tree[i].level = 0;
            tree[i].parent_index = -1;
            tree[i].next_sibling = -1;
        }
        else{
            tree[i].level = tree[tree[i].parent_index].level + 1;
        }
        if ((l != -1) && (r != -1)){
            // i's 
            tree[i].eldest_child = l;
            // left child's
            tree[l].parent_index = i;
            tree[l].next_sibling = r;
            // tree[l].eldest_child = -1;
            tree[l].level = tree[i].level + 1;
            // right child's
            tree[r].parent_index = i;
            tree[r].next_sibling = -1;
            // tree[r].eldest_child = -1;
            tree[r].level = tree[i].level + 1;
        }
        else if ((l != -1) && (r == -1)){
            // only left child
            // i's 
            tree[i].eldest_child = l;
            // left child's
            tree[l].parent_index = i;
            tree[l].next_sibling = -1;
            // tree[l].eldest_child = -1;
            tree[l].level = tree[i].level + 1;
        }
        else if ((l == -1) && (r != -1)){
            // only right child
            // i's 
            tree[i].eldest_child = r;
            // right child
            tree[r].parent_index = i;
            tree[r].next_sibling = -1;
            // tree[r].eldest_child = -1;
            tree[r].level = tree[i].level + 1;
        }
        else if ((l == -1) && (r == -1)){
            tree[i].eldest_child = -1;
            // tree[i].next_sibling = -1;
        }
    }

    fprintf(op, "%d\n", n);
    for(i=0;i<n;i++){
        fprintf(op, "%d %d %d %d %d\n", tree[i].d, tree[i].eldest_child, tree[i].next_sibling, tree[i].parent_index, tree[i].level);
        // fprintf(op, "data:%d eldestC:%d nextS:%d parentI:%d level:%d\n", tree[i].d, tree[i].eldest_child, tree[i].next_sibling, tree[i].parent_index, tree[i].level);
    }
    fclose(ip);
    fclose(op);
    // printf("%d %d",atoi(argv[3]),atoi(argv[4]));
    int *parent1 = CALLOC(int, n);
    findParent(tree, atoi(argv[3]), parent1, n);
    int *parent2 = CALLOC(int, n);
    findParent(tree, atoi(argv[4]), parent2, n);
    // for(i=0;i<n;i++){
    //     printf("%d ", parent1[i]);
    // }
    // printf("\n");
    // for(i=0;i<n;i++){
    //     printf("%d ", parent2[i]);
    // }
    // printf("\n");
    findLowestCommonParent(parent1,parent2, n);
    return 0;
}
