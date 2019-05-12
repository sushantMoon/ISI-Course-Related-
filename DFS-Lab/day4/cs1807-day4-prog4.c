/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 31 July, 2018
Program description: Word Frequency from 1 file to another
Acknowledgements:
------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MALLOC(type, size) (type *)malloc(size*sizeof(type))
#define TOTALWORDS 100
#define WORDSIZE 100

int main()
{
    char **words1, **words2;
    int count1[TOTALWORDS]={0}, count2[TOTALWORDS]={0}, i, j;
    FILE *fp;
    char c, *buffer;
    char filename[WORDSIZE];

    words1 = MALLOC(char *, TOTALWORDS);
    for( i = 0; i < TOTALWORDS; i++)
        words1[i] = MALLOC(char, WORDSIZE);
    
    words2 = MALLOC(char *, TOTALWORDS);
    for( i = 0; i < TOTALWORDS; i++)
        words2[i] = MALLOC(char, WORDSIZE);

    buffer = MALLOC(char, WORDSIZE);
    printf("Enter the name of the file 1:\n");
    scanf("%s", filename);

    fp = fopen(filename,"r");
    // fp = fopen("file1","r");
    if (fp == NULL){
        printf("PLease enter a valid name..\n");
        return 0;
    }
    i = 0;
    while(1){
        c = fgetc(fp);
        // printf("%c", c);
        if ((c == ' ') || (c == EOF)){
            buffer[i] = '\0';
            for( j = 0; j < TOTALWORDS; j++)
            {
                if (count1[j] > 0 && (strcmp(words1[j], buffer) == 0)){
                    count1[j] += 1;
                    break;
                }
                else if (count1[j] == 0){
                    strcpy(words1[j], buffer);
                    count1[j] = 1;
                    break;
                }
            }
            free(buffer);
            buffer = MALLOC(char, WORDSIZE);
            i = 0;
        }
        if (c == EOF){
            break;
            free(buffer);
            fclose(fp);
        }
        if (((64 < (int)c) && ((int)c < 91)) || ((96 < (int)c) && ((int)c < 123))){
            buffer[i] = c;
            i++;
        }
    }

    buffer = MALLOC(char, WORDSIZE);
    printf("Enter the name of the file 2:\n");
    scanf("%s", filename);

    fp = fopen(filename,"r");
    // fp = fopen("file2","r");
    if (fp == NULL){
        printf("PLease enter a valid name..\n");
        return 0;
    }
    i = 0;
    while(1){
        c = fgetc(fp);
        // printf("%c", c);
        if ((c == ' ') || (c == EOF)){
            buffer[i] = '\0';
            for( j = 0; j < TOTALWORDS; j++)
            {
                if (count2[j] > 0 && (strcmp(words2[j], buffer) == 0)){
                    count2[j] += 1;
                    break;
                }
                else if (count2[j] == 0){
                    strcpy(words2[j], buffer);
                    count2[j] = 1;
                    break;
                }
            }
            free(buffer);
            buffer = MALLOC(char, WORDSIZE);
            i = 0;
        }
        if (c == EOF){
            break;
            free(buffer);
            fclose(fp);
        }
        if (((64 < (int)c) && ((int)c < 91)) || ((96 < (int)c) && ((int)c < 123))){
            buffer[i] = c;
            i++;
        }
    }

    printf("Frequency of words of File 1 in File 2: \n");
    for(i = 0; i < TOTALWORDS; i++)
    {
        if (count1[i] > 0){
            int flag = 0;
            for(j = 0; j < TOTALWORDS; j++)
            {
                if (count2[j] > 0){
                    if (strcmp(words1[i],words2[j])==0){
                        flag = 1;
                        printf("%s : %d\n", words1[i], ( (count1[i]>count2[j]) ? count2[j] : count1[i] ));
                        break;
                    }
                }
            }
            if (flag == 0){
                printf("%s : %d\n", words1[i], 0);
            }
        }
    }

    printf("Frequency of words of File 2 in File 1: \n");
    for(i = 0; i < TOTALWORDS; i++)
    {
        if (count2[i] > 0){
            int flag = 0;
            for(j = 0; j < TOTALWORDS; j++)
            {
                if (count1[j] > 0){
                    if (strcmp(words2[i],words1[j])==0){
                        flag = 1;
                        printf("%s : %d\n", words2[i], ( (count1[i]>count2[j]) ? count2[j] : count1[i] ));
                        break;
                    }
                }
            }
            if (flag == 0){
                printf("%s : %d\n", words2[i], 0);
            }
        }
    }
    
    free(words1);
    free(words2);
    return 0;
}
