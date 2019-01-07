#ifndef DYNAMIC_ALLOCATION_H_   /* Include guard */
#define DYNAMIC_ALLOCATION_H_

void free_dynamic(void *ptr);

char *single_char_array(int size);

char **double_char_array(int row, int col);


#endif // DYNAMIC_ALLOCATION_H_