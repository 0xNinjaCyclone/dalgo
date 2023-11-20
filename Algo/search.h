#ifndef _dalgo_search
#define _dalgo_search

#include <stdio.h>

int linear_search(void *data, void *key, size_t lSize, int nItemSize, int (*compare)(void *, void *));
int binary_search(void *data, void *key, size_t lSize, int nItemSize, int (*compare)(void *, void *));

#endif
