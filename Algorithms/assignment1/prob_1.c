#include "common.h"
#include "merge.h"
#include "quick.h"
#include "heap.h"

#define repetition 2
#define LOOPCOUNT 1

int *copy_ary(int *ary, int size){
    int *copy = MALLOC(int, size);
    memcpy(copy, ary, sizeof(int)*size);
    return copy;
}

int main(){

    struct rusage usageInfo;
    struct timeval startUser, startSys, endUser, endSys;
    long long int time_taken_q_r = 0, time_taken_q_i = 0;
    long long int time_taken_m_r = 0, time_taken_m_i = 0;
    long long int time_taken_h_r = 0, time_taken_h_i = 0;

    int n;
    for(n = 100; n < 1000000; n *= 10){
        /////////////////////////
        int *ary, *ary_copy;
        int ite_i;
        
        // seeding random 
        srand(time(0));
        
        ary = MALLOC(int, n);
        for(ite_i=0; ite_i<n; ite_i++){
            // ary[ite_i] = rand()%10;
            ary[ite_i] = rand();
        }


        ite_i = repetition;
        while(ite_i > 0){
            ary_copy = copy_ary(ary, n);	
            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            startUser = usageInfo.ru_utime;
            startSys = usageInfo.ru_stime;

            quick_sort_recursive(ary_copy, 0, n-1);

            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            endUser = usageInfo.ru_utime;
            endSys = usageInfo.ru_stime;

            time_taken_q_r += (DURATION(startUser, endUser) + DURATION(startSys, endSys));
            ite_i -= 1;
            free(ary_copy);
        }
        printf("Quick Sort Recursion : N = %d : Time = %LF (microsec)\n", n, (long double)((long double)time_taken_q_r/(long double)(LOOPCOUNT*repetition)));

        ite_i = repetition;
        while(ite_i > 0){
            ary_copy = copy_ary(ary, n);	
            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            startUser = usageInfo.ru_utime;
            startSys = usageInfo.ru_stime;

            quick_sort_iterative(ary_copy, 0, n-1);

            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            endUser = usageInfo.ru_utime;
            endSys = usageInfo.ru_stime;

            time_taken_q_i += (DURATION(startUser, endUser) + DURATION(startSys, endSys));
            ite_i -= 1;
            free(ary_copy);
        }
        printf("Quick Sort Iteration : N = %d : Time = %LF (microsec)\n", n, (long double)((long double)time_taken_q_i/(long double)(LOOPCOUNT*repetition)));

        ite_i = repetition;
        while(ite_i > 0){
            ary_copy = copy_ary(ary, n);	
            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            startUser = usageInfo.ru_utime;
            startSys = usageInfo.ru_stime;

            merge_sort_recursive(ary_copy, 0, n-1);

            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            endUser = usageInfo.ru_utime;
            endSys = usageInfo.ru_stime;

            time_taken_m_r += (DURATION(startUser, endUser) + DURATION(startSys, endSys));
            ite_i -= 1;
            free(ary_copy);
        }
        printf("Merge Sort Recursion : N = %d : Time = %LF (microsec)\n", n, (long double)((long double)time_taken_m_r/(long double)(LOOPCOUNT*repetition)));

        ite_i = repetition;
        while(ite_i > 0){
            ary_copy = copy_ary(ary, n);	
            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            startUser = usageInfo.ru_utime;
            startSys = usageInfo.ru_stime;

            merge_sort_iterative(ary_copy, n);

            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            endUser = usageInfo.ru_utime;
            endSys = usageInfo.ru_stime;

            time_taken_m_i += (DURATION(startUser, endUser) + DURATION(startSys, endSys));
            ite_i -= 1;
            free(ary_copy);
        }
        printf("Merge Sort Iteration : N = %d : Time = %LF (microsec)\n", n, (long double)((long double)time_taken_m_i/(long double)(LOOPCOUNT*repetition)));

        ite_i = repetition;
        while(ite_i > 0){
            ary_copy = copy_ary(ary, n);	
            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            startUser = usageInfo.ru_utime;
            startSys = usageInfo.ru_stime;

            heap_sort_recursive(ary, n);

            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            endUser = usageInfo.ru_utime;
            endSys = usageInfo.ru_stime;

            time_taken_h_r += (DURATION(startUser, endUser) + DURATION(startSys, endSys));
            ite_i -= 1;
            free(ary_copy);
        }
        printf("Heap Sort Recursion : N = %d : Time = %LF (microsec)\n", n, (long double)((long double)time_taken_h_r/(long double)(LOOPCOUNT*repetition)));

        ite_i = repetition;
        while(ite_i > 0){
            ary_copy = copy_ary(ary, n);	
            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            startUser = usageInfo.ru_utime;
            startSys = usageInfo.ru_stime;

            heap_sort_iterative(ary, n);    

            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            endUser = usageInfo.ru_utime;
            endSys = usageInfo.ru_stime;

            time_taken_h_i += (DURATION(startUser, endUser) + DURATION(startSys, endSys));
            ite_i -= 1;
            free(ary_copy);
        }
        printf("Heap Sort Iteration : N = %d : Time = %LF (microsec)\n", n, (long double)((long double)time_taken_h_i/(long double)(LOOPCOUNT*repetition)));
        
        free(ary);






        /////////////////////////
    }
	return 0;
}