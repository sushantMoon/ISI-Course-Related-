#if !defined(__G_BLOOM_FILTER__)
#define __G_BLOOM_FILTER__

#define _BLOOM_FILTER_SIZE_ 15485863

typedef struct Bloom_Hash_Function{
    unsigned int (*hash_function)(const void *);
    struct Bloom_Hash_Function *next;   
}Bloom_Hash_Function;
// Node for the linked list of hash functions that will be used for Bloom Filter

Bloom_Hash_Function *init_hash_bloom_filter(unsigned int (*first_hash_function)(const void *));
// creates initializes hash function object for the bloom filter, with the first hash_function supplied, it returns pointer to the Bloom_Filter_Hash object

typedef struct Bloom_Filter{
    Bloom_Hash_Function *hash_head;
    // hash functions are stored in a linked list fashion
    unsigned char *hash_bits;
    // binary array which we modify bit wise
    unsigned int bloom_filter_size;
    // total size of the bloom filter
}Bloom_Filter;

void add_hash_bloom_filter(Bloom_Hash_Function *bloom_filter_hash_list, unsigned int (*new_hash_function)(const void *));
// adds the hash functions to the Bloom_Hash_Function object

Bloom_Filter *init_bloom_filter(Bloom_Hash_Function *bloom_filter_hash_list);
// initializes a bloom filter, user would have to add the hash functions to the Bloom_Hash_Function Object
void free_bloom_filter(Bloom_Filter **bloom_filter);
// frees the space allocated to the bloom filter
void add_element_bloom_filter(Bloom_Filter *bloom_filter, const void *data);
// For adding the elements to the bloom filter
int search_element_bloom_filter(Bloom_Filter *bloom_filter, const void *data);
// returns 0 if defenitely (never flase negative) not present in the filter
// returns 1 if probably (false positive posssible) present in the filter


#endif // __G_BLOOM_FILTER__












//  Reference :
//  1. https://drewdevault.com/2016/04/12/How-to-write-a-better-bloom-filter-in-C.html
//  2. https://www.youtube.com/watch?v=Bay3X9PAX5k
//  3. https://stackoverflow.com/questions/14409466/simple-hash-functions
