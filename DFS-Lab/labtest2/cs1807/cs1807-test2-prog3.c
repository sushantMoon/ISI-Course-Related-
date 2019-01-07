/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 20 September, 2018
Program description:

Duration when max number of cabs are available in kolkata

Acknowledgements:
------------------------------------*/

#include "common.h"

void updateTimeInString(char *s, int i , int j){
    // hour part
    s[0] = '0';
    s[1] = '0';
    s[2] = '0';
    s[3] = '0';
    // hour part
    if (i>0){
        s[1] = '0' + (int)(i%10);
        s[0] = '0' + (int)(i/10);
    }
    //minute part
    if (j>0){
        s[3] = '0' + (int)(j%10);
        s[2] = '0' + (int)(j/10);
    }
}

int main(){
    int n, clock24[24][60];
    int i, j, k, maxi;
    int time1, time2;
    
    for(i = 0; i < 24; i++){
        for(j = 0; j < 60; j++){
            clock24[i][j] = 0;
        }   
    }
    
    scanf("%d", &n);
    for(i = 0; i < n; i++){
        scanf("%d %d", &time1, &time2);
        if (time1 > time2){
            printf("Enter the timings correctly!! exiting the code !!");
            return 1;
        }
        int h1,m1,h2,m2;
        h1 = (int)(time1/100);
        h2 = (int)(time2/100);
        m1 = (int)(time1%100);
        m2 = (int)(time2%100);
        for( j=h1 ; j<= h2; j++){
            // for loop for hour array
            if (j == h1){
                k = m1;
            }
            else{
                k = 0;
            }
            while( ( (j < h2) && (k < 60) ) || ( (j == h2) && (k <= m2) ) ){
                //for loop for minute array
                clock24[j][k] += 1;
                k++;
            }
        }
    }

    maxi = 0;
    time1 = 0;
    time2 = 0;
    int flagh = 0;
    int flagm = 0;
    i = 0, j = 0;

    char *ot1 = MALLOC(char, 4);
    char *ot2 = MALLOC(char, 4);

    while(i < 24){
        while(j < 60){
            if (clock24[i][j] > maxi){
                maxi = clock24[i][j];
                time1 = i*100 + j;
                updateTimeInString(ot1, i , j);
                while(clock24[i][j] == maxi){
                    time2 = i*100 + j;
                    updateTimeInString(ot2, i , j);
                    j++;
                    if (j == 60){
                        j = 0;
                        i++;
                    }
                    flagm = 1;
                    flagh = 1;
                }
            }
            if (flagm == 0){
                j++;
            }
            flagm = 0;
        }
        if (flagh == 0){
            i++;
            j = 0;
        }
        flagh = 0;
    }
    // printf("%d %d %d\n", time1, time2, maxi);
    printf("%s %s %d\n", ot1, ot2, maxi);
    return 0;
}