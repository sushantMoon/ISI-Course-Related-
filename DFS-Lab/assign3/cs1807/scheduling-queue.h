#include "common.h"

#ifndef _G_COMMON_H_
#define _G_COMMON_H_
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#endif

typedef struct Node{
    int time_required;
    int process_id;
}Node;

typedef struct SchedulingQueue{
    Node *elements;
    // Array Implementation
    unsigned int num_elements;
    // total elements in the SchedulingQueue
    unsigned int start;
    // position value of the first element in the SchedulingQueue
    unsigned int end;
    // end is always the position which is just next to the last element in the array
    // position value of the last element in the SchedulingQueue
    unsigned int max_elements;
    // maximum number of elemes at the SchedulingQueue can handle
    unsigned int processes_executed;
    // number of processes scheduled
}SchedulingQueue;

SchedulingQueue *newSchedulingQueue(unsigned int max_elements);
void extract(SchedulingQueue *q, Node *output_pointer);
void push_back(SchedulingQueue *q, Node *input_pointer);
void push_front(SchedulingQueue *q, Node *input_pointer);
SchedulingQueue *create_scheduling_queue_copy(SchedulingQueue *orignal);
void print_scheduling_queue_node(SchedulingQueue *q);
void free_scheduling_queue(SchedulingQueue *q);