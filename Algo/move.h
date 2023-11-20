#ifndef _dalgo_move
#define _dalgo_move

#include <stdlib.h>
#include <string.h>

void GSwap(void *x, void *y, size_t lSize);
void GLeftRotate(void *data, size_t lSize, size_t lNumberOfItems, int nItemSize);
void GRightRotate(void *data, size_t lSize, size_t lNumberOfItems, int nItemSize);
void GLeftShift(void *data, size_t lSize, size_t lTimes, int nItemSize);
void GRightShift(void *data, size_t lSize, size_t lTimes, int nItemSize);

#endif