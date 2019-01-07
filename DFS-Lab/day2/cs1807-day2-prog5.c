/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 24 July, 2018
Program description: Logical Conditions evaluating to certain conditions as mentioned
Acknowledgements:
------------------------------------*/

#include <stdio.h>
#include <math.h>

int is_float_addition_int(float x, float y){
    // returns 1 if x+y is an integer, else 0
    float sum = x + y;
    float decimals = sum - (int)sum;
    if (decimals > 0){
        return 0;
    }
    return 1;
}

int is_m_strictly_between_x_y(int m, float x, float y){
    // returns 1 if x < m < y, else 0
    if ((x < m) && (m < y)){
        return 1;
    }
    return 0;
}

int is_m_equal_integer_of_x(int m, float x){
    // returns 1 if m is equal to integer part of x, else 0
    if ( m == (int)x) {
        return 1;
    }
    return 0;
}

int condition_on_x(float x){
    // returns 1 if integer part x >=3 and decimal part of x less than 0.3 
    if( ( (int)x >= 3 ) && ( (x-(int)x) < 0.3 ) ){
        return 1;
    }
    return 0;
}

int parity_check(int m, int n){
    // returns 1 if parity of m and n is same
    if ((m&1) == (n&1))
        return 1;
    return 0;   
}

int perfect_square_check(int m){
    // returns 1 is m is perfect square
    double root = sqrt(m);
    if (root == (int)root)
        return 1;
    return 0;
}

int main()
{
    int m,n;
    float x,y;
    printf("Enter the two int numbers m & n: ");
    scanf("%d %d", &m, &n);
    printf("Enter the two float numbers x & y: ");
    scanf("%f %f", &x, &y);
    printf("x + y is %sinteger\n", is_float_addition_int(x,y)?"":"not ");
    printf("Is m strictly between x & y => %s\n", is_m_strictly_between_x_y(m,x,y)?"Yes":"No");
    printf("Is m equal to integer part of x => %s\n", is_m_equal_integer_of_x(m, x)?"Yes":"No");
    printf("Is (Int Part)X >= 3 and (Decimal Part)X < 0.3 => %s\n", condition_on_x(x)?"Yes":"No");
    printf("Does m & n have same parity => %s\n", parity_check(m, n)?"Yes":"No");
    printf("Is m perfect square => %s\n", perfect_square_check(m)?"Yes":"No");
    return 0;
}
