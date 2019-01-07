#ifndef _GSTACK_
#define _GSTACK_

#include <stdio.h>

#define _INIT_MAX_ELEMENTS_STACK_ 8

typedef struct {
    void *elements;
    void (*freeElements) (void *);      
    // freeElements is to be defined with the elements of the stack 
    // are not normal int, char, etc.. but are like Node with some special structures inside it 
    size_t element_size;
    // size of the type of element stored in the stack
    size_t num_elements;
    // number of elements currently stored in the stack
    size_t max_elements;
    // maximum number of elements that can be stored in the stack
} Stack;

Stack *newStack(size_t element_size);
void initStack (Stack *s, size_t element_size);
void freeStack(Stack **s);
int isEmpty(const Stack *s);
void push(Stack *s, const void *eptr);
void pop(Stack *s, void *eptr);
void stackGrow(Stack *s);
void stackReduce(Stack *s);
void top(Stack *s, void *eptr);

#endif  //_GSTACK_
