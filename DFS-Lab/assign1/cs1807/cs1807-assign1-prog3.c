/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 28 August, 2018
Program description: Consider a simple encryption scheme (Vigen`ere cipher) in which, given a plain text (PT)
message, you pick a suitable word from the text and use that as an encryption key to
generate the cipher text (CT). Applying the Vigen`ere cipher can be described algebraically
as follows. If the letters A–Z are taken to be the numbers 0–25 (A ≡ 0, B ≡ 1, etc.), and
addition is performed modulo 26, Vigen`ere encryption E using the key K can be written as
Ci = EK(Mi) = (Mi + Ki) mod 26
2
where Ci
is the ith character of CT, Mi
is the ith character of PT, and Ki
is the i-th character
of the key.

Run using : gcc -g -Wall cs1807-assign1-prog3.c -o prog3 -lm


Acknowledgements:
------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MALLOC(type, n) (type *)malloc(sizeof(type)*n)
#define CALLOC(type, n) (type *)calloc(sizeof(type), n)
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

size_t read_from_file_to_char_array(char *file_name, char** buffer){
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

size_t longest_repeating_subtring(char *str, size_t length, char **common){
    size_t i = 0, j = 0, len = 1;
    while(len < length){
        int internal = 0;
        common[0] = CALLOC(char, len+1);
        for (i=0; i<len; i++){
            common[0][i] = str[i];
        }
        for(j = 0; j < length; j++)
        {
            if (str[j] != common[0][j%len]){
                len++;
                internal = 1;
                break;
            }
        }
        if (internal == 0){
            break;
        }
        free(common[0]);   
    }
    return len;
}

int main(){
    
    char plain_text_file[55], cipher_text_file[55];
    printf("Enter the name of the file with plain text (use plain_text.txt): ");
    scanf("%s", plain_text_file);

    printf("Enter the name of the file with cipher text (use cipher_text.txt): ");
    scanf("%s", cipher_text_file);

    char *plain_text;
    size_t plain_size = read_from_file_to_char_array(plain_text_file, &plain_text);
    char *cipher_text;
    size_t cipher_size = read_from_file_to_char_array(cipher_text_file, &cipher_text);

    if (cipher_size != plain_size){
        perror("The two files are not of same size!!\n");
        exit(-1);
    }

    char *result = CALLOC(char, cipher_size);
    // printf("%s\n%s\n", plain_text, cipher_text);
    size_t i = 0,j = 0;
    int value;
    while(i < cipher_size){
        if ((cipher_text[i] > 96) && (cipher_text[i]<123)){
            cipher_text[i] = tolower(cipher_text[i]);
            plain_text[i] = tolower(plain_text[i]);
            value = 0;
            if ((cipher_text[i] - 'a') >= (plain_text[i] - 'a')){
                // printf("%c", (cipher_text[i] - 'a') - (plain_text[i] - 'a'));
                value = 97  + cipher_text[i] - plain_text[i];
                // printf("%c", (char)value);
            }
            else{
                // printf("%c", (26 - ((cipher_text[i] - 'a') - (plain_text[i] - 'a'))));
                value = 97 + (26 - plain_text[i] + cipher_text[i]);
                // printf("%c", (char)value);
            }
            result[j++] = (char)value;
        }
        i++;
    }
    // printf("%s\n", result);

    // subroutine for longest repeating substring
    char *common;
    // int common_size = longest_repeating_subtring(result, j-1, &common);
    // printf("The string for cipher key is obtained is %s\n", result);
    // printf("The cipher key is : %s and its of length : %d\n", common, common_size);

    if (longest_repeating_subtring(result, j-1, &common)){
        printf("%s\n", common);
    }

    return 0;
}