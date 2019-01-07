#include "common.h"

#include <gdsl/gdsl_rbtree.h>

#define GDSL_OK 0

gdsl_element_t my_alloc(void *data) {
    int *p;

    if (NULL == (p = Malloc(1, int)))
        ERR_MESG("my_alloc: out of memory");
    *p = *( (int *) data );
    return p;
}

void my_free(gdsl_element_t E) {
    free(E);
}

long int my_compare(const gdsl_element_t E, void * value) {
    int v1 = *( (int *) value );
    int v2 = *( (int *) E );

    return (v2 - v1);
}

int my_map(const gdsl_element_t E, gdsl_location_t l, void * user_data) {
    return GDSL_MAP_CONT;
    // return GDSL_MAP_STOP;
}

int main(int ac, char *av[])
{
    int i, data, status;
    gdsl_rbtree_t my_tree;

    if (NULL == (my_tree = gdsl_rbtree_alloc("First-tree", my_alloc, my_free,
                                             my_compare)))
        ERR_MESG("RB tree creation failed");
                                             
    for (i = 1; i < ac; i++) {
        data = atoi(av[i]);
        gdsl_rbtree_insert(my_tree, (void *) &data, &status);
        printf("%lu\n", gdsl_rbtree_get_size(my_tree));
    }

    return 0;
}
