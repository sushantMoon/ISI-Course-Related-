/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 27 October, 2018
Program description: 
An implementation of a Min-Max Binary Heap, based on 1986 article 
"Min-Max Heaps and Generalized Priority Queues"

Compile Using : ```gcc -g -Wall -o prog3 cs1807-assign3-prog3-zcxaxy.c min-max-heap.c -lm```
Run : ```./prog3 <m1> <m2> <m3> <m4> ... so on```

Acknowledgements:

------------------------------------*/

#include "common.h"
#include "min-max-heap.h"

// #define DEBUG
#define BUFFER 10240

int main(int argc, char const *argv[])
{
    if (argc < 2){
        #ifdef DEBUG
        ps("./prog3 <m1> <m2> <m3> <m4> ... and so on ..\n");
        #endif
        return 0;
    }

    char *input = CALLOC(char, BUFFER);
    char *input_copy = CALLOC(char, BUFFER);
    char *token;
    int *A;
    int count, i, flag, k, query;
    size_t length;
    MinMaxHeap *h;
    
    #ifdef DEBUG
    ps("Enter the integers space seperated : \n<int 1> <int 2> <int 3> <int 4> ... and so on ..\n");
    #endif
    
    fgets(input, BUFFER, stdin);
    length = strlen(input);
    if ( (length == (BUFFER-1)) && (input[length-1] != '\n') ){
        printf("Error, line over-flow buffer!\n");
        return 1;
    }
    if (input[length-1]=='\n'){
        input[length-1]='\0';
    }

    memcpy(input_copy, input, BUFFER);

    // counting the number of elements
    count = 0;
    token = strtok(input, " ");
    while(token != NULL){
        count++;
        token = strtok(NULL, " ");
    }
    #if defined(DEBUG)
    printf("Total number of elements entered are %d\nThe elements are :\n", count);
    #endif // DEBUG
    
    i = 0;
    A = MALLOC(int, count);
    token = strtok(input_copy, " ");
    while(token != NULL){
        A[i] = atoi(token);
        #if defined(DEBUG)
        printf("A[%d] = %d\n", i, A[i]);
        #endif // DEBUG
        i++;
        token = strtok(NULL, " ");
    }
    
    flag = 0;
    i = 1;
    while(i < argc){
        query = atoi(argv[i]);
        h = newMinMaxHeap(sizeof(int), &integer_comparator);
        // Populating the Min-Max-Heap
        for(k = 0; k < count; k++){
            MinMaxHeapInsert(h, &A[k]);            
        }
    
        if (query != 0){
            if (query > 0){
                flag = 1; // flag is 1 when extract max needs to be done else -1 for extract min
            }
            else if (query < 0){
                flag = -1;
                query *= -1;
            }
            int *output_pointer = MALLOC(int, 1);
            while(query > 0){
                if (flag == 1){
                    MinMaxHeapExtractMax(h, output_pointer);
                }
                else if (flag == -1){
                    MinMaxHeapExtractMin(h, output_pointer);
                }
                query--;
            }
            printf("%d ", *output_pointer);
            flag = 0;
            free(output_pointer);
        }
        freeMinMaxHeap(h);
        i++;
    }
    printf("\n");

    return 0;
}
