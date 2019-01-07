/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 24 July, 2018
Program description: Roots of quadratic equation
Acknowledgements: use -lm when compiling 
------------------------------------*/

#include <stdio.h>
#include <math.h>


struct Complex
{
    double real;
    double complex;
};

int main(){
    int a, b, c;
    printf("Enter a, b, c space seperated\n");
    scanf("%d %d %d", &a, &b, &c);
    int complex = 0;
    double D = (b*b) - (4*a*c);
    if (D < 0){
        D *= -1;
        complex = 1;
    }
    double rootD = sqrt(D);
    printf("The roots for %d x^2 + %d x + %d = 0 are :\n", a, b, c);
    if (complex){
        // struct Complex c1;
        struct Complex c2;
        // c1.real = (-1*b)/(2*a);
        c2.real = (-1*b)/(2*a);
        // c1.complex  = (-1 * rootD)/(2*a);
        c2.complex  = rootD/(2*a);
        printf("%f + %f i & %f - %f i\n", c2.real, c2.complex, c2.real, c2.complex);
    }
    else{
        printf("%f & %f\n",((-1*b) - rootD)/(2*a), ((-1*b) + rootD)/(2*a));    
    }
    return 0;
}
