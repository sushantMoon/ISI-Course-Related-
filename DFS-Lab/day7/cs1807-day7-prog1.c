/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 10 August, 2018
Program description: Tower of Hanoi
Acknowledgements:
------------------------------------*/
#include <stdio.h>

int pro_move(int n, char s, char t, char a){
    
    if (n == 0) {
        printf("Moving Disk %d from %c to %c\n", 0, s, t );
        return 0;
    }
    pro_move(n-1, s, a, t);
    printf("Moving Disk %d from %c to %c\n", n, s, t );
    pro_move(n-1, a, t, s);
    return 0;
}

int main()
{
    int n = 4;
    pro_move(n, 'A', 'C', 'B');    
    return 0;
}