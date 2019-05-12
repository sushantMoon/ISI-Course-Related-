/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 30 November, 2018
Program description:

Compile using : ``` gcc -g -Wall cs1807-test4b-prog3-xxx.c -o prog3 ```

Acknowledgements:
------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MALLOC(type, n) (type *)malloc(sizeof(type)*n)
#define CALLOC(type, n) (type *)calloc(sizeof(type), n)
#define REALLOC(array, array_length, type_of_elements_in_array) realloc(array, (array_length - 1) * sizeof(type_of_elements_in_array))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MAX_LENGTH 512

int is_A_prefix_of_B(const char *A, const char *B){
    int lenA = strlen(A);
    int lenB = strlen(B);
    if (lenB < lenA){
        return 0;
    }
    else{
        if (strncmp(A, B, lenA) == 0){
            return 1;
        }
    }
    return 0;
}

int string_comparator(const void *a, const void *b){
    //comparator for reverse order
    //comparator for ascending order
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    // int la = strlen(*ia);
    // int lb = strlen(*ib);
    // if (la == lb){
    //     // return strcmp(*ib, *ia);
    //     return strcmp(*ia, *ib);
    // }
    // return lb - la;
    // // return la - lb;
    return strcmp(*ib, *ia);
}

char ** remove_from_list(char **list, int list_size, int position_to_remove){
    int i;
    for(i = position_to_remove; i < list_size-1; i++){
        list[i] = list[i+1];
    }
    
    char **temp = REALLOC(list, list_size-1, char *);
    if (temp == NULL && list_size > 1){
        exit(EXIT_FAILURE);
    }
    list = temp;
    return list;
    // decrease the list_size by urself 
}

char ** copy_list(char **list, int list_size){
    char **new_list = CALLOC(char *, list_size);
    int i;
    for(i = 0; i < list_size; i++){
        new_list[i] = CALLOC(char, strlen(list[i]));
        strcpy(new_list[i], list[i]);
    }
    return new_list;
}

void free_list(char **list, int list_size){
    int i;
    for(i = 0; i < list_size; i++){
        free(list[i]);   
    }
    free(list);
}

void print_list(char **list, int list_size){
    int i;
    for(i = 0; i < list_size; i++){
        printf("%s ", list[i]);
    }
    printf("\n");
}

int prefix_segment(char *S, char **list, int list_size, char *prefix, int string_in_prefix){
    if (strcmp(prefix, S) == 0){
        return string_in_prefix;
    }
    else{
        if (is_A_prefix_of_B(prefix, S) == 1){
            int i, new_list_size, value, min = INT_MAX;
            for(i = 0; i < list_size; i++){
                char *prefix_str = CALLOC(char, MAX_LENGTH);
                strcpy(prefix_str,prefix);
                strcat(prefix_str, list[i]);
                if (strcmp(prefix_str, S) == 0){
                    return string_in_prefix + 1;
                }
                else if (is_A_prefix_of_B(prefix_str, S) == 1){
                    char **new_list = copy_list(list, list_size);
                    new_list_size = list_size;
                    new_list = remove_from_list(new_list, new_list_size, i);
                    new_list_size -= 1;
                    // print_list(new_list, new_list_size);
                    value = prefix_segment(S, new_list, new_list_size, prefix_str, string_in_prefix + 1);
                    if ((value != -1) && value < min){
                        min = value;
                    }
                    free_list(new_list, new_list_size);
                }
                free(prefix_str);
            }
            if (min == INT_MAX){
                return -1;
            }
            else{
                return min;
            }
        }
        else{
            return -1;
        }
    }
    return -1;
}

int main(){
    int n, list_size=0;
    char *S = CALLOC(char , MAX_LENGTH);
    int i;
    scanf("%d %s", &n, S);

    char** list = CALLOC(char *, n);
    for(i = 0; i < n; i++){
        char* temp_element = CALLOC(char, MAX_LENGTH);
        scanf("%s", temp_element);

        char *p = strstr(S, temp_element);
        // strstr checks if temp_element is substring of S
        // returns NULL if no match else pointer to starting position for the match 

        if (p != NULL){
            list[list_size] = CALLOC(char, MAX_LENGTH);
            strcpy(list[list_size], temp_element);
            list_size += 1;
        }
        free(temp_element);
    }
    qsort(list, list_size, sizeof(char *), string_comparator);
    
    int min = INT_MAX, value = 0;
    int new_list_size = 0;

    for(i = 0; i < list_size; i++){
        char **new_list = copy_list(list, list_size);
        new_list_size = list_size;
        char *prefix_str = CALLOC(char, strlen(new_list[i]));
        strcpy(prefix_str, new_list[i]);
        new_list = remove_from_list(new_list, new_list_size, i);
        new_list_size -= 1;
        // print_list(new_list, new_list_size);
        value = prefix_segment(S, new_list, new_list_size, prefix_str, 1);
        if ((value != -1) && value < min){
            min = value;
        }
        free(prefix_str);
        free_list(new_list, new_list_size);
    }
    free_list(list, list_size);
    if (min == INT_MAX){
        printf("0\n");
    }
    else{
        printf("%d\n", min);
    }
    return 0;
}