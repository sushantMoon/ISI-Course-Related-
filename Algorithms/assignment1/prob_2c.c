#include "common.h"
#include "quick.h"


int main(){

    struct rusage usageInfo;
    struct timeval startUser, startSys, endUser, endSys;
    long long int time_taken_q_r = 0, time_taken_q_i = 0;
    llu swap_comparision_r=0, swap_comparision_i=0;

    int n;

    printf("Quick Sort\n");
    printf("N\t, \tRecursive, \tIterative\n");
    printf("N\t, \tTime : \tSwap_Comparsion, \tTime : \tSwap_Comparsion\n");

    FILE *fp = fopen("prob_2c.dat", "wb");
    fprintf(fp, "#Quick Sort\n");
    fprintf(fp, "#N, Recursive, Iterative\n");
    fprintf(fp, "#N, R. Time, R. Swap_Comparsion, I. Time, I. Swap_Comparsion\n");


    for(n = 10; n < MaxNumElements; n += n/2){
        // iterations for different N 
        lli *ary, *ary_copy;
        int ite_i;
        
        // seeding random 
        srand(time(0));
        
        ary = MALLOC(lli, n);
        for(ite_i=0; ite_i<n; ite_i++){
            ary[ite_i] = rand()%MODULO;
        }

        ite_i = repetition;
        while(ite_i > 0){
            ary_copy = copy_ary(ary, n);
            llu swap_comparision_temp = 0;	
            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            startUser = usageInfo.ru_utime;
            startSys = usageInfo.ru_stime;

            quick_sort_recursive(ary_copy, 0, n-1, &swap_comparision_temp);
            
            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            endUser = usageInfo.ru_utime;
            endSys = usageInfo.ru_stime;

            time_taken_q_r += (DURATION(startUser, endUser) + DURATION(startSys, endSys));
            ite_i -= 1;
            free(ary_copy);
            swap_comparision_r += (swap_comparision_temp/repetition);
        }

        ite_i = repetition;
        while(ite_i > 0){
            ary_copy = copy_ary(ary, n);
            llu swap_comparision_temp = 0;	
            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            startUser = usageInfo.ru_utime;
            startSys = usageInfo.ru_stime;

            quick_sort_iterative(ary_copy, 0, n-1, &swap_comparision_temp);

            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            endUser = usageInfo.ru_utime;
            endSys = usageInfo.ru_stime;

            time_taken_q_i += (DURATION(startUser, endUser) + DURATION(startSys, endSys));
            ite_i -= 1;
            free(ary_copy);
            swap_comparision_i += (swap_comparision_temp/repetition);
        }
        
        free(ary);

        /////////////////////////
        printf(
            "%d, \t%LF, \t%llu, \t%LF, \t%llu\n", 
            n, 
            (long double)((long double)time_taken_q_r/(long double)(LOOPCOUNT*repetition)),
            swap_comparision_r,
            (long double)((long double)time_taken_q_i/(long double)(LOOPCOUNT*repetition)),
            swap_comparision_i
        );
        fprintf(
            fp,
            "%d, %LF, %llu, %LF, %llu\n", 
            n, 
            (long double)((long double)time_taken_q_r/(long double)(LOOPCOUNT*repetition)),
            swap_comparision_r,
            (long double)((long double)time_taken_q_i/(long double)(LOOPCOUNT*repetition)),
            swap_comparision_i
        );
    }
    fclose(fp);
	return 0;
}