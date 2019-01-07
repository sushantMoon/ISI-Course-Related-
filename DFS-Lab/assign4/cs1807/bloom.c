#include "common.h"
#include "bloom.h"

// #define DEBUG 1

Bloom_Hash_Function *init_hash_bloom_filter(unsigned int (*first_hash_function)(const void *)){
    Bloom_Hash_Function *hash_function_object = CALLOC(Bloom_Hash_Function, 1);
    hash_function_object->hash_function = first_hash_function;
    hash_function_object->next = NULL;
    return hash_function_object;
}

void add_hash_bloom_filter(Bloom_Hash_Function *bloom_filter_hash, unsigned int (*new_hash_function)(const void *)){
    Bloom_Hash_Function *hash = init_hash_bloom_filter(new_hash_function);
    Bloom_Hash_Function *root = bloom_filter_hash;
    while(root->next != NULL){
        root = root->next;
    }
    root->next = hash;
}

Bloom_Filter *init_bloom_filter(Bloom_Hash_Function *bloom_filter_hash_list, unsigned int bloom_filter_size){
    Bloom_Filter *bloom_filter = CALLOC(Bloom_Filter, 1);
    bloom_filter->hash_head = bloom_filter_hash_list;
    bloom_filter->bloom_filter_size = bloom_filter_size;
    bloom_filter->hash_bits = CALLOC(unsigned char, bloom_filter->bloom_filter_size);
    return bloom_filter;
}

void free_bloom_filter(Bloom_Filter **bloom_filter){
    if((*bloom_filter)){
        Bloom_Hash_Function *h = (*bloom_filter)->hash_head;
        if (h) {
            Bloom_Hash_Function *t = h;
            h = h->next;
            free(t);   
        }
        free((*bloom_filter)->hash_bits);
        free((*bloom_filter));
        *bloom_filter = NULL;
    }
}

void add_element_bloom_filter(Bloom_Filter *bloom_filter, const void *data){
    #if defined(DEBUG)
        printf("Adding : %s | %p...\n", (char *)data, (void *)data);
    #endif // DEBUG

    Bloom_Hash_Function *h = bloom_filter->hash_head;
    unsigned char *hash_bits = bloom_filter->hash_bits;
    while(h){
        unsigned int hash_value = h->hash_function(data);

        #if defined(DEBUG)
            printf("\tfunction: %p\n", (void *)(h->hash_function));
            printf("\thash_value: %d\n", (int)hash_value);
        #endif // DEBUG

        hash_value = hash_value % bloom_filter->bloom_filter_size;

        #if defined(DEBUG)
            printf("\tscaled_hash_value: %d\n", (int)hash_value);
        #endif // DEBUG

        hash_bits[hash_value] = hash_bits[hash_value] | (1 << (hash_value % 8));
        
        #if defined(DEBUG)
            printf("\thash_bits[hash_value]: %d\n\n", (int)hash_bits[hash_value]);
        #endif // DEBUG

        h = h->next;
    }
}

int search_element_bloom_filter(Bloom_Filter *bloom_filter, const void *data){
    #if defined(DEBUG)
        printf("Searching : %s | %p...\n", (char *)data, (void *)data);
    #endif // DEBUG

    Bloom_Hash_Function *h = bloom_filter->hash_head;
    unsigned char *hash_bits = bloom_filter->hash_bits;
    while(h){
        unsigned int hash_value = h->hash_function(data);

        #if defined(DEBUG)
            printf("\tfunction: %p\n", (void *)(h->hash_function));
            printf("\thash_value: %d\n", (int)hash_value);
        #endif // DEBUG

        hash_value = hash_value % bloom_filter->bloom_filter_size;

        #if defined(DEBUG)
            printf("\tscaled_hash_value: %d\n", (int)hash_value);
            printf("\thash_bits[hash_value]: %d\n\n", (int)hash_bits[hash_value]);
        #endif // DEBUG

        if( !(hash_bits[hash_value] & (1 << (hash_value % 8)) )){
            return 0;
        }
        h = h->next;
    }
    return 1;
}

int check_and_add_element_bloom_filter(Bloom_Filter *bloom_filter, const void *data){
    #if defined(DEBUG)
        printf("Checking and Adding only if not present already : %s | %p...\n", (char *)data, (void *)data);
    #endif // DEBUG

    Bloom_Hash_Function *h = bloom_filter->hash_head;
    unsigned char *hash_bits = bloom_filter->hash_bits;
    int flag = 0;
    while(h){
        unsigned int hash_value = h->hash_function(data);

        #if defined(DEBUG)
            printf("\tfunction: %p\n", (void *)(h->hash_function));
            printf("\thash_value: %d\n", (int)hash_value);
        #endif // DEBUG

        hash_value = hash_value % bloom_filter->bloom_filter_size;

        #if defined(DEBUG)
            printf("\tscaled_hash_value: %d\n", (int)hash_value);
        #endif // DEBUG

        if( !(hash_bits[hash_value] & (1 << (hash_value % 8)) )){
            hash_bits[hash_value] = hash_bits[hash_value] | (1 << (hash_value % 8));
            flag = 1;
        }
        
        #if defined(DEBUG)
            printf("\thash_bits[hash_value]: %d\n\n", (int)hash_bits[hash_value]);
        #endif // DEBUG

        h = h->next;
    }
    
    if (flag == 1) {
        printf("Bloom Filter : Inserted\n");
        return 1;
    }

    printf("Bloom Filter : Duplicate\n");
    return 0;
    
}