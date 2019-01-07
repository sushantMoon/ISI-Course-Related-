#include "common.h"
#include "eertree.h"

eertree *initialize_eertree(){
    eertree *tree = CALLOC(eertree, 1);
    tree->index = 2;
    tree->suffix = 2;
    tree->node[1].length = -1;
    tree->node[1].suffix_link = 1;
    tree->node[2].length = 0;
    tree->node[2].suffix_link = 1;
    return tree;
}

int get_suffix_link(int position, char* input, int index, eertree* tree){
    int current = index;
    while(1){
        if ( ( (position - tree->node[current].length - 1) >= 0 ) && ( input[position - tree->node[current].length - 1] == input[position] ) ){
            break;
        }
        current = tree->node[current].suffix_link;
    }
    return current;
}

int add_letter_eertree(int position, char* input, eertree* tree){
    int current = get_suffix_link(position, input, tree->suffix, tree);
    int letter = input[position] - 'a';

    if(tree->node[current].next[letter]){
        tree->suffix = tree->node[current].next[letter];
        return 0;
    }

    tree->index += 1;
    tree->suffix = tree->index;
    tree->node[tree->index].length = tree->node[current].length + 2;
    tree->node[current].next[letter] = tree->suffix;

    if(tree->node[tree->index].length == 1){
        tree->node[tree->index].suffix_link = 2;
        tree->node[tree->index].count = 1;        
    }
    else{
        int pos = get_suffix_link(position, input, tree->node[current].suffix_link, tree);
        tree->node[tree->suffix].suffix_link = tree->node[pos].next[letter];
    }
    return 1;
}
