/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 27 July, 2018
Program description: Logical Operations for complex numbers implemented using structures
Acknowledgements:
------------------------------------*/

#include <stdio.h>

struct number
{
    int real;
    int imaginery;
};

int is_sum_imaginery(struct number x, struct number y){
    int real = x.real + y.real;
    int imaginery = x.imaginery + y.imaginery;
    if (imaginery == 0)
        return 0;
    else if(real == 0)
        return 1;
    return 0;
}

int are_conjugate(struct number x, struct number y){
    if ( (x.real == y.real) && (x.imaginery + y.imaginery == 0) )
        return 1;
    return 0;
}

int are_real(struct number x, struct number y){
    if ( ( x.imaginery  == 0 ) && ( y.imaginery == 0 ) )
        return 1;
    return 0;
}

int main(){
    struct number x;  
    struct number y;
    printf("Enter the real and imaginery part of x (space seperated) :\n");
    scanf("%d %d",&(x.real),&(x.imaginery)); 
    printf("Enter the real and imaginery part of y (space seperated) :\n");
    scanf("%d %d",&(y.real),&(y.imaginery));

    printf("The sum x+y is %simaginery\n",(is_sum_imaginery(x,y)==0)?"not ":"");
    printf("x and y are %scomplex conjugate\n",(are_conjugate(x,y)==0)?"not ":"");
    printf("x and y both are %sreal\n",(are_real(x,y)==0)?"not ":"");

    return 0;
}