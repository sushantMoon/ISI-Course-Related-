/*-----------------------------------
Name: Sushant Sharad Moon
Roll number: MTC1807
Date: 20 July, 2018
Program description: Implementations for strlen, strcmp and differByOne
Acknowledgements:
------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int strleng(char *s){
    // int count;
    // for (int i=0 ; i<SIZE ; i++){
    //     if (s[i] == '\n' || s[i] == '\0')
    //     {
    //         count = i;
    //         break;
    //     }
    // }
    // return count;

    int j;
    for(j = 0; s[j] != '\0'; j++);
    return j;
}

int strcmp(char *s, char *t){
    while(*s && (*s==*t))
        s++,t++;
    if (*s - *t == 0){
        return 1;
    }
    return 0;
}

int diffByOne(char *s, char *t){
    int differ = 0;
    while(*s && *t){
        if (*s != *t)
            differ += 1;
        s++;
        t++;
    }
    if (*s && !*t){
        while(*s)
        {
            differ += 1;
            s++;
        }
    }
    if (!*s && *t){
        while(*t)
        {
            differ += 1;
            t++;
        }
    }
    return differ;
}

int main()
{
    char *s = (char *) malloc(sizeof(char)*SIZE);   //remember : the values are initialized to \0  
    char *t = (char *) malloc(sizeof(char)*SIZE);  
    printf("Enter the String S (max length 100) : ");
    scanf("%s", s);
    // printf("\n");
    printf("Enter the String T (max length 100) : ");
    scanf("%s", t);
    // printf("\n");

    printf("Lenght of S : %d\n", strleng(s));
    printf("Lenght of T : %d\n", strleng(t));

    printf("Comparing S and T : ");
    
    if (strcmp(s,t)) {
        printf("S and T are exactly the same\n");
    }
    else {
        printf("S and T have differences\n");
    }

    printf("Comparing for One Difference S and T : ");
    int difference = diffByOne(s, t);
    if (difference == 1){
        printf("S and T are differ by exactly one character\n");
    }
    if (difference > 1){
        printf("S and T are differ by many character\n");
    }
    if (difference == 0){
        printf("S and T are same\n");
    }
    return 0;
}
