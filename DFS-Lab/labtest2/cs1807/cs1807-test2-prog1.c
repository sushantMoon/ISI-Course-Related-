/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 20 September, 2018
Program description:

Leaky Stack

Acknowledgements:
------------------------------------*/
#include "common.h"

typedef struct {
    int *elements;
    int num_elements;
    int max_elements;
    int tolerance;
    int count;
} Stack;

void displayStack(Stack *s){
    int i;
    for(i=(s->num_elements)-1; i>-1; i--){
        printf("%d ", s->elements[i]);
    }
    printf("\n");
}

void leak(Stack *s){
    int i;
    if (s->count == s->tolerance){
        s->count = 0;
        int last = s->num_elements - 1;
        for(i=1;i<s->num_elements;i++){
            s->elements[i-1] = s->elements[i];
        }
        s->elements[last] = 0;
        if (s->num_elements > 0)
            s->num_elements--;
    }
}

void pop(Stack *s){
    if (s == NULL){
        printf("Stack Pointer cannot be NULL, stack seems to be deleted!!\n");
        return;
    }
    s->count++;
    if(s->num_elements == 0){
        //underflow not being reported
        displayStack(s);
        return;
    }
    s->elements[s->num_elements - 1] = 0;
    s->num_elements -= 1;
    leak(s);
    displayStack(s);
}

void push(Stack *s, int value){
    if (s == NULL){
        printf("Stack Pointer cannot be NULL, stack seems to be deleted!!\n");
        return;
    }
    s->count++;
    if(s->num_elements >= s->max_elements){
        // overflow is not reported.
        leak(s);
        displayStack(s);
        return;
    }
    s->elements[s->num_elements] = value;
    s->num_elements += 1;
    leak(s);
    displayStack(s);
}

void initStack (Stack *s, int max_elements, int tolerance){
    assert(s != NULL);
    s->max_elements = max_elements;
    s->num_elements = 0;
    s->elements = CALLOC(int,max_elements);
    s->tolerance = tolerance;
    s->count = 0;
}

Stack *newStack(int max_elements, int tolerance){
    Stack *s = MALLOC(Stack, 1);
    assert(s != NULL);
    initStack(s, max_elements, tolerance);
    return s;
}


int main(){
    int tolerance;
    int size;
    scanf("%d %d", &size, &tolerance);
    Stack *s = newStack(size, tolerance);
    while(1){
        char str;
        int operation = -1;
        int value = 0;
        while(1){
            str = getchar();
            if (str == '+'){
                operation = 1;
            }
            else if (str == '-'){
                operation = 0;
                break;
            }
            else if ((str != '\n') && (str != ' ')){
                value = value*10 + (str - '0');
            }
            else if (str == '\n'){
                break;
            }
        }
        if (operation == 1){
            push(s, value);
        }
        if (operation == 0){
            pop(s);
        }
        
    }

    return 0;
}