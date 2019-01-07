/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 28 August, 2018
Program description: 
The mimic function in number theory 
Run using : gcc -g -Wall cs1807-assign1-prog2.c -o prog2 -lm
Acknowledgements:
------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MALLOC(type, n) (type *)malloc(sizeof(type)*n)
#define CALLOC(type, n) (type *)calloc(sizeof(type), n)
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

int base_conversion_to_10(int N, int base){
    // works of bases less than equal to 10
    int result = 0;
    int i, value;
    i = 0;
    value = N;
    while(value>0){
        result += (value%10) * pow(base, i);
        value /= 10;
        i++;
    }
    return result;
}

int base_conversion_10_to_d(int N, int base){
    // works of bases less than equal to 10
    int result = 0;
    int i, value;
    i = 0;
    value = N;
    while(value>0){
        result += (value%base) * pow(10, i);
        value /= base;
        i++;
    }
    return result;
}

int base_conversion_to_d(int N, int current_base, int new_base){
    // works of bases less than equal to 10
    int result;
    // converting to base 10 first    
    int rep_in_base_10 = base_conversion_to_10(N, current_base);
    result = base_conversion_10_to_d(rep_in_base_10, new_base);
    return result;
}

int mimic_number_calculator(int N, int base, int d){
    int result = 0;
    int f_n_d = N;
    int n;
    printf("%d ", f_n_d);
    while(f_n_d != d && f_n_d > d){
        n = f_n_d;
        f_n_d = 0;
        int i = 0;
        while(n>0){
            f_n_d += (n%10) * pow((base - d), i);
            n /= 10;
            i++;
        }
        result++;
        printf("%d ", f_n_d);
        if (f_n_d == d){
            break;
        }
        f_n_d = base_conversion_to_d(f_n_d, 10, base);
    }
    printf("\n");
    return result;
}

int main(){
    int base, N, d;
    // int base = 8, N = 167, d=7;  
    // int base = 8, N = 1725, d=9;
    // int base = 8, N = 1725, d=9;
    scanf("%d %d %d", &base, &N, &d);
    int base_10_rep = base_conversion_to_10(N, base);
    // int base_d_rep = base_conversion_to_d(N, base, base);
    // printf("%d (in base 8) (i.e %d in base 10) (i.e %d in base %d) divided by %d = %lf\n", N, base_10_rep, base_d_rep, base, d, (double)base_10_rep/(double)d );
    
    if (base_10_rep%d != 0){
        printf("-1\n");
        return 0;
    }
    printf("%d\n",mimic_number_calculator(N, base, d));
    
    return 0;
}
