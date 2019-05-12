#include "common.h"
#include "scheduling-queue.h"


SchedulingQueue *newSchedulingQueue(unsigned int max_elements){
    SchedulingQueue *q = MALLOC(SchedulingQueue, 1);
    if (q == NULL){
        printf("newSchedulingQueue : Failed to allot heap memory when initialising the queue");
        // return NULL;
        exit(-1);
    }
    q->num_elements = 0;
    (q->start) = 0;
    (q->end) = 0;
    (q->processes_executed) = 0;
    q->max_elements = max_elements;
    q->elements = malloc(sizeof(Node)*q->max_elements);
    if (q->elements == NULL){
        printf("newSchedulingQueue : Failed to allot heap memory when initialising elements array");
        // return NULL;
        exit(-1);
    }
    return q;
}

static void growSchedulingQueue(SchedulingQueue *h){
    h->max_elements = h->max_elements * 2;
    h->elements = realloc(h->elements, (sizeof(Node)*h->max_elements));
    if (h->elements == NULL){
        printf("growSchedulingQueue : Failed memory allocation with SchedulingQueue resizing.\n");
        exit(0);
    }
}

void push_back(SchedulingQueue *q, Node *input_pointer){
    // always pushes the element in the end of the queue
    if (q->end == q->max_elements){
        growSchedulingQueue(q);
    }
    memcpy((void *)(&(q->elements[q->end])), (void *)input_pointer, sizeof(Node));
    q->end += 1;
    q->num_elements += 1;
}

void push_front(SchedulingQueue *q, Node *input_pointer){
    // pushes the element in the front of the queue
    if (q->start == 0){
        printf("Can't push in front of 0th position!!\nPush front failed!!\n");
        return;
    }
    q->start -= 1;
    memcpy((void *)(&(q->elements[q->start])), (void *)input_pointer, sizeof(Node));
    q->num_elements += 1;
}

void extract(SchedulingQueue *q, Node *output_pointer){
    // always extract the element from the front of the queue
    // output_pointer should always be malloced before this function call

    if (q->num_elements == 0){
        printf("No elements left in the queue to extarct!!\n");
        return;
    }
    memcpy((void *)output_pointer, (void *)(&(q->elements[q->start])), sizeof(Node));
    q->start += 1;
    q->num_elements -= 1;
}

SchedulingQueue *create_scheduling_queue_copy(SchedulingQueue *orignal){
    SchedulingQueue *copy = MALLOC(SchedulingQueue, 1);
    if (copy == NULL){
        printf("newSchedulingQueue : Failed to allot heap memory when initialising the queue");
        // return NULL;
        exit(-1);
    }
    copy->num_elements = orignal->num_elements;
    (copy->start) = orignal->start;
    (copy->end) = orignal->end;
    (copy->processes_executed) = orignal->processes_executed;
    copy->max_elements = orignal->max_elements;
    copy->elements = malloc(sizeof(Node)*copy->max_elements);
    if (copy->elements == NULL){
        printf("newSchedulingQueue : Failed to allot heap memory when initialising elements array");
        // return NULL;
        exit(-1);
    }
    copy->elements = memcpy(copy->elements, orignal->elements, sizeof(Node)*copy->max_elements);
    return copy;

}

void print_scheduling_queue_node(SchedulingQueue *q){
    int i;
    for(i=q->start; i<q->end; i++){
        printf("Queue[%d] : %d\n", (q->elements[i]).process_id, (q->elements[i]).time_required);
    }
}

void free_scheduling_queue(SchedulingQueue *q){
    free(q->elements);
    free(q);
}