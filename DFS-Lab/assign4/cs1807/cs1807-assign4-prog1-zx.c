/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 4 December, 2018
Program description: 

Compile Using : ```gcc -g -Wall -o prog1 cs1807-assign4-prog1-zx.c stack.c -lm```
Run : ``` ./prog1 100 80 10 200 ```
Acknowledgements:

------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "stack.h"
#include "common.h"

#define MALLOC(type, n) (type *)malloc(sizeof(type)*n)
#define CALLOC(type, n) (type *)calloc(sizeof(type), n)
#define REALLOC(array, array_length, type_of_elements_in_array) (type_of_elements_in_array *)realloc(array, array_length* sizeof(type_of_elements_in_array))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MAX_LENGTH 1024


int main(int argc, char const *argv[])
{
    Stack *intStack = newStack(sizeof(int));
    int i=0, max_sum=INT_MIN, min_value_over_range=INT_MAX, no_of_elements=0, current_value, sum, value;
    
    for(i = 1; i < argc; i++){
        current_value = atoi(argv[i]);
        if (min_value_over_range > current_value){
            sum = (no_of_elements + 1) * current_value;
            value = current_value;
        }
        else if (min_value_over_range <= current_value){
            sum = (no_of_elements + 1) * min_value_over_range;
            value = min_value_over_range;
        }
        if (sum > max_sum){
            min_value_over_range = value;
            max_sum = sum;
            no_of_elements += 1;
            int *element = MALLOC(int, 1);
            *element = i;
            push(intStack, element); 
        }
    }

    for(i=0; i<intStack->num_elements; i++){
        printf("%d ", ((int *)intStack->elements)[i]);
    }

    printf("%d\n", min_value_over_range);

    freeStack(&intStack);
    return 0;
}
