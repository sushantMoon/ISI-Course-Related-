#if !defined(__G_BINARY_TREE__)
#define __G_BINARY_TREE__

typedef struct BTNode{
    void *data;
    struct BTNode *leftchild;
    struct BTNode *rightchild;
}BTNode;

typedef struct BinaryTree{
    BTNode root;
}BinaryTree;


#endif // __G_BINARY_TREE__

