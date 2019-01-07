/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 10 August, 2018
Program description: Calculating the function G 
Acknowledgements:
------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define MALLOC(type, n) (type *)malloc(sizeof(type)*n)

int recursiveG(int n){
    if (n == 0){
        return 0;
    }
    else if (n == 1){
        return 1;
    }
    else if (n == 2){
        return 2;
    }
    else{
        return recursiveG(n-1) + recursiveG(n-2) + recursiveG(n-3);
    }
}


int iterativeG(int n){
    int *G;
    G = MALLOC(int, n+1);
    G[0] = 0;
    if (n >= 1)
        G[1] = 1;
    if (n >= 2)
        G[2] = 2;
    int i;
    for (i=3;i<=n;i++){
        G[i] = G[i-3] + G[i-1] + G[i-2];
    }
    return G[n];
}

int main()
{
    printf("Enter the number n for G(n): ");
    int n;
    scanf("%d", &n);
    printf("The recursive implementation G(%d) : %d\n", n, recursiveG(n));    
    printf("The iterative implementation G(%d) : %d\n", n, iterativeG(n));    
    return 0;
}
