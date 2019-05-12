/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 10 August, 2018
Program description: Calculating the function f's behaviour
Acknowledgements:
------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define MALLOC(type, n) (type *)malloc(sizeof(type)*n)



int f ( int n )
{
int s = 0;
while (n--) s += 1 + f(n);
return s;
}

int main(int argc, char const *argv[])
{
    int n;
    printf("Enter the number n for f(n) : ");
    scanf("%d", &n);
    printf("The value for f(%d) = %d\n", n, f(n));
    return 0;
}

