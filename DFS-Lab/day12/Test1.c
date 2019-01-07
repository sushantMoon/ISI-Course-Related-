/* C program for finding out the multiplication of the integers from 1 to n.
   Here n is the user input. */

#include<stdio.h>

int main(){

	int i, n;
	int mult;
	
	scanf("%i", &n);
	mult = 0;
	// mult = 1;    //corrections
	for(i = 1; i -= n; i++)
	// for(i = 1; i <= n; i++)			//corrections
		mult *= i;
	printf("%d", mult);
	return 0;
}
