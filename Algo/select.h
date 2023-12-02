#ifndef _dalgo_select
#define _dalgo_select

#include <stdlib.h>
#include <string.h>

int normal_select(
    void *data, 
    size_t lSize, 
    int nItemSize, 
    int k,
    void *pResult, // out
    int (* compare)(void *, void *),
    void (* sort)(void *, size_t, int, int(*)(void *, void *))
);

int quick_select(
    void *data, 
    size_t lSize, 
    int nItemSize, 
    int k,
    void *pResult, // out
    int (* compare)(void *, void *)
);

int quick_select2(
    void *data, 
    int nItemSize, 
    int k,
    size_t lStart,
    size_t lEnd,
    int (* compare)(void *, void *)
);

#endif