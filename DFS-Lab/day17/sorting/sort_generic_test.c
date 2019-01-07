#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include"sort_generic.h"

typedef struct emp {
    char name[20];
    char dept[20];
    int salary;
} EMP;

int salaryComparator(void *a, void *b) { //ascending order
    EMP *x = (EMP*)a;
    EMP *y = (EMP*)b;
    return x->salary - y->salary;
}

int nameComparator(void *a, void *b) { //ascending order
    EMP *x = (EMP*)a;
    EMP *y = (EMP*)b;
    return strcmp(x->name, y->name);
}

void printEMPArray(EMP *arr, int n) {
    int i;
    for(i = 0; i < n; i++) {
        printf("%s %s %d\n", arr[i].name, arr[i].dept, arr[i].salary);
    }
    putchar('\n');
}

int intComparator(void *a, void *b) {
    int *x = (int*)a;
    int *y = (int*)b;
    return *x - *y;
}

void printIntArray(int *arr, int n) {
    int i;
    for(i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

int main() {
    int i;
    int array[] = {32, 23, 24, 46, 57, 26, 75}; //7 elements
    inPlaceSort(array, 7, sizeof(int), intComparator);
    printIntArray(array, 7);
    
    putchar('\n');
    
    EMP arr[10];
    for( i= 0; i<10; i++ ){
          scanf("%s%s%d", arr[i].name, arr[i].dept, &arr[i].salary);  
    }

    inPlaceSort(arr, 10, sizeof(EMP), salaryComparator);
    printEMPArray(arr, 10);

    putchar('\n');
    
    inPlaceSort(arr, 10, sizeof(EMP), nameComparator);
    printEMPArray(arr, 10);
    return 0;
}