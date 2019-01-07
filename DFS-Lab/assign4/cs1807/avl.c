#include "avl.h"
#include "common.h"

int avl_tree_height(AVL_Tree_Node *N){ 
	if (N == NULL){
		return 0;
    }
	return N->height; 
}

int avl_tree_height_difference(AVL_Tree_Node *N){ 
	if (N == NULL){
		return 0; 
    }
	return avl_tree_height(N->left) - avl_tree_height(N->right); 
}

AVL_Tree_Node *avl_tree_init_new_node(int key){ 
	AVL_Tree_Node *node = MALLOC(AVL_Tree_Node, 1);
	node->key = key; 
	node->left = NULL; 
	node->right = NULL; 
	node->height = 1;
    node->count = 1;
	return node; 
}

AVL_Tree_Node *avl_tree_right_rotate(AVL_Tree_Node *y){ 
	AVL_Tree_Node *x = y->left; 
	AVL_Tree_Node *T2 = x->right; 

	x->right = y; 
	y->left = T2; 

	y->height = MAX(avl_tree_height(y->left), avl_tree_height(y->right)) + 1; 
	x->height = MAX(avl_tree_height(x->left), avl_tree_height(x->right)) + 1; 

	return x; 
}

AVL_Tree_Node *avl_tree_left_rotate(AVL_Tree_Node *x){ 
	AVL_Tree_Node *y = x->right; 
	AVL_Tree_Node *T2 = y->left; 

	y->left = x; 
	x->right = T2; 

	x->height = MAX(avl_tree_height(x->left), avl_tree_height(x->right)) + 1; 
	y->height = MAX(avl_tree_height(y->left), avl_tree_height(y->right)) + 1; 

	return y; 
}

AVL_Tree_Node *avl_tree_insert(AVL_Tree_Node* node, int key){ 
	if (node == NULL){
        printf("AVL Tree : Inserted\n");
		return(avl_tree_init_new_node(key)); 
    }

	if (key < node->key){
		node->left = avl_tree_insert(node->left, key); 
    }
	else if (key > node->key){
		node->right = avl_tree_insert(node->right, key); 
    }
	else if (key == node->key){
        node->count += 1;
        printf("AVL Tree : Duplicate\n");
		return node; 
    }   

	node->height = 1 + MAX(avl_tree_height(node->left), avl_tree_height(node->right)); 

	int balance = avl_tree_height_difference(node);

	// Left Left Case 
	if (balance > 1 && key < node->left->key) 
		return avl_tree_right_rotate(node); 

	// Right Right Case 
	if (balance < -1 && key > node->right->key) 
		return avl_tree_left_rotate(node); 

	// Left Right Case 
	if (balance > 1 && key > node->left->key) 
	{ 
		node->left = avl_tree_left_rotate(node->left); 
		return avl_tree_right_rotate(node); 
	} 

	// Right Left Case 
	if (balance < -1 && key < node->right->key) 
	{ 
		node->right = avl_tree_right_rotate(node->right); 
		return avl_tree_left_rotate(node); 
	} 

	return node; 
} 

int avl_tree_count_check(AVL_Tree_Node* node, int key){
    if (node == NULL){
		return -1; 
    }
	if (key < node->key){
		return avl_tree_count_check(node->left, key); 
    }
	else if (key > node->key){
		return avl_tree_count_check(node->right, key); 
    }
	else if (key == node->key){
		return node->count; 
    }
	return -1;
}

void avl_tree_free(AVL_Tree_Node *root){
	if ((root->left == NULL) && (root->right == NULL)){
		free(root);
	}
	else{
		if (root->left != NULL){
			avl_tree_free(root->left);
		}
		if (root->right != NULL){
			avl_tree_free(root->right);
		}
		free(root);
	} 
}