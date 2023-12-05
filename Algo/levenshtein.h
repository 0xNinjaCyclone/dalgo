#ifndef _dalgo_levenshtein
#define _dalgo_levenshtein

#include <stdlib.h>
#include <string.h>

long levenshtein_distance(void *pStr1, size_t lStr1Size, void *pStr2, size_t lStr2Size, int nItemSize, int (* charcmp)(void *, void *));

#endif