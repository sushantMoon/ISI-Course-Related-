/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 21 August, 2018
Program description: Stable Matching Problem 
Acknowledgements:
------------------------------------*/ 


#include <stdio.h>
#include <stdlib.h>
#define MALLOC(type, n) (type *)malloc(sizeof(type)*n)

int main()
{
    int n;
    // printf("Enter the n : ");
    scanf("%d", &n);
    int **women_preferences, **men_preferences, **women_proposed, **men_proposed, i, j, k;

    women_preferences = MALLOC(int *, n);
    for(i=0;i<n;i++)
        women_preferences[i] = MALLOC(int, n);

    men_preferences = MALLOC(int *, n);
    for(i=0;i<n;i++)
        men_preferences[i] = MALLOC(int, n);

    women_proposed = MALLOC(int *, n);
    for(i=0;i<n;i++)
        women_proposed[i] = MALLOC(int, n);

    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            women_proposed[i][j] = 0;       // 0 means ith women has not been proposed the jth men

    men_proposed = MALLOC(int *, n);
    for(i=0;i<n;i++)
        men_proposed[i] = MALLOC(int, n);

    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            men_proposed[i][j] = 0;     // 0 means ith men has not proposed jth women
    
    int *men_status = MALLOC(int, n);
    for(i=0;i<n;i++)
        men_status[i] = -1;    // -1 means no engagement, and any other number means the engagement to other person 

    int *women_status = MALLOC(int, n);
    for(i=0;i<n;i++)
        women_status[i] = -1;   // -1 means no engagement, and any other number means the engagement to other person
    
    int *women_suitor_rank = MALLOC(int, n);
    for(i=0;i<n;i++)
        women_suitor_rank[i] = __INT_MAX__;             // lower the rank better

    // input for men pref
    for(i = 0; i < n; i++){
        for(j=0;j<n;j++){
            scanf("%d",&men_preferences[i][j]);
            men_preferences[i][j] = men_preferences[i][j]%n;
        }
    }

    // input for women pref
    for(i = 0; i < n; i++){
        for(j=0;j<n;j++){
            scanf("%d",&women_preferences[i][j]);
            women_preferences[i][j] = women_preferences[i][j]%n;
        }
    }

    int total_number_unengaged = n;

    while(total_number_unengaged > 0){
        // Step 1
        // 1.a
        for(i = 0; i < n; i++)
        {
            k=0;
            // Step 1.a's routine
            // men_proposed[i][men_preferences[i][k]] = 1;
            // women_proposed[men_preferences[i][k]][i] = 1;
            
            // Modified Step 1.a and 2 routine
            if (men_status[i] < 0){             // for all the men who are not engaged and have status -1
                while(k<n){
                    if (men_proposed[i][men_preferences[i][k]] == 0){
                        men_proposed[i][men_preferences[i][k]] = 1;
                        women_proposed[men_preferences[i][k]][i] = 1;
                        break;
                    }
                    else{
                        k++;
                    }
                }
                if (k >= n){
                    printf("This should never happen, please check the code.!!\nTerminating\n");
                    return 1;
                }
            }
        }
        // 1.b
        for(i = 0; i < n; i++){   
            int man_who_proposed=-1, priority_of_man_who_proposed=__INT_MAX__;
            for(j = 0; j < n; j++){
                if (women_proposed[i][j] == 1){
                    if (man_who_proposed == -1){
                        man_who_proposed = j;
                        for(k = 0; k < n; k++){
                            if (women_preferences[i][k] == j){
                                priority_of_man_who_proposed = k;
                            }
                        }
                    }
                    else{
                        int new_proposals_priority=__INT_MAX__;
                        for(k = 0; k < n; k++){
                            if (women_preferences[i][k] == j){
                                new_proposals_priority = k;
                            }
                        }
                        if (new_proposals_priority < priority_of_man_who_proposed){
                            priority_of_man_who_proposed = new_proposals_priority;
                            man_who_proposed = j;
                        }
                    }
                }
            }
            if (man_who_proposed != -1){
                if (women_status[i] > -1){
                    men_status[women_status[i]] = -1;
                }
                women_status[i] = man_who_proposed;                         // man_who_proposed is the jth man value varies from [0 - n-1] 
                women_suitor_rank[i] = priority_of_man_who_proposed;        // lower the value the better
                men_status[man_who_proposed] = i;
            }
        }
        // check for Step 3's Termination
        total_number_unengaged = n;
        for(i = 0; i < n; i++)
        {
            if (men_status[i] > -1) {
                total_number_unengaged -= 1;
            }
        }
        // printf("total unengaged %d\n", total_number_unengaged);
    }


    for( i=0; i<n; i++ ){
        printf("%d %d\n", n+i, women_status[i]);
    }

    // printf("Men Status : Reverse View\n");
    // for( i=0; i<n; i++ ){
    //     printf("%d %d\n", i, men_status[i]+n);
    // }


    return 0;
}
