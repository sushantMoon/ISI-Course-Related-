/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 2 November, 2018
Program description:

Scheduling Problem

Compile Using : ```gcc -g -Wall -o prog2 cs1807-assign3-prog2-shaui.c scheduling-queue.c -lm```

Acknowledgements:

------------------------------------*/

#include "common.h"
#include "scheduling-queue.h"

// #define DEBUG
#define SCHEDULE_LIMIT 40
#define SLOT_DEFAULT 6
#define SLOT_INCREASED 8

void schedule_processes(SchedulingQueue *q, int quantum, int *idle_time, int *process_completed, int *time_passed){
    Node *process1 = MALLOC(Node, 1);
    Node *process2 = MALLOC(Node, 1);
    extract(q, process1);
    quantum -= process1->time_required;
    (*time_passed) += process1->time_required;
    #if defined(DEBUG)
        ps("Process ID : %d (%d)", process1->process_id, process1->time_required);
    #endif // DEBUG
    if (*time_passed <= SCHEDULE_LIMIT){
        (*process_completed) += 1;
        (q->processes_executed) += 1;
        #if defined(DEBUG)
            ps("\t... completed\n");
        #endif // DEBUG
    }
    else{
        #if defined(DEBUG)
            ps("\n");
        #endif // DEBUG
    }
    if ((*time_passed >= SCHEDULE_LIMIT) || (quantum == 0)){
        // free(process1);
        // free(process2);
        // return;
        quantum = 0;
    }

    while(quantum > 0){
        extract(q, process1);
        if (quantum >= process1->time_required) {
            quantum -= process1->time_required;
            (*time_passed) += process1->time_required;
            #if defined(DEBUG)
                ps("Process ID : %d (%d)", process1->process_id, process1->time_required);
            #endif // DEBUG
            if (*time_passed <= SCHEDULE_LIMIT){
                (*process_completed) += 1;
                (q->processes_executed) += 1;
                #if defined(DEBUG)
                    ps("\t... completed\n");
                #endif // DEBUG
            }
            else{
                #if defined(DEBUG)
                    ps("\n");
                #endif // DEBUG
            }
            if ((*time_passed >= SCHEDULE_LIMIT) || (quantum == 0)){
                break;
            }
        }
        else{
            extract(q, process2);
            if ((process1->time_required + process2->time_required) > SLOT_INCREASED) {
                if(process1->time_required > process2->time_required){
                    push_back(q, process1);
                    push_front(q, process2);
                }
                else if(process1->time_required < process2->time_required){
                    push_back(q, process2);
                    push_front(q, process1);
                }
                else if(process1->time_required == process2->time_required){
                    if(process1->process_id > process2->process_id){
                        push_back(q, process2);
                        push_front(q, process1);
                    }
                    else{
                        push_back(q, process1);
                        push_front(q, process2);
                    }
                }
            }
            else {
                push_front(q, process2);
                push_front(q, process1);
            }
            #if defined(DEBUG)
                ps("Idle Time: (%d)\n", quantum);
            #endif // DEBUG
            *idle_time += quantum;
            *time_passed += quantum;
            quantum = 0;
        }
    }
    free(process1);
    free(process2);
} 

int main(int argc, char const *argv[])
{
    int size_q0, size_q1;
    SchedulingQueue *Q0;
    SchedulingQueue *Q1;
    Node *n1, *n2;
    int i;
    char value_str_parsed[5], value_str[5];
    int idle_time_option1 = 0, idle_time_option2 = 0, process_completed_option1 = 0, process_completed_option2 = 0;
    int time_passed = 0;
    int option_counter;

    #if defined(DEBUG)
        ps("Enter the size of the 2 queues\n");
    #endif // DEBUG
    
    scanf("%d %d", &size_q0, &size_q1);

    Q0 = newSchedulingQueue(size_q0*2);
    Q1 = newSchedulingQueue(size_q1*2);

    #if defined(DEBUG)
        ps("Enter the elements of the process P with Process Id:\nP{processId} {executionTimeRequired}\n");
    #endif // DEBUG

    for(i = 0; i < size_q0; i++){
        #if defined(DEBUG)
        printf("Enter P[%d]\n", i+1);
        #endif // DEBUG

        n1 = MALLOC(Node, 1);
        scanf("%s %d", value_str, &(n1->time_required));
        memcpy(value_str_parsed, value_str + sizeof(char), sizeof(char)*(strlen(value_str)-1));
        n1->process_id = atoi(value_str_parsed);
        #if defined(DEBUG)
        printf("Entered Process => P[%d]: %d\n", n1->process_id, n1->time_required);
        #endif
        push_back(Q0, n1);
        free(n1);
        n1 = NULL;
    }
    
    #if defined(DEBUG)
        ps("The Processes Entered are\n");
        // for(i = 0; i < size_q0; i++){
        //     n1 = MALLOC(Node, 1);
        //     extract(Q0, n1);
        //     printf("P%d %d\n", n1->process_id, n1->time_required);   
        // }
        print_scheduling_queue_node(Q0);
    #endif // DEBUG

    for(i = 0; i < size_q1; i++){
        #if defined(DEBUG)
        printf("Enter W[%d]\n", i+1);
        #endif // DEBUG

        n2 = MALLOC(Node, 1);
        scanf("%s %d", value_str, &(n2->time_required));
        memcpy(value_str_parsed, value_str + sizeof(char), sizeof(char)*(strlen(value_str)-1));
        n2->process_id = atoi(value_str_parsed);
        #if defined(DEBUG)
        printf("Entered Process => W[%d]: %d\n", n2->process_id, n2->time_required);
        #endif
        push_back(Q1, n2);
        free(n2);
        n2 = NULL;
    }
    
    #if defined(DEBUG)
        ps("The Processes Entered are\n");
        // for(i = 0; i < size_q1; i++){
        //     n2 = MALLOC(Node, 1);
        //     extract(Q1, n2);
        //     printf("W%d %d\n", n2->process_id, n2->time_required);     
        // }
        print_scheduling_queue_node(Q1);
    #endif // DEBUG

    #if defined(DEBUG)
        ps("Copying the Queues for the two Options\n");    
    #endif // DEBUG
    SchedulingQueue *q0_option1 = create_scheduling_queue_copy(Q0);
    SchedulingQueue *q1_option1 = create_scheduling_queue_copy(Q1);
    SchedulingQueue *q0_option2 = create_scheduling_queue_copy(Q0);
    SchedulingQueue *q1_option2 = create_scheduling_queue_copy(Q1);
    
    #if defined(DEBUG)
        ps("Testing the  create_scheduling_queue_copy function\n");
        ps("Queue 1\n");
        print_scheduling_queue_node(q0_option1);
        ps("Queue 2\n");
        print_scheduling_queue_node(q1_option1);
        ps("Queue 1\n");
        print_scheduling_queue_node(q0_option2);
        ps("Queue 2\n");
        print_scheduling_queue_node(q1_option2);
    #endif // DEBUG
    
    #if defined(DEBUG)
        ps("Option 1:\n");
    #endif // DEBUG
    option_counter = 0;
    while(time_passed < SCHEDULE_LIMIT){
        if (option_counter%2 == 0){
            #if defined(DEBUG)
                ps("Scheduling Queue 0:\n");
            #endif // DEBUG
            // schedule queue 0
            if ((process_completed_option1 == 0) || (q0_option1->processes_executed >= q1_option1->processes_executed)) {
                // executing the schedule for first time;
                schedule_processes(q0_option1, SLOT_DEFAULT, &idle_time_option1, &process_completed_option1, &time_passed);
            }
            else if(q0_option1->processes_executed < q1_option1->processes_executed){
                schedule_processes(q0_option1, SLOT_INCREASED, &idle_time_option1, &process_completed_option1, &time_passed);
            }
        }
        else if (option_counter%2 == 1){
            #if defined(DEBUG)
                ps("Scheduling Queue 1:\n");
            #endif // DEBUG
            // schedule queue 1
            if(q0_option1->processes_executed > q1_option1->processes_executed){
                schedule_processes(q1_option1, SLOT_INCREASED, &idle_time_option1, &process_completed_option1, &time_passed);
            }
            else{
                schedule_processes(q1_option1, SLOT_DEFAULT, &idle_time_option1, &process_completed_option1, &time_passed);
            }
        }
        option_counter += 1;
    }
    #if defined(DEBUG)
        ps("Option1 :\nProcesses Completed : %d\nTotal Idle Time : %d\n", process_completed_option1, idle_time_option1);
    #endif // DEBUG

    #if defined(DEBUG)
        ps("Option 2:\n");
    #endif // DEBUG
    option_counter = 1;
    time_passed = 0;
    while(time_passed < SCHEDULE_LIMIT){
        if (option_counter%2 == 1){
            #if defined(DEBUG)
                ps("Scheduling Queue 1:\n");
            #endif // DEBUG
            // schedule queue 0
            if ((process_completed_option2 == 0) || (q1_option2->processes_executed >= q0_option2->processes_executed)) {
                // executing the schedule for first time;
                schedule_processes(q1_option2, SLOT_DEFAULT, &idle_time_option2, &process_completed_option2, &time_passed);
            }
            else if(q1_option2->processes_executed < q0_option2->processes_executed){
                schedule_processes(q1_option2, SLOT_INCREASED, &idle_time_option2, &process_completed_option2, &time_passed);
            }
        }
        else if (option_counter%2 == 0){
            #if defined(DEBUG)
                ps("Scheduling Queue 0:\n");
            #endif // DEBUG
            // schedule queue 1
            if(q1_option2->processes_executed > q0_option2->processes_executed){
                schedule_processes(q0_option2, SLOT_INCREASED, &idle_time_option2, &process_completed_option2, &time_passed);
            }
            else{
                schedule_processes(q0_option2, SLOT_DEFAULT, &idle_time_option2, &process_completed_option2, &time_passed);
            }
        }
        option_counter += 1;
    }
    
    #if defined(DEBUG)
        ps("Option2 :\nProcesses Completed : %d\nTotal Idle Time : %d\n", process_completed_option2, idle_time_option2);
    #endif // DEBUG
    
    ps("%d %d\n", process_completed_option1, idle_time_option1);
    ps("%d %d\n", process_completed_option2, idle_time_option2);
    
    if (process_completed_option1 > process_completed_option2) {
        ps("Option 1 is better than Option 2\n");
    }
    else if(process_completed_option1 < process_completed_option2) {
        ps("Option 2 is better than Option 1\n");
    }
    else {
        if (idle_time_option1 < idle_time_option2) {
            ps("Option 1 is better than Option 2\n");
        }
        else if(idle_time_option1 > idle_time_option2) {
            ps("Option 2 is better than Option 1\n");
        }
        else {
            ps("Both Option 1 and 2 are equally good\n");
        }
    }
    free_scheduling_queue(q0_option1);
    free_scheduling_queue(q1_option1);
    free_scheduling_queue(q0_option2);
    free_scheduling_queue(q1_option2);
    free_scheduling_queue(Q0);
    free_scheduling_queue(Q1);
    return 0;
}
