/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 27 July, 2018
Program description: Check for matrix multiplication feasibility, if possible return the resultant matrix
Acknowledgements:
------------------------------------*/


#include <stdio.h>
#include <stdlib.h>

#define MALLOC(type, size) (type *)malloc(sizeof(type)*size)

int matrix_multiplication(int **x,int row_x,int col_x, int **y, int row_y,int col_y){
    int *single_x_row;
    int **result = x;
    int flag = 0;
    int i, j, k;
    single_x_row = MALLOC(int, col_x);

    
    if (col_x != col_y) {
        printf("As columns of X = %d and columns of Y = %d are not equal, \
                We would need to create a new matrix to store the results...\n \
                Creating a matrix of size %d x %d\n", col_x, col_y, row_x, col_y);
        result = MALLOC(int *, row_x);
        for(i = 0; i < row_x; i++)
            *(result+i) = MALLOC(int, col_y);
        flag = 1;
    }
    else{
        printf("Reusing matrix X for storing result ...\n");
    }    
    
    for(i = 0; i < row_x; i++)
    {
        for(j = 0; j < col_x; j++)
            single_x_row[j] = x[i][j];
        for(k = 0; k < col_y; k++)
        {
            result[i][k] = 0;
            for(j = 0; j < col_x; j++) /* col_x == row_y*/
            {
                result[i][k] += (single_x_row[j] * y[j][k]);
            }
        }
        
    }
    
    printf("Elements of X x Y are:\n");
    for(i = 0; i < row_x; i++)
        for(j = 0; j < col_y; j++)
            printf("%d\n",result[i][j]);
    
    if (flag == 1)
        free(result);
    return 0;
}


int is_matrix_mul_possible(int row_x, int col_x, int row_y, int col_y){
    if (col_x == row_y) {
        return 1;
    }
    return 0;
}

int main()
{
    int row_x,col_x,row_y,col_y, i, j;
    int **x, **y;
    printf("Enter the dimensions of the matrix X (space separated): \n");
    scanf("%d %d", &row_x, &col_x);
    x = MALLOC(int *, row_x);
    for(i = 0; i < row_x; i++)
        *(x+i) = MALLOC(int, col_x);
    

    printf("Enter the dimensions of the matrix Y (space separated): \n");
    scanf("%d %d", &row_y, &col_y);
    y = MALLOC(int *, row_y);
    for(i = 0; i < row_y; i++)
        *(y+i) = MALLOC(int, col_y);


    int is_possible = is_matrix_mul_possible(row_x,col_x,row_y,col_y);
    printf("X x Y is %spossible\n",(is_possible==1)?"":"not ");

    printf("Enter the elements of X in row-wise fashion one after the other:\n");
    for(i = 0; i < row_x; i++)
        for(j = 0; j < col_x; j++)
            scanf("%d",&(x[i][j]));

    printf("Enter the elements of Y in row-wise fashion one after the other:\n");
    for(i = 0; i < row_y; i++)
        for(j = 0; j < col_y; j++)
            scanf("%d",&(y[i][j]));        
    
    // printf("Elements of X are:\n");
    // for(int i = 0; i < row_x; i++)
    //     for(int j = 0; j < col_x; j++)
    //         printf("%d\n",x[i][j]);

    // printf("Elements of Y are:\n");
    // for(int i = 0; i < row_y; i++)
    //     for(int j = 0; j < col_y; j++)
    //         printf("%d\n",y[i][j]); 

    if (is_possible == 1) {
        matrix_multiplication(x,row_x,col_x,y,row_y,col_y);
    }

    free(x);
    free(y);
    return 0;
}
