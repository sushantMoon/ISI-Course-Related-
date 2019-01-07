/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 7 August, 2018
Program description: kNNs for each node of the graph with adjacency matrix of size 1000x1000
Acknowledgements:
------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


#define SIZE 1000
#define MAX 99999999
#define MALLOC(type, size) (type *)malloc(sizeof(type)*size)


// Generating the random matrix of defines Size
int** GenMatrix(int **A, int size){
    int i,j;
    for(i=0;i<size;i++)
    {
        for(j=0;j<=i;j++)
        { 
            A[i][j]=rand()%2;
            if(i!=j)
            {
                A[j][i]=A[i][j];
            }
        }
    }
    return A;
}


int fill(int array[], int value, int size){
    int index = 0;
    for(index=0; index<size; index++){
        array[index]=value;
    }
    return 0;
}


int dijkstras(int **mat, int source, int distance[], int unvisited[], int size){
    distance[source] = 0;
    int current,j, visitedCount = 0;
    // printf("Source Node %d\n", source+1);    
    for(current=source; ;){
        if (unvisited[current] == 0){
            // printf("Visiting the node %d\n", current+1);
            unvisited[current] = 1;
            visitedCount++;
            
            for(j = 0; j < size; j++)
            {
                // if ( (unvisited[j] == 0) && (mat[current][j] > 0) && ((distance[current] + mat[current][j]) < distance[j]) ){
                if (  (mat[current][j] > 0) && ((distance[current] + mat[current][j]) < distance[j]) ){
                    distance[j] = distance[current] + mat[current][j];                    
                    // printf("Minimum Distance of node %d from source node %d = %d\n", j+1, source+1, distance[j]);
                }
            }
            
            if (visitedCount >= size){
                break;
            }
            current += 1;
            current = current%size;
        }
    }
    return 0;
}

int main(){
    int k;
    int i,l,j;
    printf("Enter the number of hops : ");
    scanf("%d", &k);

    int **matrix;
    matrix=MALLOC(int*, SIZE);
    for(i=0;i<SIZE;i++)
        matrix[i]=MALLOC(int, SIZE);

    matrix = GenMatrix(matrix, SIZE);

    FILE *fp;
    fp = fopen("knn-matrix.txt", "w");
    if (fp != NULL){
        for(i=0;i<SIZE;i++){
            for(j=0;j<SIZE;j++)
                fprintf(fp, "%d ",matrix[i][j]);
            fprintf(fp, "\n");
        }
    }
    else{
        printf("Error in opening the output file\n");
        return 0;
    }
    fclose(fp);
    fp = fopen("knn-results.txt", "w");
    fclose(fp);

    clock_t start = clock();

    // // routine to print the matrix
    // for(i=0;i<SIZE;i++){
    //     for(j=0;j<SIZE;j++)
    //         printf("%d ", matrix[i][j]);
    //     printf("\n");
    // }

    for (i=0;i<SIZE;i++){
        int distance[SIZE];
        fill(distance, MAX, SIZE);    // 999999 is infinity
        
        int unvisited[SIZE];
        fill(unvisited, 0, SIZE);
        // starting node is i
        
        //dijkstras subroutine
        dijkstras(matrix, i, distance, unvisited, SIZE);
        // for(j = 0; j < SIZE; j++)
        // {
        //     printf("%d ", distance[j]);
        // }
        // printf("\n");
        // break;

        // printf("For Node %d, Nodes that are k=%d hops away are: ", i+1, k);
        // for(l=0;l<SIZE;l++){
        //     if ( (distance[l] <= k) && (distance[l] != 0)){
        //         printf("%d ", l+1);
        //     }
        // }
        // printf("\n");

        fp = fopen("knn-results.txt", "a");
        if (fp != NULL){
            fprintf(fp, "For Node %d, Nodes that are k=%d hops away are: ", i+1, k);
            for(l=0;l<SIZE;l++){
                if ( (distance[l] <= k) && (distance[l] != 0) ){
                    fprintf(fp, "%d ", l+1);
                }
            }
            fprintf(fp, "\n");
        }
        else{
            printf("Error in opening the knn-results file\n");
            return 0;
        }
        fclose(fp);
    }
    clock_t end = clock();
    printf("Results are stored in knn-results.txt\n");
    printf("Total time Taken for finding the nodes that can be reached in K=%d Hops:  %lf\n", k, ((double)(end - start)) / CLOCKS_PER_SEC);
    return 0;
}
