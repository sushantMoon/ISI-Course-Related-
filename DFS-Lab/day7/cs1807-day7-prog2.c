/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 10 August, 2018
Program description: Combinations :  n choose r  
Acknowledgements:
------------------------------------*/
#include <stdio.h>

int combination(int n , int r){
    if (n < r){
        return 0;
    }
    if (n == 1){
        return 1;
    }
    if (r == 1){
        return n;
    }
    return combination(n-1, r) + combination(n-1, r-1);
}

int main()
{
    int n, r;
    printf("Enter the values n, r (space separated): ");
    scanf("%d %d", &n, &r);
    printf("The ways to choose r from n elements: %d\n", combination(n, r));
    return 0;
}
