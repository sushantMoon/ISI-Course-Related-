#if !defined(__G_EERTREE__)
#define __G_EERTREE__

#define TREESIZE 100000

typedef struct eertree_node{
    int length;
    int suffix_link;
    int next[26];
    int count;
}eertree_node;

typedef struct eertree{
    int index;
    int suffix;
    eertree_node node[TREESIZE];
}eertree;

eertree *initialize_eertree();
int add_letter_eertree(int position, char* input, eertree* tree);
int get_suffix_link(int position, char* input, int index, eertree* tree);

#endif // __G_EERTREE__
