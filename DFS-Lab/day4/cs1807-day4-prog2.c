/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 31 July, 2018
Program description: Check for Strong and Weak password
Acknowledgements: 
------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MALLOC(type, size) (type *)malloc(sizeof(type)* size)
#define COUNT 100
#define LIMIT COUNT*COUNT

int prime[COUNT];

int primeGenerator()
{
    prime[0] = 2;
    int i = 1;
    int j,k;
    int *check;
    check = MALLOC(int, LIMIT);
    for(j=3;j<COUNT;j+=2){
        if(check[j] == 0){
            prime[i] = j;
            i++;
            for( k = j*j; k < LIMIT; k += (2*j) )
                check[k] = 1;
        }
    }
    return 0;
}

int isPrime(int n){
    int i = 0;
    for( i = 0; i < COUNT && prime[i]>0; i++)
    {
        if (n == prime[i])
            return 1;
    }
    return 0;
}

int main()
{
    primeGenerator();
    printf("Enter the password:\n");
    char c = '\0';
    system ("/bin/stty raw -echo");
    int low = 0, cap = 0, symbol = 0, num = 0;
    while(c != 13) {
        c=getchar();
        putchar('?');
        if (ispunct(c) || isblank(c))
            symbol++;
        else if (isalpha(c) && isupper(c))
            cap++;
        else if (isalpha(c) && islower(c))
            low++;
        else if (isdigit(c))
            num++;
    }
    system ("/bin/stty cooked echo");
    printf("\n");
    if ( (symbol > 1) && (cap > 1) && (low > 1) && (num > 1) ){
        if (isPrime(symbol) && isPrime(cap) && isPrime(low) && isPrime(num)){
            printf("Strong Password Entered\n");
        }
    }
    else{
        printf("Weak Password Entered\n");
    }
    return 0;
}
