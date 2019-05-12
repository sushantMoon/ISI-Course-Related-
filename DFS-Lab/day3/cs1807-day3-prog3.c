/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 27 July, 2018
Program description: Concatinate strings and check for palindrome
Acknowledgements:
------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#define MALLOC(type, size) (type *)malloc(sizeof(type)*size)

int palindrome(char *a, int low, int high){
    if (high - low >= 2){
        if( *(a+low) == *(a+high) )
        {
            low++;
            high--;
            return palindrome(a, low, high);
        }
        else
            return 0;
    }
    else if (high - low == 1){
        if (*(a+low) == *(a+high))
            return 1;
        else
            return 0;
    }
    else if (low == high) {
        if (*(a+low) == *(a+high))
            return 1;
        else
            return 0;
    }
    return 0;
}


int main()
{
    char* a;
    a = MALLOC(char, 100);
    printf("Enter the string A (max length 100):\n");
    scanf("%s",a);

    char* b;
    b = MALLOC(char, 100);
    printf("Enter the string B (max length 100):\n");
    scanf("%s",b);

    int i = 0, j=0;
    while(*(a+i) != '\0'){
        i++;
    }
    while(*(b+j) != '\0'){
        *(a+i) = *(b+j);
        j++;
        i++;
    }
    *(a+i) = '\0';
    if(palindrome(a, 0, i-1) == 1)
        printf("Yes its a palindrome\n");
    else
        printf("No its not a palindrome\n");
    return 0;
}
