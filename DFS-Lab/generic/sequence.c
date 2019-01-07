#include "sequence.h"

Sequence *newSequence(char element_type){
    if (element_type == 'i' || element_type == 'f' || element_type == 's'){
        Sequence *s = MALLOC(Sequence, 1);
        assert(s != NULL);
        initSequence(s, element_type);
        return s;
    }
    else{
        printf("Please enter valid option for the Sequence Elements\ni for Integers, f for Floats, s for Strings(Char *)\n");
        return NULL;
    }
}

static void initSequence(Sequence *s, char element_type){
    assert(s != NULL);
    s->element_type = element_type;
    // size of the type of element stored in the Sequence

    s->max_elements = _INIT_MAX_ELEMENTS_SEQUENCE_;
    // maximum number of elements that can be stored in the Sequence
    
    s->num_elements = 0;
    // number of elements currently stored in the Sequence
    if (s->element_type == 'i' || s->element_type == 'f'){
        s->elements = malloc(sizeof(int)*_INIT_MAX_ELEMENTS_SEQUENCE_);
    }
    else if (s->element_type == 's'){
        s->elements = malloc(sizeof(char *)*_INIT_MAX_ELEMENTS_SEQUENCE_);
    }
    else{
        return;
    }
}

void freeSequence(Sequence *s){
    free(s->elements);
    s->num_elements = 0;
    free(s);
}

static void reduceSequence(Sequence *s){
    s->max_elements = s->max_elements / 2;

    if (s->element_type == 'i' || s->element_type == 'f'){
        s->elements = realloc(s->elements,(sizeof(int)*(s->max_elements)));
    }
    else if (s->element_type == 's'){
        s->elements = realloc(s->elements, (sizeof(char *)*(s->max_elements)));
    }

    assert(s != NULL);
}

static void growSequence(Sequence *s){
    s->max_elements = s->max_elements * 2;

    if (s->element_type == 'i' || s->element_type == 'f'){
        s->elements = realloc(s->elements,(sizeof(int)*(s->max_elements)));
    }
    else if (s->element_type == 's'){
        s->elements = realloc(s->elements, (sizeof(char *)*(s->max_elements)));
    }
    
    assert(s != NULL);
}

size_t length(Sequence s){
    return s.num_elements;
}

int asciiSum(char *str){
    int i=0,value = 0;
    while(str[i] != '\0'){
        value += (int)str[i];
        i++;
    }
    return value;
}

void get_element(Sequence s, size_t position){
    if(s.num_elements == 0){
        printf("The Sequence is Empty\n");
        return;
    }
    if (position > s.num_elements || position < 0){
        printf("The position does not exists in the sequence!!\n");
        return;
    }
    if (s.element_type == 'i'){
        printf("%d\n", ((int *)s.elements)[position]);
    }
    else if (s.element_type == 'f'){
        printf("%d\n", (int)round(((float *)s.elements)[position]));
    }
    else if (s.element_type == 's'){
        char *str = (char *)(s.elements + (position * sizeof(char *)));
        printf("%d\n", asciiSum(str));
    }
}

void summation(Sequence s){
    if(s.num_elements == 0){
        printf("0\n");
        return;
    }
    int i=0, value=0;
    for(i=0;i<s.num_elements;i++){
        if (s.element_type == 'i'){
            value += ((int *)s.elements)[i];
        }
        else if (s.element_type == 'f'){
            value += (int)round(((float *)s.elements)[i]);
        }
        else if (s.element_type == 's'){
            char *str = (char *)(s.elements + (i * sizeof(char *)));
            value += asciiSum(str);
        }
    }
    printf("%d\n", value);
}


int summation_copy(Sequence s){
    if(s.num_elements == 0){
        return 0;
    }
    int i=0, value=0;
    for(i=0;i<s.num_elements;i++){
        if (s.element_type == 'i'){
            value += ((int *)s.elements)[i];
        }
        else if (s.element_type == 'f'){
            value += (int)round(((float *)s.elements)[i]);
        }
        else if (s.element_type == 's'){
            char *str = (char *)(s.elements + (i * sizeof(char *)));
            value += asciiSum(str);
        }
    }
    return value;
}

void push(Sequence *s, const void *eptr){
    if(s == NULL){
        printf("The Sequence needs to be provided !!\n");
        return;
    }

    if (s->num_elements == s->max_elements){
        growSequence(s);
    }
    // assert(s->num_elements < s->max_elements);

    // for diff debug
    // printf("Node being pushed in the stack is :%d \n", *(int *)((*(Node *)eptr).data));  // uncomment include <linkedlist.h>
    // printf("Int being pushed in the stack is :%d \n", *(int *)eptr);
    // printf("Pushing address location: %d\n", (int)s->num_elements);

    size_t element_size = 0;
    if (s->element_type == 'i' || s->element_type == 'f'){
        element_size = sizeof(int);
    }
    else if (s->element_type == 's'){
        element_size = sizeof(char *);
    }
    else{
        return;
    }
    void *targetAddress = s->elements + (s->num_elements * element_size);
    memcpy(targetAddress, eptr, element_size);
    s->num_elements += 1;
}


void pop(Sequence *s, void *eptr){
    if(s == NULL){
        printf("The Sequence needs to be provided !!\n");
        return;
    }
    if(s->num_elements == 0){
        printf("The Sequence is empty!!\n");
        return;
    }

    if (s->num_elements <= (s->max_elements/4)){
        reduceSequence(s);
    }
    // printf("Pop address offset : %d\n", offset);
    size_t element_size = 0;
    if (s->element_type == 'i' || s->element_type == 'f'){
        element_size = sizeof(int);
    }
    else if (s->element_type == 's'){
        element_size = sizeof(char *);
    }
    else{
        return;
    }
    void *popAddress = s->elements + ( (s->num_elements - 1) * element_size );
    memcpy(eptr, popAddress, element_size);
    s->num_elements -= 1;
}
