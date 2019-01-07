#include "common.h"
#include "stack.h"
// #include "linkedlist.h"


Stack *newStack(size_t element_size){
    Stack *s = MALLOC(Stack, 1);
    assert(s != NULL);
    initStack(s, element_size);
    return s;
}

void initStack (Stack *s, size_t element_size){
    assert(s != NULL);
    s->element_size = element_size;
    // size of the type of element stored in the stack

    s->max_elements = _INIT_MAX_ELEMENTS_STACK_;
    // maximum number of elements that can be stored in the stack
    
    s->num_elements = 0;
    // number of elements currently stored in the stack
    
    s->elements = malloc(element_size*_INIT_MAX_ELEMENTS_STACK_);
}

void freeStack(Stack **s){
    // It expects pointer to pointer to the stack
    if ((*s)->freeElements != NULL){
        // freeElements is to be defined with the elements of the stack 
        // are not normal int, char, etc.. but are like Node with some special structures inside it 
        int i;
        for(i=0; i<(*s)->num_elements;i++){
            (*s)->freeElements((char *)(*s)->elements+(i*(*s)->element_size));
        }
    }
    free((*s)->elements);
    (*s)->num_elements = 0;
    free(*s);
    *s = NULL;
}

int isEmpty(const Stack *s){
    // returns 0 if not empty
    if(s->num_elements == 0){
        return 1;
    }
    return 0;
}

void stackGrow(Stack *s){
    s->max_elements = s->max_elements * 2;
    s->elements = realloc(s->elements, (s->element_size)*(s->max_elements));
    assert(s != NULL);
}

void push(Stack *s, const void *eptr){
    assert(s != NULL);

    //stackgrow function
    if (s->num_elements == s->max_elements){
        stackGrow(s);
    }
    assert(s->num_elements < s->max_elements);

    // for diff debug
    // printf("Node being pushed in the stack is :%d \n", *(int *)((*(Node *)eptr).data));  // uncomment include <linkedlist.h>
    // printf("Int being pushed in the stack is :%d \n", *(int *)eptr);
    // printf("Pushing address location: %d\n", (int)s->num_elements);

    void *targetAddress = s->elements + (s->num_elements * s->element_size);
    memcpy(targetAddress, eptr, s->element_size);
    s->num_elements += 1;
}

void stackReduce(Stack *s){
    s->max_elements = s->max_elements / 2;
    s->elements = realloc(s->elements, (s->element_size)*(s->max_elements));
    assert(s != NULL);
}

void pop(Stack *s, void *eptr){
    assert(s != NULL);
    assert(s->num_elements != 0);
    // stackreduce function
    if (s->num_elements <= (s->max_elements/4)){
        stackReduce(s);
    }
    int offset = s->num_elements - 1;
    // printf("Pop address offset : %d\n", offset);
    void *popAddress = s->elements + ( offset * s->element_size );
    memcpy(eptr, popAddress, s->element_size);
    s->num_elements -= 1;
}

void top(Stack *s, void *eptr){
    // unchecked // test properly
    assert(s != NULL);
    assert(s->num_elements != 0);
    int offset = s->num_elements - 1;
    void *topAddress = s->elements + ( offset * s->element_size );
    memcpy(eptr, topAddress, s->element_size);
}