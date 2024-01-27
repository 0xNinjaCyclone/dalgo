#ifndef _dalgo_sort
#define _dalgo_sort

#include <stdio.h>

void selection_sort(void *data, size_t lSize, int nItemSize, int (* compare)(void *, void *));
void bubble_sort(void *data, size_t lSize, int nItemSize, int (* compare)(void *, void *));
void double_sort(void *data, size_t lSize, int nItemSize, int (* compare)(void *, void *));
void insertion_sort(void *data, size_t lSize, int nItemSize, int (* compare)(void *, void *));
void quick_sort(void *data, size_t lSize, int nItemSize, int (* compare)(void *, void *));
void quick_sort2(void *data, int nItemSize, size_t lStart, size_t lEnd, int (* compare)(void *, void *));
void merge_sort(void *data, size_t lSize, int nItemSize, int (* compare)(void *, void *));
void merge_sort2(void *data, int nItemSize, size_t lLeftIdx, size_t lRightIdx, int (* compare)(void *, void *));
void heap_sort(void *data, size_t ulSize, int nItemSize, int (* compare)(void *, void *));

#endif