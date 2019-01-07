/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 1 October, 2018
Program description: 
Traversal in n dimension, positions reachable within k steps 

Compiling using : gcc -g -Wall cs1807-assign2-prog3.c -o prog3 -lm
Run using :
```
./prog3 4 2
```

Recursion formula used is :
F(n,k) = F(n-1, k) + 2*(summation F(n-1,i) where i goes from 0 to k-1)


Acknowledgements:
------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#define MALLOC(type, n) (type *)malloc(sizeof(type)*n)
#define CALLOC(type, n) (type *)calloc(sizeof(type),n)





int main(int argc, char const *argv[]){
    int i,j,k,n;
    if (argc < 3){
        printf("The format is ./prog3 {n} {k}\n");
        return 0;
    }
    k = atoi(argv[2]);
    n = atoi(argv[1]);
    long long int **d = CALLOC(long long int *, n+1);
    for(i=0; i<=n; i++){
        d[i] = CALLOC(long long int, k+1);
    }
    for(i=0; i<=n; i++){
        d[i][0] = 1;
    }
    for(j=0; j<=k; j++){
        d[0][j] = (2*j) + 1; // though not necessary
        d[1][j] = (2*j) + 1;
    }
    for(i=2; i<=n; i++){
        for(j=1; j<=k; j++){
            long long int sum = 0;
            int l=j-1;
            while(l>=0){
                sum += d[i-1][l];
                l -= 1;
            }
            d[i][j] = d[i-1][j] + (2*sum);
        }
    }    

    printf("%lld\n", d[n][k]);
    for(i=0; i<=n; i++){
        free(d[i]);
    }
    free(d);
    return 0;
}
