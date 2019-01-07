/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 7 August, 2018
Program description: Reverse the content of the file provided.
Acknowledgements:
------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 250000
#define MALLOC(type, size) (type *)malloc(sizeof(type)*size)

int main()
{
    clock_t start = clock();
    FILE *fp;
    char *buffer;
    long int bsize;
    int i;
    fp = fopen("indentation.html", "rb");
    if (fp == NULL){
        printf("File Not Available\n");
        return 0;
    }
    // moving the pointer to the end of the file
    fseek(fp, 0, 2);
    // storing the size of the file;
    bsize = ftell(fp);
    // rewinding to the starting of the file
    rewind(fp);

    buffer = MALLOC(char, bsize);
    if (buffer == NULL){
        printf("Memory Allocation failed !!\n");
        return 0;
    }

    size_t result = fread(buffer, 1, bsize, fp);
    
    if (result != bsize) {
        printf("Reading Error !!\n");
        return 0;
    }
    fclose(fp);

    fp = fopen("reverse-indentation.html", "w");
    if (fp != NULL){
        for(i = bsize-1; i >= 0; i--)
        {
            fputc(buffer[i],fp);
        }
    }
    else{
        printf("Error in opening the output file\n");
    }
    fclose(fp);
    clock_t end = clock();
    printf("Total time Taken to reverse the html file %lf\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    return 0;
}
