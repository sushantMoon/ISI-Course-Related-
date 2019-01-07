/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 28 September, 2018
Program description: 

Implement a generic data structure SEQUENCE to hold a list of elements of any one of the
following types: int, float, char* (all elements in a particular list will be of the same type)

Compile using : gcc -g -Wall cs1807-assign2-prog1.c sequence.c -o prog1 -lm
For Part 1 :
1. use the input_test_part1a.txt
2. uncomment the code for part 1 and use command :
    ```
        ./prog1 < input_test_part1a.txt    
    ```
For Part 2 :
Directly run the code using `./prog1 < input.txt`
Or `./prog1` followed by the input format mentioned in the assignment 

Note : 0 Based indexing
Acknowledgements:
------------------------------------*/


#include "sequence.h"

#define MAX_STRING_SIZE 4096

int main(){
    int i, k, j, N;
    char type;

    //Part 1.a
    // Testing The Required Functions
    // // For Ints
    // scanf(" %c", &type);
    // Sequence *si = newSequence(type);
    // scanf("%d", &k);
    // for(j=0; j<k; j++){
    //     int *valuei = MALLOC(int, 1);
    //     scanf("%d", valuei);
    //     push(si, valuei);
    // }
    // printf("Size of the Sequence is : %lu\n", length(*si));
    // for(i=k-1;i>-1;i--){
    //     get_element(*si, i);
    // }
    // summation(*si);
    // freeSequence(si);

    // // For Floats
    // scanf(" %c", &type);
    // Sequence *sf = newSequence(type);
    // scanf("%d", &k);
    // for(j=0; j<k; j++){
    //     float *valuef = MALLOC(float, 1);
    //     scanf("%f", valuef);
    //     push(sf, valuef);
    // }
    // printf("Size of the Sequence is : %lu\n", length(*sf));
    // for(i=k-1;i>-1;i--){
    //     get_element(*sf, i);
    // }
    // summation(*sf);
    // freeSequence(sf);

    // // For Strings
    // scanf(" %c", &type);
    // Sequence *sc = newSequence(type);
    // scanf("%d", &k);
    // for(j=0; j<k; j++){
    //     char *values = MALLOC(char, MAX_STRING_SIZE);
    //     scanf("%s", values);
    //     push(sf, values);
    // }
    // printf("Size of the Sequence is : %lu\n", length(*sc));
    // for(i=k-1;i>-1;i--){
    //     get_element(*sc, i);
    // }
    // summation(*sc);
    // freeSequence(sc);

    //Part 1.b
    scanf("%d", &N);
    Sequence *maxS;
    int max = -1;
    for(i=0; i<N; i++){
        scanf(" %c", &type);
        Sequence *s = newSequence(type);
        scanf("%d", &k);
        for(j=0; j<k; j++){
            if (type == 's'){
                char *values = MALLOC(char, MAX_STRING_SIZE);
                scanf("%s", values);
                push(s, values);
            }
            else if (type == 'i'){
                int *values = MALLOC(int, 1);
                scanf("%d", values);
                push(s, values);
            }
            else if (type == 'f'){
                float *values = MALLOC(float, 1);
                scanf("%f", values);
                push(s, values);
            }
        }
        int sum = summation_copy(*s);
        // printf("%d", sum);
        if (max < sum){
            max = sum;
            maxS = s;
            s = NULL;
        }
        else{
            freeSequence(s);
            s = NULL;
        }
    }
    for(i=0; i<maxS->num_elements ;i++){
        get_element_of_sequence(*maxS, i);
    }
    printf("\n");
    return 0;
}