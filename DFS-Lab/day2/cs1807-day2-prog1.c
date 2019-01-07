/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 24 July, 2018
Program description: Print max, if the numbers are not same (no use of relational operators)
Acknowledgements:
------------------------------------*/

#include <stdio.h>

int main()
{
    int a,b;
    printf("Enter two numbers (space seperated): ");
    scanf("%d %d", &a, &b);
    if (!(a^b)){
        printf("Numbers are same\n");
    }
    else{
        int n1 = a/b;
        if (n1){
            printf("Maximum Number : %d\n",a);
        }
        else {
            printf("Maximum Number : %d\n",b);
        }
    }
    return 0;
}