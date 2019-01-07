/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 7 December, 2018
Program description: 

Compile Using : ```gcc -g -Wall -o prog1 cs1807-project1-prog1-zx.c eertree.c -lm```
Run : ``` ./prog1  ```
Acknowledgements:

------------------------------------*/


// #include <stdio.h>
// #include <string.h>
// #include <stdbool.h>
#include "eertree.h"
#include "common.h"

// int n, suffix, key;
// char str[5000005], out[5000005];
// struct data {
//     int len, with[2], suffixLink;
// } tree[5000005];

// void init() {
//     suffix = key = 2;
//     tree[1].len = -1, tree[1].suffixLink = 1;
//     tree[2].len =  0, tree[2].suffixLink = 1;
// }

// int getLink(int idx, int cur) {
//     while(true) {
//         if(idx-tree[cur].len-1>=0 && str[ idx-tree[cur].len-1 ] == str[idx]) break;
//         cur = tree[cur].suffixLink;
//     }
//     return cur;
// }

// bool update(int idx) {
//     int cur = getLink(idx, suffix), letter = str[idx]-'a';
//     if(tree[cur].with[letter]) {
//         suffix = tree[cur].with[letter];
//         return false;
//     }
//     suffix = ++key;
//     tree[suffix].len = tree[cur].len+2;
//     tree[cur].with[letter] = suffix;
//     if(tree[suffix].len == 1) tree[suffix].suffixLink = 2;
//     else tree[suffix].suffixLink = tree[ getLink(idx, tree[cur].suffixLink) ].with[letter];
//     return true;
// }

int main() {
    scanf("%s", str);
    int i, len=strlen(str);
    // init();
    // for(i=0; i<len; i++) {
    //     if(update(i)) out[i] = '1';
    //     else out[i] = '0';
    // }
    // puts(out);

    // printf("\n\n");

    eertree *tree = initialize_eertree();
    for(i=0;i<len;i++){
        printf("%d", add_letter_eertree(i, str, tree));
    }
    printf("\n");
    return 0;
}