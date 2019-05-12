/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 4 December, 2018
Program description: 

Compile Using : ```gcc -g -Wall -o prog2 cs1807-assign4-prog2-zxx.c trie.c -lm```
Run : ``` ./prog2 input.txt string.txt ```
Acknowledgements:

------------------------------------*/

#include "common.h"
#include "trie.h"
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

// #define DEBUG 1

size_t read_from_file_to_char_array(const char *file_name, char** buffer){
    // Opening the fle in binary read mode
    FILE *fp = fopen(file_name, "rb");
    if (fp == NULL){
        perror("File Not Available\n");
        exit(-1);
    }

    // moving the pointer to the end of the file
    fseek(fp, 0, 2);

    // storing the size of the file;
    size_t bsize = ftell(fp);

    // rewinding to the starting of the file
    rewind(fp);

    *buffer = MALLOC(char, bsize);
    if (*buffer == NULL){
        perror("Memory Allocation failed !!\n");
        exit(-1);
    }

    size_t result = fread(*buffer, 1, bsize, fp);
    
    if (result != bsize) {
        perror("Reading Error !!\n");
        exit(-1);
    }
    fclose(fp);
    return bsize;
}


int main(int argc, char const *argv[])
{
    TrieNode *root;
    root = newTrie();
    char *token;
    size_t i;

    char *input;
    size_t input_size = read_from_file_to_char_array(argv[1], &input);

    char *string;
    size_t string_size = read_from_file_to_char_array(argv[2], &string);

    
    for(i = 0; i < input_size; i++){
        if (isspace(input[i]) || !isalnum(input[i]) || ispunct(input[i])){
            input[i] = ' ';
        }
        input[i] = tolower(input[i]);
    }

    for(i = 0; i < string_size; i++){
        if (!isalnum(string[i])){
            string[i] = ' ';
        }
        string[i] = tolower(string[i]);
    }
    
    
    #if defined(DEBUG)
        printf("############### START : THE CONTENT OF THE FILE\n");
    #endif // DEBUG
    token = strtok(input, " ");
    while(token != NULL){
        #if defined(DEBUG)
            printf("%s\n", token);
        #endif // DEBUG
        insertTrie(root, token);
        token = strtok(NULL, " ");
    }

    #if defined(DEBUG)
        printf("############### START : THE CONTENT OF THE STRING\n");
    #endif // DEBUG
    token = strtok(string, " ");
    while(token != NULL){
        #if defined(DEBUG)
            printf("%s\nResults: ", token);    
        #endif // DEBUG
        TrieNode *r = searchTrie(root, token);
        if (r == NULL){
            printf("%s 0\n", token);
        }
        else{
            printf("%s %d\n", token, r->count);
        }
        token = strtok(NULL, " ");
    }
    freeTrie(root);
    return 0;
}
