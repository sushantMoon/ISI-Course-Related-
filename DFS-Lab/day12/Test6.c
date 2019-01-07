#include<stdio.h>

void func1();
void func2();

int main(){
    int i = 10;
    function1();
    printf("In main(): %d\n", i);
}

void function1(){
    int n = 20;
    printf("In function1(): %d\n",n);
    function2();
}

void function2(){
    int n = 30;
    printf("In function2() : %d\n",n);
    main();
}
