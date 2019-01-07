#ifndef _G_COMMON_H_
#define _G_COMMON_H_
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#endif

#ifndef _G_MEMORY_ALLOCATION_H_
#define _G_MEMORY_ALLOCATION_H_
#define MALLOC(type, n) (type *)malloc(sizeof(type)*n)
#define CALLOC(type, n) (type *)calloc(sizeof(type), n)
#endif

#ifndef _G_COMPARISION_H_
#define _G_COMPARISION_H_
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif