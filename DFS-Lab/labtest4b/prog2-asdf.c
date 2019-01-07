#include<stdio.h>
#include<stdlib.h>

int main() {

	int num, ind = 0, count = 0, flag = 0, countr = 0, countb = 0, county = 0, i, min, max;
	char ch;
	int *array = (int *)malloc(100 * sizeof(int));
	
	for(;;) {
		scanf("%d%c", &num, &ch);
		if((ind == 0) && (num != -1)) {
			flag = 1;
		}
		if((ind > 0) && (num == -1)) {
                        flag = 1;       
                }
		array[ind] = num;
		if(ind > 0) {
			if(array[ind] == array[ind-1]) {
				count++;
				if(count > 1) {
                                        printf("-1\n");
                                        return 0;
                                }
			}
			else if(array[ind] != array[ind-1]) {				
				count = 0;
			}
		}
		ind++;
		if(ch == '\n')
			break;
        }

	if(flag == 1) {
		printf("-1\n");
		return 0;
	}

	int *colors = (int *)malloc(ind * sizeof(int));

	for(i = 0; (i < 3) && (i < ind); i++) {
		colors[i] = i;
	}
	for(i = 3; i < ind; i++) {
		if(((i-1) >= 0) && (array[i] >= 0)) {
			if(colors[i-1] == colors[array[i]])
				colors[i] = colors[i-2];
			else
				colors[i] = 3 - (colors[i-1] + colors[array[i]]);
		}
	}
	
	for(i = 0; i < ind; i++) {
		if(colors[i] == 0)
			countr++;
		else if(colors[i] == 1)
                        countb++;
		else if(colors[i] == 2)
                        county++;
	}

	if(countr > countb) {
		max = countr;
		min = countb;
	} 
	else {
		max = countb;
                min = countr;
	}

	if(max < county)
		max = county;
	if(min > county)
		min = county;

	printf("%d %d\n", min, max);

	free(array);	
	free(colors);

        return 0;

}
