/*-----------------------------------
Name: Sushant Sharad Moon
Roll number: MTC1807
Date: 20 July, 2018
Program description: Counts the number of vowels and the words in the text entered in the terminal
Acknowledgements:
------------------------------------*/

#include <stdio.h>

int main()
{
    printf("Please Enter the Text :\n");
    char c;
    char prev;
    int whitespace = 0;
    int vowel = 0;
    while(1){
        c = getchar();
        if (c == '\n'){
            if (prev != ' '){
                whitespace += 1;
            }
            break;
        }
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
            vowel += 1;
        }
        if (c == ' '){
            if (prev != ' '){
                whitespace += 1;
            }
        }
        prev = c;
    }
    printf("Number of Vowels : %d\n", vowel);
    printf("Number of Words : %d\n", whitespace);
    return 0;
}
