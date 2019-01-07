/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 27 July, 2018
Program description: Get Highest and second highest with upper bound on number of comparisions 2n+3
Acknowledgements:
------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define MALLOC(type, size) (type *)malloc(sizeof(type)*size)

int count;
int *divide_and_conquor(int *a, int low, int high){
    int *r , *l, *result;
    r = MALLOC(int, 2);
    l = MALLOC(int, 2);
    result = MALLOC(int, 2);

    if (high - low == 1){
        count += 1;
        if (a[high] >= a[low]){
            result[0]=a[high];
            result[1]=a[low];
        }
        else{
            result[0]=a[low];
            result[1]=a[high];
        }
        return result;
    }
    else if (high - low == 2){
        l = divide_and_conquor(a, low, low+1);
        
        if (l[0] < a[high]) {
            count += 1;
            l[1] = l[0];
            l[0] = a[high];
        }
        
        else if (l[1] < a[high]) {
            count += 2;
            l[1] = a[high];
        }
        return l;
        
    }
    else{
        int mid = (int)((high+low)/2);
        l = divide_and_conquor(a, low, mid);
        r = divide_and_conquor(a, mid+1, high);
        if(r[0] > l[0]) {
            count += 1;
            result[0] = r[0];
            result[1] = (r[1]>=l[0])?r[1]:l[0];
        }
        else if(r[0] < l[0]) {
            count += 2;
            result[0] = l[0];
            result[1] = (r[0]<=l[1])?l[1]:r[0];
        }
        else {
            count += 2;
            result[0] = r[0];
            result[1] = (r[1]>=l[1])?r[1]:l[1];
        }
        return result;
    }
}

int main()
{
    count = 0;
    int *a, n, i=0;
    printf("Enter the size in the array :\n");
    scanf("%d",&n);
    a = MALLOC(int, n);
    printf("Enter the numbers (followed by enter) :\n");
    for(i=0;i<n;i++)
        scanf("%d",a+i);
    int *results = divide_and_conquor(a, 0, n-1);
    printf("Highest number is :%d\n", *results);
    printf("Second Highest number is :%d\n", *(results+1));
    printf("Total Comparisions :%d\n", count);
    free(a);
    return 0;
}
