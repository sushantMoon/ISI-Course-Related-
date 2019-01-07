#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct emp {
    char name[20];
    char dept[20];
    int salary;
} EMP;

int salaryComparator(EMP *a, EMP *b) { //ascending order
    return a->salary - b->salary;
}

int nameComparator(EMP *a, EMP *b) { //ascending order
    return strcmp(a->name, b->name);
}

void swapemp(EMP *elem1, EMP *elem2) {
    EMP *tmp = (EMP*)malloc(sizeof(EMP));
    *tmp = *elem1; //blind memory copy
    *elem1 = *elem2;
    *elem2 = *tmp;
    free(tmp);
}


//bubble sort
void inPlaceSort(EMP *arr, int elemCount, int (*comparator) (EMP *, EMP *)) {
    int i,j;
    int swapped = 0;
    for(i = 0; i < elemCount-1; i++) {
        for(j = 0; j < elemCount-i-1; j++) {
            if(comparator(&arr[j], &arr[j+1]) > 0) { //ascending order
                swapemp(&arr[j], &arr[j+1]);
                swapped = 1;
            }
        }
        if(! swapped) break;
    }
}

void printArray(EMP *arr, int n) {
    int i;
    for(i = 0; i < n; i++) {
        printf("%s %s %d\n", arr[i].name, arr[i].dept, arr[i].salary);
    }
    putchar('\n');
}

int main() {
    int i;
    EMP arr[10];

    for( i= 0; i<10; i++ ){
          scanf("%s%s%d", arr[i].name, arr[i].dept, &arr[i].salary);  
    }

    inPlaceSort(arr, 10, salaryComparator);
    printArray(arr, 10);

    putchar('\n');
    
    inPlaceSort(arr, 10, nameComparator);
    printArray(arr, 10);
    return 0;
}