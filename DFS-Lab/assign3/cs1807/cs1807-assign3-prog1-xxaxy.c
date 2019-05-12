/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 27 October, 2018
Program description: 
Finding the relations between SYNONYM and ANTONYM
Compile Using : ```gcc -g -Wall -o prog1 cs1807-assign3-prog1-xxaxy.c -lm```
Run : ```./prog1 <dictionary_filename> <word1> <word2>```

Acknowledgements:
number_of_lines_in_file : O(n)
brute_find_index_in_dictioary : O(n^2)
log_n_find_index_in_dictioary : O(log(n))
populate_dictionary : O(n^2)
update_synonyms_antonyms_relation : O(n^3)  worst case
search on relation : O(1)
------------------------------------*/

#include "common.h"

#define WORDSIZE 512   // sizeof each word (assumtions)
#define LINESIZE 4096  // sizeof line in the file (assumptions)
// #define DEBUG

int number_of_lines_in_file(char* file_name){

    #ifdef DEBUG
    printf("Entered number_of_lines_in_file %s function\n", (char *)file_name);
    #endif

    FILE* fp = fopen(file_name, "r");
    int lines = 0;
    char ch;
    if (fp == NULL){
        perror("File Not Available\n");
        exit(-1);
    }
    while(!feof(fp)){
        ch = fgetc(fp);
        if(ch == '\n'){
            lines++;
        }
    }
    lines++;
    fclose(fp);
    return lines;
}

int string_comparator(const void *a, const void *b){ 
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
} 

void print_string_array(char **array, int len){ 
    int i;
    for(i=0; i<len; i++) 
        printf("%s | ", array[i]);
 
    putchar('\n');
}

void print_matrix(int** matrix, int dict_size){
    int i,j;
    for(i = 0; i < dict_size; i++){
        for(j = 0; j < dict_size; j++){
            printf("%d | ", matrix[i][j]);   
        }
        printf("\n");
    }
}

int brute_find_index_in_dictioary(char ** dict, int dict_size, char* word){
    int i = 0;
    for(i=0; i < dict_size; i++){
        if (strcmp(dict[i], word) == 0){
            return i;
        }
    }
    return -1;  //word in not in the dictionary 
}

int log_n_find_index_in_dictioary(char ** dict, int dict_size, char* word){
    int i, start, end;
    i = dict_size/2;
    start = 0;
    end = dict_size;
    while( (i >= 0) || (i < dict_size) ){
        if (strcmp(dict[i], word) == 0){
            return i;
        }
        else if (strcmp(dict[i], word) > 0){
            end = i;
            i = ((start + end)/2);
        }
        else if (strcmp(dict[i], word) < 0){
            start = i;
            i = ((start + end)/2);
        }
        if ((i == 0) || (i == dict_size - 1)){
            if (strcmp(dict[i], word) == 0){
                return i;
            }
            break;
        } 
    }
    return -1;  //word in not in the dictionary 
}

int populate_dictionary(char* file_name, char** dict){
    FILE* fp = fopen(file_name, "r");
    int size_dictionary = 0;
    while(!feof(fp)){
        char* symbol = MALLOC(char, 5);
        char* word1 = MALLOC(char, WORDSIZE);
        char* word2 = MALLOC(char, WORDSIZE);
        fscanf(fp, "%s %s %s", symbol, word1, word2);
        if(brute_find_index_in_dictioary(dict, size_dictionary, word1) == -1){
            strcpy(dict[size_dictionary], word1);
            size_dictionary++;
        }
        if(brute_find_index_in_dictioary(dict, size_dictionary, word2) == -1){
            strcpy(dict[size_dictionary], word2);
            size_dictionary++;
        }
        free(word1);
        free(word2);
        free(symbol);
    }
    fclose(fp);
    return size_dictionary;
}

void update_synonyms_antonyms_relation(int** matrix, char** dict, int dict_size, char* file_name){
    FILE* fp = fopen(file_name, "r");
    int i, j, k;
    if (fp == NULL){
        perror("File Not Available\n");
        exit(-1);
    }
    while(!feof(fp)){
        char* symbol = MALLOC(char, 5);
        char* word1 = MALLOC(char, WORDSIZE);
        char* word2 = MALLOC(char, WORDSIZE);
        fscanf(fp, "%s %s %s", symbol, word1, word2);
        i = log_n_find_index_in_dictioary(dict, dict_size, word1);
        j = log_n_find_index_in_dictioary(dict, dict_size, word2);
        matrix[i][i] = 1;
        matrix[j][j] = 1;
        if (strcmp(symbol, "+") == 0){
            matrix[i][j] = 1;
            matrix[j][i] = 1;
        }
        if (strcmp(symbol, "-") == 0){
            matrix[i][j] = -1;
            matrix[j][i] = -1;
        }
        free(word1);
        free(word2);
        free(symbol);
    }
    // printf("\n");
    // print_matrix(matrix, dict_size);
    // printf("\n");

    // making updates for rest of the relations in rows and columns of i and j
    for (i=0; i<dict_size; i++){
        for(k=0; k<dict_size; k++){
            if (i == k){
                continue;
            }
            else if (matrix[i][k] == 1){
                for (j=0; j<dict_size; j++){
                    if (matrix[i][j] == 0){
                        matrix[i][j] = matrix[k][j];
                    }
                    if (matrix[k][j] == 0){
                        matrix[k][j] = matrix[i][j];
                    }
                }
            }
            else if (matrix[i][k] == -1){
                for (j=0; j<dict_size; j++){
                    if (matrix[i][j] == 0){
                        matrix[i][j] = -1 * matrix[k][j];
                    }
                    if (matrix[k][j] == 0){
                        matrix[k][j] = -1 * matrix[i][j];
                    }
                }
            }
        }
    }
    fclose(fp);
}

int main(int argc, char const *argv[]){
    if (argc < 4){
        printf("The input format is : ./prog1 <dictionary_filename> <word1> <word2>\n");
        return -1;
    }

    int i, DICTSIZE = 0;

    DICTSIZE = 2 * number_of_lines_in_file((char *)argv[1]);
    #ifdef DEBUG
    printf("Output from number_of_lines_in_file %s function : %d\n", (char *)argv[1], DICTSIZE/2);
    #endif
    
    char **dictionary = CALLOC(char*, DICTSIZE);
    
    for(i = 0; i < DICTSIZE; i++){
        dictionary[i] = CALLOC(char, WORDSIZE);
        memset(dictionary[i], '\0', WORDSIZE);
    }
    
    DICTSIZE = populate_dictionary((char *)argv[1], dictionary);
    
    #ifdef DEBUG
    printf("Testing the populate function\n"); 
    print_string_array(dictionary, DICTSIZE);
    #endif

    // sorting the string in dictionary for log n search time 
    qsort(dictionary, DICTSIZE, sizeof(char *), string_comparator);
    #ifdef DEBUG
    printf("Testing the QSort Operation\n");
    print_string_array(dictionary, DICTSIZE);
    #endif
    
    #ifdef DEBUG
    printf("Testing the Log Find Operation\n");
    for(i = 0; i < DICTSIZE; i++){
        printf("%s : index %d\n", dictionary[i], log_n_find_index_in_dictioary(dictionary, DICTSIZE, dictionary[i]));
    }
    #endif

    
    int **matrix = CALLOC(int *, DICTSIZE);
    for(i=0 ; i<DICTSIZE ; i++){
        matrix[i] = CALLOC(int, DICTSIZE);
    }

    update_synonyms_antonyms_relation(matrix, dictionary, DICTSIZE, (char *)argv[1]);

    #ifdef DEBUG
    printf("Printing the Relationship Matrix:\n");
    print_matrix(matrix, DICTSIZE);
    #endif

    int k = log_n_find_index_in_dictioary(dictionary, DICTSIZE, (char *)argv[2]);
    int l = log_n_find_index_in_dictioary(dictionary, DICTSIZE, (char *)argv[3]);

    if ((k == -1) || (l == -1)){
        printf("The words given as agruments are not present in the dictionary. Try Again.\n");
        return -1;
    }
    if (matrix[k][l] == 1){
        printf("SYNONYM\n");
    }
    else if (matrix[k][l] == -1){
        printf("ANTONYM\n");
    }
    else if (matrix[k][l] == 0){
        printf("UNRELATED\n");
    }
    return 0;
}
