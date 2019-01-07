/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 24 July, 2018
Program description: Number is strong is sum of factorial of its digits is equal to that number
Acknowledgements:
------------------------------------*/

#include <stdio.h>

int factorial(int n){
    // factorial calculation
    int value = 1;
    for(int i = 1; i <= n; i++)
    {
        value *= i;
    }
    return value;
}

int main(){
    int n;
    printf("Enter the number:\n");
    scanf("%d", &n);
    int sum_of_factorial = 0;
    int temp = n;
    while(temp/10 > 0){
        sum_of_factorial += factorial(temp%10);
        temp = temp/10;
    }
    sum_of_factorial += factorial(temp%10);
    if (sum_of_factorial == n)
        printf("Strong\n");
    else
        printf("Weak\n");
    return 0;
}