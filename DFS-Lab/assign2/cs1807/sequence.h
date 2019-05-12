#ifndef _G_COMMON_H_
#define _G_COMMON_H_
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
// #include <ctype.h>
// #include <time.h>
#include <string.h>
#include <assert.h>
#endif

#ifndef _GSEQUENCE_
#define _GSEQUENCE_

#define _INIT_MAX_ELEMENTS_SEQUENCE_ 8

typedef struct sequence{
    void *elements;
    char element_type;
    // size of the type of element stored in the sequence
    size_t num_elements;
    // number of elements currently stored in the sequence
    size_t max_elements;
    // maximum number of elements that can be stored in the sequence
} Sequence;

Sequence *newSequence(char element_type);
void initSequence (Sequence *s, char element_type);
void freeSequence(Sequence *s);
void growSequence(Sequence *s);
void reduceSequence(Sequence *s);
void push(Sequence *s, const void *eptr);
void pop(Sequence *s, void *eptr);
size_t length(Sequence s);
void get_element(Sequence s, size_t position);
void get_element_of_sequence(Sequence s, size_t position);
void summation(Sequence s);
int asciiSum(char *str);
int summation_copy(Sequence s);

#endif  //_GSEQUENCE_


#ifndef _G_MEMORY_ALLOCATION_H_
#define _G_MEMORY_ALLOCATION_H_
#define MALLOC(type, n) (type *)malloc(sizeof(type)*n)
#define CALLOC(type, n) (type *)calloc(sizeof(type), n)
#endif

#ifndef _G_COMPARISION_H_
#define _G_COMPARISION_H_
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif