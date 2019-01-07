/*-----------------------------------
Name: Sushant Moon
Roll number: CS1807
Date: 4 December, 2018
Program description: 

Compile Using : ```gcc -g -Wall -o prog3 cs1807-assign4-prog3-zxxx.c bloom.c avl.c -lm```
Run : ``` ./prog3 {m} {k} {num1} {num1} {num2} {num3} and so on ... ```
Acknowledgements:

// Reference : https://stackoverflow.com/questions/14409466/simple-hash-functions
// Analysis:
    // Space Complexity :
    //     Array of 15485863*8 bits is required.
    // Time Complexity :
    //     1. For Searching within the Binary array, Order(# of hash functions) i.e Order(3)   (jenkins/sdbm/djb2)
    //     2. For Adding data in the binary array, Order(# of hash functions) i.e Order(3)
    //     3. At any given time probability of false positive (p) is dependent on three factors 
    //         a. Total number of hash Functions (k)
    //         b. Total number of elements that we have already added in the binary array (n)
    //         c. Size of the binary array (m)
    //         Therefore p is given by the formula:
    //             p = (1 - exp( -(k*n)/m )) ^ k
//  
------------------------------------*/


#include "common.h"
#include "bloom.h"
#include "avl.h"
#include <sys/time.h>
#include <sys/resource.h>

#define DURATION(start, end) ((end.tv_usec - start.tv_usec) + (end.tv_sec - start.tv_sec) * 1000000)
#define LOOPCOUNT 10000

// #define DEBUG 1

unsigned int djb2(const void *_str) {
	const char *str = _str;
	unsigned int hash = 5381;
	char c;
	while ((c = *str++)) {
		hash = ((hash << 5) + hash) + c;
	}
	return hash;
}

unsigned int jenkins(const void *_str) {
    const char *str = _str;
	unsigned int hash = 0;
	char c;
	while ((c = *str++)) {
        hash = hash + c;
		hash = hash + (hash << 10);
		hash = hash ^ (hash >> 6);
    }
	hash = hash + (hash << 3);
	hash = hash ^ (hash >> 11);
	hash = hash + (hash << 15);
	return hash;
}

unsigned int sdbm(const void *_str){
    const char *str = _str;
	unsigned int hash = 0;
	char c;
	while ((c = *str++)) {
		hash = c + (hash << 6) + (hash << 16) - hash;
	}
    return hash;
}

unsigned int assignment_random(const void *_str){
    srand(atoi(_str));
    return rand();
}

int main(int argc, char const *argv[])
{
    // Bloom_Hash_Function *hash_list = init_hash_bloom_filter(sdbm);
    // add_hash_bloom_filter(hash_list, djb2);
    // add_hash_bloom_filter(hash_list, jenkins);
    // Bloom_Filter *bloom_filter = init_bloom_filter(hash_list, _BLOOM_FILTER_SIZE_);

    // #if defined(DEBUG)
    //     int i = 0;
    //     while(i<1){
    //         printf("####### i = %d #######\n", i);
    //         printf("djb2[%s] : %d", "Bloom Filter Testing", (unsigned int)djb2("Bloom Filter Testing"));
    //         printf("#######\n");
    //         printf("jenkins[%s] : %d", "Bloom Filter Testing", (unsigned int)jenkins("Bloom Filter Testing"));
    //         printf("#######\n");
    //         printf("sdbm[%s] : %d", "Bloom Filter Testing", (unsigned int)sdbm("Bloom Filter Testing"));
    //         printf("#######\n");
    //         i++;
    //     }
    // #endif // DEBUG

    // #if defined(DEBUG)    
    //     // Testing the waters
    //     // Example 1
    //     printf("Searching for '%s', Answer (Must be 0): %d\n", "Bloom Filter Testing", search_element_bloom_filter(bloom_filter, "Bloom Filter Testing"));
    //     printf("Adding '%s' to the filter.\n", "Bloom Filter Testing");
    //     add_element_bloom_filter(bloom_filter, "Bloom Filter Testing");
    //     printf("Searching for '%s', Answer (Must be 1): %d\n", "Bloom Filter Testing", search_element_bloom_filter(bloom_filter, "Bloom Filter Testing"));
    //     printf("Searching for '%s', Answer ( Must be 0 with some probability): %d\n", "Filter Testing Bloom", search_element_bloom_filter(bloom_filter, "Filter Testing Bloom"));

    //     // Testing the waters
    //     // Example 2
    //     printf("Searching for '%s', Answer (Must be 0): %d\n", "5684213", search_element_bloom_filter(bloom_filter, "5684213"));
    //     printf("Adding '%s' to the filter.\n", "5684213");
    //     add_element_bloom_filter(bloom_filter, "5684213");
    //     printf("Searching for '%s', Answer (Must be 1): %d\n", "5684213", search_element_bloom_filter(bloom_filter, "5684213"));
    //     printf("Searching for '%s', Answer ( Must be 0 with some probability): %d\n", "5683421", search_element_bloom_filter(bloom_filter, "5683421"));

    //     // Testing the waters
    //     // Example 3
    //     printf("Searching for '%s', Answer (Must be 0): %d\n", "hello, are you with me ??", search_element_bloom_filter(bloom_filter, "hello, are you with me ??"));
    //     printf("Adding '%s' to the filter.\n", "hello, are you with me ??");
    //     add_element_bloom_filter(bloom_filter, "hello, are you with me ??");
    //     printf("Searching for '%s', Answer (Must be 1): %d\n", "hello, are you with me ??", search_element_bloom_filter(bloom_filter, "hello, are you with me ??"));
    //     printf("Searching for '%s', Answer ( Must be 0 with some probability): %d\n", "hello, are you with me ?? hello ??", search_element_bloom_filter(bloom_filter, "hello, are you with me ?? hello ??"));
    // #endif // DEBUG
    
    // free_bloom_filter(&bloom_filter);


    Bloom_Hash_Function *hash_list = init_hash_bloom_filter(assignment_random);
    int j, number_nodes=0, true_negative=0, false_positive=0;
    long long int time_taken_bloom_filter = 0, time_taken_avl_tree = 0;

    
    struct rusage usageInfo;
    struct timeval startUser, startSys, endUser, endSys;

    for(j = 0; j < (atoi(argv[2]) - 1); j++){
        add_hash_bloom_filter(hash_list, assignment_random);
    }
    
    add_hash_bloom_filter(hash_list, jenkins);
    Bloom_Filter *bloom_filter = init_bloom_filter(hash_list, (atoi(argv[1])/8)+1);
    
    AVL_Tree_Node *root = NULL;

    for(j = 3; j < argc; j++){
        printf("Input is : %s\n", argv[j]);
        // inserting in the avl
        if (0 != getrusage(RUSAGE_SELF, &usageInfo))
            perror("getrusage: ");
        startUser = usageInfo.ru_utime;
        startSys = usageInfo.ru_stime;
        root = avl_tree_insert(root, atoi(argv[j]));
        if (0 != getrusage(RUSAGE_SELF, &usageInfo))
            perror("getrusage: ");
        endUser = usageInfo.ru_utime;
        endSys = usageInfo.ru_stime;
        time_taken_avl_tree += (DURATION(startUser, endUser) + DURATION(startSys, endSys));


        int count_avl = avl_tree_count_check(root, atoi(argv[j]));
        if (count_avl == 1){
            number_nodes += 1;
        }

        // inserting in the bloom
        if (0 != getrusage(RUSAGE_SELF, &usageInfo))
            perror("getrusage: ");
        startUser = usageInfo.ru_utime;
        startSys = usageInfo.ru_stime;
        int count_bloom = check_and_add_element_bloom_filter(bloom_filter, argv[j]);
        if (0 != getrusage(RUSAGE_SELF, &usageInfo))
            perror("getrusage: ");
        endUser = usageInfo.ru_utime;
        endSys = usageInfo.ru_stime;
        time_taken_bloom_filter += (DURATION(startUser, endUser) + DURATION(startSys, endSys));


        if ((count_avl == 1) && (count_bloom == 0)){
            // avl inserted but bloom says it is duplicate
            // hence false positive
            false_positive += 1;
        }
        // else if ( ((count_avl > 1) && (count_bloom == 0)) || (count_avl == count_bloom) ){
        else if ( ((count_avl > 1) && (count_bloom == 0)) ){
            true_negative += 1;
        }
        printf("------------\n");
    }
    
    free_bloom_filter(&bloom_filter);
    avl_tree_free(root);

    // Statistics
    printf("AVL Tree : \n"
            "Number of Nodes = %d\n"
            "Total Size in Bytes = %d\n"
            "Total Time Taken : %LF ms\n",
                                        number_nodes,
                                        (int)(number_nodes*sizeof(AVL_Tree_Node)), 
                                        (long double)((long double)time_taken_avl_tree/(long double)LOOPCOUNT)
        );
    printf("Bloom Filter : \n"       
            "Total Size in Bytes = %s\n"
            "Total Number of Hash Functions = %s\n"
            "Total Time Taken : %LF ms\n"
            "False Positive Rate Percent(FP*100/FP+TN) = %f\n", 
                                        argv[1], 
                                        argv[2], 
                                        (long double)((long double)time_taken_bloom_filter/(long double)LOOPCOUNT), 
                                        (double)(((double)false_positive*100)/((double)false_positive+(double)true_negative))
        );
    return 0;
}

