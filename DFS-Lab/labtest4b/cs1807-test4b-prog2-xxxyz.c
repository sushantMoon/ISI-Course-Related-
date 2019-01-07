/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 30 November, 2018
Program description:

Compile using : ``` gcc -g -Wall cs1807-test4b-prog2-xxxyz.c -o prog2 ```

Acknowledgements:
------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MALLOC(type, n) (type *)malloc(sizeof(type)*n)
#define CALLOC(type, n) (type *)calloc(sizeof(type), n)
#define REALLOC(array, array_length, type_of_elements_in_array) (type_of_elements_in_array *)realloc(array, array_length* sizeof(type_of_elements_in_array))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MAX_LENGTH 1024

void print_array(int *T, int count){
    int i;
    for(i = 0; i < count; i++){
        printf("%d ", T[i]);
    }
    printf("\n");
}

int main(){
    int colorA=0, colorB=0, colorC=0, tree_size=0, multiplier = 1, i = 0, count = 0, is_invalid_FnBT = 0;
    char temp;
    int *T = MALLOC(int, MAX_LENGTH*multiplier);
    do{
        scanf("%d%c", &T[tree_size], &temp);
        if (is_invalid_FnBT == 0){
            if((tree_size == 0) && (T[tree_size] != -1)){
                is_invalid_FnBT = 1;
            }
            if((tree_size > 0) && (T[tree_size] == -1)){
                is_invalid_FnBT = 1;       
            }

            if (tree_size > 0){
                if (T[tree_size] == T[tree_size - 1]){
                    count += 1;
                }
                else{
                    if (count > 1){
                        is_invalid_FnBT = 1;
                    }
                    count = 0;
                }
            }
        }

        tree_size += 1;
        if (tree_size + 1 >= MAX_LENGTH*multiplier){
            multiplier += 1;
            T = REALLOC(T, MAX_LENGTH*multiplier, int);
        }
    }while(temp != '\n');

    T = REALLOC(T, tree_size, int);
    // print_array(T, tree_size);
    int *color = CALLOC(int, tree_size);
    // print_array(color, tree_size);
    
    // checking for valid FnBT
    if (is_invalid_FnBT == 1) {
        printf("-1\n");
        return 0;
    }

    for(i = 0; i < tree_size; i++){
        if (i == 0){
            color[i] = 1;
            colorA += 1;
        }
        else if (i == 1){
            color[i] = 2;
            colorB += 1; 
        }
        else{
            if (color[T[i]] != color[i-1]){
                int i_th_color = 6 - (color[T[i]] + color[i-1]);
                if (i_th_color == 1){
                    color[i] = 1;
                    colorA += 1;
                }
                else if (i_th_color == 2){
                    color[i] = 2;
                    colorB += 1;
                }
                else if (i_th_color == 3){
                    color[i] = 3;
                    colorC += 1;
                }
            }
            else{
                if (color[i-1] == 1){
                    color[i] = 2;
                    colorB += 1;
                }
                else if (color[i-1] == 2){
                    color[i] = 1;
                    colorA += 1;
                }
                else if (color[i-1] == 3){
                    color[i] = 1;
                    colorA += 1;
                }
            }
        }
    }

    int min = MIN(colorA, MIN(colorB,colorC));
    int max = MAX(colorA, MAX(colorB,colorC));
    
    printf("%d %d\n", min, max);
    return 0;
}