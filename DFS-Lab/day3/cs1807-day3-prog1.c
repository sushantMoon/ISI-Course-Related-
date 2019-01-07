/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 27 July, 2018
Program description: Print The total number matches of pattern B in A
Acknowledgements:
------------------------------------*/

#include <stdio.h>
#include <stdlib.h>


int comparator(const void *p, const void *q){
    int l = *(int *)p;
    int r = *(int *)q;
    return l-r;
}

void longest_prefix(int m, int *pattern, int *lps)
{
    int length = 0;
    int i=1;
    lps[0] = 0;
    while(i < m){
        
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        }
        else {
            
            if (length != 0) {
                length = lps[length-1];
            }
            else {
                lps[i] = 0;
                i++;
            }
            
        }
        
    }
}

int kmp(int n, int m, int *a, int *b, int *lps){
    int i = 0;
    int j = 0;
    int count = 0;
    while(i < n){
        
        if (b[j] == a[i]) {
            i++;
            j++;
        }
        
        if (j == m) {
            count++;
            j = lps[j-1];
        }
        
        else if (i < n && b[j] != a[i]){
            
            if (j != 0) {
                j = lps[j-1];
            }
            else {
                i++;
            }
            
        }
        
    }
    return count;
}

int main()
{   
    int *a, *b, *lps;
    int n, m;
    int i = 0, j =0, flag =0;
    printf("Enter the size of list a : ");
    scanf("%d", &n);
    a = (int *)malloc(sizeof(int) * n);
    printf("Enter the elements of list a (Press enter after every element) : \n");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
        
    printf("Enter the size of list b : ");
    scanf("%d", &m);
    b = (int *)malloc(sizeof(int) * m);
    lps = (int *)malloc(sizeof(int) * m);
    printf("Enter the elements of list b (Press enter after every element) : \n");
    for(i = 0; i < m; i++)
    {
        scanf("%d", &b[i]);
    }
    
    longest_prefix(m, b, lps);

    int count = kmp(n, m, a, b, lps);

    printf("The total number of pattern B in A are : %d\n", count);
    
    
    qsort(a, n, sizeof(a[0]), comparator);
    qsort(b, m, sizeof(b[0]), comparator);

    j = 0;
    for(i = 0; i < n; i++)
    {
        if ((a[i] != b[j]) || (j>m)) {
            flag = 1;
            break;
        }
        j++;   
    }

    printf("The MultiSet of A and be are %ssame.\n",(flag)?"not ":"");
    
    free(b);
    free(a);
    return 0;
}