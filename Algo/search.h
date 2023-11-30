#ifndef _dalgo_search
#define _dalgo_search

#include <stdio.h>
#include <stdlib.h>


#ifndef min
#define MIN(x, y) ( (x < y) ? x : y )

#else
#define MIN min

#endif


int linear_search(void *data, void *key, size_t lSize, int nItemSize, int (*compare)(void *, void *));
int dbl_linear_search(void *data, void *key, size_t lSize, int nItemSize, int (*compare)(void *, void *));
int binary_search(void *data, void *key, size_t lSize, int nItemSize, int (*compare)(void *, void *));
int jump_search(void *data, void *key, size_t lSize, int nItemSize, int (*compare)(void *, void *));

#endif
