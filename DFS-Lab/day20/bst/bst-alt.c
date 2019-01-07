#include "common.h"
#include "bst-alt.h"
#include <time.h>

void insert(TREE *tree, int *rootptr, int d) {
    int root = *rootptr, next;

    if (root == -1) {
        assert(tree->num_nodes < tree->max_nodes);
        if (tree->num_nodes == tree->free_list){
            next = tree->num_nodes;
            tree->free_list++;
        }
        else{
            next = tree->free_list;
            tree->free_list = tree->nodelist[tree->free_list].left;
        }
        tree->num_nodes++;
        tree->nodelist[next].data = d;
        tree->nodelist[next].left = tree->nodelist[next].right = -1;
        *rootptr = next;
    }

    else if (d < tree->nodelist[root].data)
        insert(tree, &(tree->nodelist[root].left), d);
    else if (d > tree->nodelist[root].data)
        insert(tree, &(tree->nodelist[root].right), d);
    return;
}

void delete(TREE *tree, int root,  int d) {
    int successor_index = -1;

    assert(tree != NULL);
    if (tree->nodelist == NULL) return;

    if (d < tree->nodelist[root].data){
        delete(tree, tree->nodelist[root].left, d);
    }
    else if (d > tree->nodelist[root].data){
        delete(tree, tree->nodelist[root].right, d);
    }
    else {
        if (tree->nodelist[root].left == -1 && tree->nodelist[root].right == -1) {
            /* Case I: leaf, just delete */
            tree->nodelist[root].data = -1;
            tree->nodelist[root].left = tree->free_list;
            tree->nodelist[root].right = -1;
            tree->free_list = root;
            return;
        }
        else{
            /* Case II: only one child */
            if (tree->nodelist[root].left == -1){
                successor_index = tree->nodelist[root].right;
                tree->nodelist[root].data = tree->nodelist[successor_index].data;
                tree->nodelist[root].left = tree->nodelist[successor_index].left;
                tree->nodelist[root].right = tree->nodelist[successor_index].right;
            }
            else if (tree->nodelist[root].right == -1) {
                successor_index = tree->nodelist[root].left;
                tree->nodelist[root].data = tree->nodelist[successor_index].data;
                tree->nodelist[root].left = tree->nodelist[successor_index].left;
                tree->nodelist[root].right = tree->nodelist[successor_index].right;
            }
            else if(tree->nodelist[root].left != -1 && tree->nodelist[root].right != -1){
                /* Case III: both sub-trees present */
                successor_index = detach_successor(tree, root);
                tree->nodelist[root].data = tree->nodelist[successor_index].data;
            }
            if (successor_index != -1){
                tree->nodelist[successor_index].data = -1;
                tree->nodelist[successor_index].left = tree->free_list;
                tree->nodelist[successor_index].right = -1;
                tree->free_list = successor_index;
                tree->num_nodes--;
                return;
            }
        }
    }
    return;
}



int main(int ac, char *av[])
{
    int N, i, SIZE;
    int *data;
    // NODE *nodeptr;
    TREE tree;

    if (ac != 2)
        ERR_MESG("Usage: bst <number>");
    N = atoi(av[1]); // max. number of nodes
    // N = 10;
    SIZE = N*2;
    data = Malloc(N, int);

    /* Initialise tree */
    tree.num_nodes = 0;
    tree.max_nodes = N;
    tree.root = -1;   // -1 repesents NULL
    tree.free_list = 0;
    if (NULL == (tree.nodelist = Malloc(SIZE, NODE)))
        ERR_MESG("bst: out of memory");

    /* Insert nodes */
    srandom((int) time(NULL));
    for (i = 0; i < N; i++){
        data[i] = random()%1000;
        insert(&tree, &(tree.root), data[i]);
        fprintf(stderr, "After inserting %d\n", data[i]);
        print_pstree(&tree, tree.root);
        fprintf(stderr, "\n\n");
    }    

    // print_pstree(&tree, tree.root);
//     printf("Number of Nodes : %u\n", tree.num_nodes);
//     nodeptr = tree.nodelist;
//     for (i = 0; i < tree.max_nodes; i++)
//         printf("index : %d, data :%d, left: %d, right: %d\n", i, nodeptr[i].data,
// #ifdef LINENUM
//                (nodeptr[i].left > 0) ? nodeptr[i].left + 2 : nodeptr[i].left,
//                (nodeptr[i].right > 0) ? nodeptr[i].right + 2 : nodeptr[i].right
// #else
//                nodeptr[i].left, nodeptr[i].right
// #endif
//             );

    // delete half nodes
    int index_to_delete;
    for (i = 0; i < N/2; i++){
        index_to_delete = random() % N;
        if (data[index_to_delete] != -1){
            delete(&tree, tree.root, data[index_to_delete]);
            fprintf(stderr, "After deleting %d\n", data[index_to_delete]);
            print_pstree(&tree, tree.root);
            fprintf(stderr, "\n\n");
            data[index_to_delete] = -1;
        }
    } 


    // reinsert 1/4 more
    // for (i = 0; i < N/4; i++){
    //     data[i] = random()%1000;
    //     insert(&tree, &(tree.root), data[i]);
    //     fprintf(stderr, "After inserting %d\n", data[i]);
    //     print_pstree(&tree, tree.root);
    //     fprintf(stderr, "\n\n");
    // } 
//     printf("Number of Nodes : %u\n", tree.num_nodes);
//     nodeptr = tree.nodelist;
//     for (i = 0; i < tree.max_nodes; i++)
//         printf("index : %d, data :%d, left: %d, right: %d\n", i, nodeptr[i].data,
// #ifdef LINENUM
//                (nodeptr[i].left > 0) ? nodeptr[i].left + 2 : nodeptr[i].left,
//                (nodeptr[i].right > 0) ? nodeptr[i].right + 2 : nodeptr[i].right
// #else
//                nodeptr[i].left, nodeptr[i].right
// #endif
//             );
//     printf("Free Index: %d\n", tree.free_list);
    // print_pstree(&tree, tree.root);

    return 0;
}
