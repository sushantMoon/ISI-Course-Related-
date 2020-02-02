#ifndef __COMMON_H__ 
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <sys/time.h>
#include <sys/resource.h>

#define DURATION(start, end) ((end.tv_usec - start.tv_usec) + (end.tv_sec - start.tv_sec) * 1000000)

#define MALLOC(type, n) (type *)malloc(sizeof(type)*n)
#define MIN(a, b) (a>b)?b:a
#define MAX(a, b) (a>b)?a:b
#define lli long long int
#define llu unsigned long long int

#endif // __COMMON_H__
