/**
 * @author Sushant Moon
 * @email sushant.moon@gmail.com
 * @create date 2018-08-23 05:01:31
 * @modify date 2018-08-23 05:01:31
 * @desc Matric Multiplication for Spare Matrix using Data Structure mentioned on 
    https://www.cs.umd.edu/~mount/420/Lects/420lects.pdf page 16
*/

#include <stdio.h>
#include <stdlib.h>
#define MALLOC(type, n) (type *)malloc(sizeof(type)*n)


typedef struct matrix_node{
	int i, j, data;
    struct matrix_node *col, *row;
}Matrix_Node;

typedef struct matrix_index{
    int index_position;
    Matrix_Node *node;
}Matrix_Index;

typedef struct matrix{
    int m,n;
    Matrix_Index *ROW, *COL;            // Array of Linked List
}Matrix;

void insert_in_matrix(Matrix *A, int i, int j, int v){
    if (v > 0){
        Matrix_Node *node = MALLOC(Matrix_Node,1);
        node->data = v;
        node->i = i;
        node->j = j;
        node->col = NULL;
        node->row = NULL;

        // update A.ROW's entry
        if ((A->ROW+i)->node == NULL){
            (A->ROW+i)->node = node;
        }
        else{
            Matrix_Node *row_tail = (A->ROW+i)->node;
            while(row_tail->row != NULL){
                row_tail = row_tail->row;
            }
            row_tail->row = node;
        }

        // update A.COL's entry
        if ((A->COL+j)->node == NULL){
            (A->COL+j)->node = node;
        }
        else{
            Matrix_Node *col_tail = (A->COL+j)->node;
            while(col_tail->col != NULL){
                col_tail = col_tail->col;
            }
            col_tail->col = node;
        }
    }
}

void iniialize_matrix(Matrix *A, int m, int n){
    int i;
    A->m = m;
    A->n = n;
    A->ROW = MALLOC(Matrix_Index, A->m);
    A->COL = MALLOC(Matrix_Index, A->n);
    
    for(i = 0; i <m; i++){
        (A->ROW+i)->index_position = i;
        (A->ROW+i)->node = NULL;
    }

    for(i = 0; i <n; i++){
        (A->COL+i)->index_position = i;
        (A->COL+i)->node = NULL;
    }
}

void print_matrix_elements_columns_wise(Matrix *A,char C){
    int i;
    printf("Elements of Matrix %c :\n", C);
    for(i=0;i<A->n;i++){
        Matrix_Node *node;
        node = (A->COL+i)->node;
        printf("Printing Col %d\n", i);
        while(node != NULL){
            printf("%c[%d,%d] = %d\n", C, node->i, node->j, node->data);
            node = node->col;
        }
    }
}

void multiply_matrix(Matrix *A, Matrix *B, Matrix *C){
    int i, j;
    if (A->n == B->m){
        iniialize_matrix(C, A->m, B->n);
        for(i = 0; i < A->m; i++){
            for(j = 0; j < B->n; j++){
                Matrix_Node *row = (A->ROW+i)->node;
                Matrix_Node *col = (B->COL+j)->node;
                if (col != NULL && row != NULL){
                    int value = 0;
                    while(col != NULL && row != NULL){
                        if (row->j == col->i){
                            value += (row->data * col->data);
                            row = row->row;
                            col = col->col;
                        }
                        else if(row->j < col->i){
                            row = row->row;
                        }
                        else if(row->j > col->i){
                            col = col->col;
                        }
                    }
                    insert_in_matrix(C, i, j, value);
                }
            }
        }
    }
    else{
        perror("Matrix cannot be multiplied");
        exit(-1);
    }
}

int main()
{
    int i, j;
    Matrix A, B;
    int m1, n1, m2, n2;
    printf("Enter the dimension of Matrix A (space separated, eg. 3 2 for a 3x2 matrix) : ");
    scanf("%d %d", &m1, &n1);
    iniialize_matrix(&A, m1, n1);
    printf("Enter the dimension of Matrix A (space separated, eg. 2 3 for a 2x3 matrix) : ");
    scanf("%d %d", &m2, &n2);
    iniialize_matrix(&B, m2, n2);
    
    printf("Enter Elements of Matrix 1\n");
    for(i = 0; i < A.m; i++){
        for(j = 0; j < A.n; j++){
            printf("A[%d,%d] = ", i, j);
            int v;
            scanf("%d", &v);
            insert_in_matrix(&A, i, j, v);
        }
    }

    
    // Printing A columnwise
    // print_matrix_elements_columns_wise(&A,'A');

    printf("Enter Elements of Matrix 2\n");
    for(i = 0; i < B.m; i++){
        for(j = 0; j < B.n; j++){
            printf("B[%d,%d] = ", i, j);
            int v;
            scanf("%d", &v);
            insert_in_matrix(&B, i, j, v);
        }
    }
    
    Matrix C;  // result matrix
    multiply_matrix(&A, &B, &C);

    // print_matrix_elements_columns_wise(&A, 'A');
    // print_matrix_elements_columns_wise(&B, 'B');
    print_matrix_elements_columns_wise(&C, 'C');

    return 0;
}
