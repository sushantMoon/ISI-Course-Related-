#include "common.h"
#include "merge.h"
#include "quick.h"
#include "heap.h"

int main(){

    struct rusage usageInfo;
    struct timeval startUser, startSys, endUser, endSys;
    lli time_taken_q_r = 0;
    lli time_taken_m_r = 0;
    lli time_taken_h_r = 0;
    llu swap_comparision_h=0, swap_comparision_q=0, swap_comparision_m=0;

    int n;
    printf("Recursive Routines\n");
    printf("N\t, \tQuick Sort, \tMerge Sort, \tHeap Sort\n");
    printf("#N,\t Q. Time,\t Q. Swap_Comparsion,\t M. Time,\t M. Swap_Comparsion,\t H. Time,\t H. Swap_Comparsion\n");

    FILE *fp = fopen("prob_3a.dat", "wb");
    fprintf(fp, "#Recursive Routines\n");
    fprintf(fp, "#N, Quick Sort, Merge Sort, Heap Sort\n");
    fprintf(fp, "#N, Q. Time, Q. Swap_Comparsion, M. Time, M. Swap_Comparsion, H. Time, H. Swap_Comparsion\n");

    for(n = 10; n < MaxNumElements; n += n/2){

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
            swap_comparision_q += (swap_comparision_temp/repetition);
        }
        
        ite_i = repetition;
        while(ite_i > 0){
            ary_copy = copy_ary(ary, n);	
            llu swap_comparision_temp = 0;

            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            startUser = usageInfo.ru_utime;
            startSys = usageInfo.ru_stime;

            merge_sort_recursive(ary_copy, 0, n-1, &swap_comparision_temp);

            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            endUser = usageInfo.ru_utime;
            endSys = usageInfo.ru_stime;

            time_taken_m_r += (DURATION(startUser, endUser) + DURATION(startSys, endSys));
            ite_i -= 1;
            free(ary_copy);

            swap_comparision_m += (swap_comparision_temp/repetition);

        }
        
        ite_i = repetition;
        while(ite_i > 0){
            ary_copy = copy_ary(ary, n);	
            llu swap_comparision_temp = 0;

            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            startUser = usageInfo.ru_utime;
            startSys = usageInfo.ru_stime;

            heap_sort_recursive(ary_copy, n, &swap_comparision_temp);

            if (0 != getrusage(RUSAGE_SELF, &usageInfo))
                perror("getrusage: ");
            endUser = usageInfo.ru_utime;
            endSys = usageInfo.ru_stime;

            time_taken_h_r += (DURATION(startUser, endUser) + DURATION(startSys, endSys));
            ite_i -= 1;
            free(ary_copy);
            swap_comparision_h += (swap_comparision_temp/repetition);
        }
        
        free(ary);

        printf(
            "%d\t, \t%LF, \t%llu, \t%LF, \t%llu, \t%LF, \t%llu\n", 
            n,
            (long double)((long double)time_taken_q_r/(long double)(LOOPCOUNT*repetition)),
            swap_comparision_q,
            (long double)((long double)time_taken_m_r/(long double)(LOOPCOUNT*repetition)),
            swap_comparision_m,
            (long double)((long double)time_taken_h_r/(long double)(LOOPCOUNT*repetition)), 
            swap_comparision_h
        );
        fprintf(
            fp,
            "%d, %LF, %llu, %LF, %llu, %LF, %llu\n", 
            n,
            (long double)((long double)time_taken_q_r/(long double)(LOOPCOUNT*repetition)), 
            swap_comparision_q,
            (long double)((long double)time_taken_m_r/(long double)(LOOPCOUNT*repetition)), 
            swap_comparision_m,
            (long double)((long double)time_taken_h_r/(long double)(LOOPCOUNT*repetition)),
            swap_comparision_h
        );
    }
    fclose(fp);
	return 0;
}