/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 25 Sepetember, 2018
Program description: 

Locating Max Tolerance using :
1. Locate the range using increment in power of 2.
2. Binary Search to locate within the range.

Acknowledgements:
------------------------------------*/
#include "../generic/common.h"

long long int binarySearch(long long int start, long long int end, long long int maxTolerance, int *steps){
    if (start <= end){
        (*steps)++;
        long long int middle = (start + end)/2;
        if (middle == maxTolerance){
            return middle;
        }
        else if (middle < maxTolerance){
            return binarySearch(middle, end, maxTolerance, steps);
        }
        else{
            return binarySearch(start, middle, maxTolerance, steps);
        }
    }
    return -1;
}

int main(){
    int steps=0;
    long long int maxTolerance;
    printf("Enter the Max Tolerance :");
    scanf("%lld", &maxTolerance);

    long long int bp=1;
    while(1){
        if (bp > maxTolerance){
            break;
        }
        bp *= 2;
        steps++;
    }
    printf("The max tolerance that the sheet can handle is : %lld\nTotal Steps taken to calculate are : %d\n", binarySearch(bp/2, bp, maxTolerance, &steps), steps);
    return 0;
}