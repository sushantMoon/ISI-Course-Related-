/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 24 July, 2018
Program description: Print string consisting of * of length = fibonacci value corresponding to the line number 
Acknowledgements:
------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n){
    // calculates the nth fibonacci value
    if (n <= 0)
        return 0;
    if (n == 1)
        return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}

int main(){
    int n;
    printf("Enter the number of lines to print:");
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        // create a char array of length fibonacci value of that line number
        int fib = fibonacci(1+i);
        char *c;
        c = (char *)malloc(sizeof(char)*fib);
        // fill the char array with *
        for(int j = 0; j < fib; j++)
        {
            c[j]='*';
        }
        printf("%s\n", c);
    }
    return 0;
}