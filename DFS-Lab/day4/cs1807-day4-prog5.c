/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 31 July, 2018
Program description: Count of HTML TAGS in DFSLAB Page
Acknowledgements:
------------------------------------*/


#include <stdio.h>
#include <stdlib.h>

#define MALLOC(type, size) (type *)malloc(size*sizeof(type))

int main()
{
    FILE *fp;
    fp = fopen("dfslab.html", "r");
    char c,p;
    int count=0;
    while(1){
        c = fgetc(fp);
        if (c == EOF){
            fclose(fp);
            break;
        }
        if (c == '<')
            count++;
        if ((c == '/') && (p == '<')){
            count--;
        }
        p = c;
    }
    printf("Total HTML Tags in dfslab.html is : %d\n", count);
    return 0;
}
