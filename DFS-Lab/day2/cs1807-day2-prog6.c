/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 24 July, 2018
Program description: Assign m some value based on certain conditions
Acknowledgements:
------------------------------------*/

#include <stdio.h>

int is_divisible_by_4(int n){
    // Returns 1 if n is divisible by 4, else 0
    int quotient = n >> 2;
    int remainder = n - (quotient*4);
    if (remainder == 0)
        return 1;
    return 0;   
}

int rotate_left(unsigned long int n, int k){
    // Rotate the number bitwise to left
    // rotate bits of n to the left by k places OR rotate bits of n by 32-k positions to right 
    // (to get the bits in the position that were moved out of 32 bit range due to left shift, OR operation will keep the bits that were originally present in the initial k positions to the end of the number)  
    return (n<<k)|(n>>(32-k));
}

int rotate_right(unsigned long int n, int k){
    // Rotate the number bitwise to right
    // rotate bits of n to the right by k places OR rotate bits of n by 32-k positions to left 
    // (to get the bits in the position that were moved out of 32 bit range due to right shift, OR operation will keep the bits that were originally present in the last k positions to the front of the number)  
    return (n>>k)|(n<<(32-k));
}

int main()
{
    unsigned long int n;
    unsigned long int m;
    int k;
    printf("Enter the number n: ");
    scanf("%lu",&n);
    printf("Enter the number k: ");
    scanf("%d",&k);

    // checking if n is even or odd
    int parity = ((n&1)==1);
    m = parity?1:0;
    printf("n is %s, hence m = %lu\n", (parity)?"odd":"even", m);

    // checking for divisibility by 4
    int divisibility = is_divisible_by_4(n);
    m = divisibility?1:0;
    printf("n is %sdivisible by 4, hence m = %lu\n", divisibility?"":"not ", m);

    // assigning m as 2*n if n<=31
    if (n<=31) {
        m = 2 * n;
        printf("n = %lu, hence m = %lu\n", n, m);
    }
    else {
        printf("n should not be greater than 31\n");
    }
    
    // rotation of n by k places by k positions, and k should be >= 0
    if (k>=0) {
        m = rotate_left(n,k);
        printf("Rotating n=%lu to left by k=%d position, we get m=%lu\n",n,k,m);
        m = rotate_right(n,k);
        printf("Rotating n=%lu to right by k=%d position, we get m=%lu\n",n,k,m);
    }
    else
    {
        printf("k should not be less than 0\n");
    }
    
    return 0;
}
