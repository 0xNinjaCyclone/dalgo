

#include "select.h"
#include "move.h"

int normal_select(
    void *data, 
    size_t lSize, 
    int nItemSize, 
    int k,
    void *pResult,
    int (* compare)(void *, void *),
    void (* sort)(void *, size_t, int, int(*)(void *, void *))
) {
    void *pTemp;
    size_t lFullSize;
    int nIdx = -1;

    // invalid input
    if ( k >= lSize )
        return -1;

    // array size in bytes
    lFullSize = nItemSize * lSize;

    // a temporary array will hold the same data as input
    if ( !(pTemp = malloc(lFullSize)) )
        return -1;

    // copy the data to the temp array
    memcpy(pTemp, data, lFullSize);

    // sort the temp array
    sort(pTemp, lSize, nItemSize, compare);

    // set the result
    memcpy(pResult, (void *)((__SIZE_TYPE__) pTemp + k * nItemSize), nItemSize);

    // deallocate the temp array
    free(pTemp);

    // find the index of the target
    while ( compare((void *)((__SIZE_TYPE__) data + (++nIdx) * nItemSize), pResult) != 0 );

    return nIdx;
}

size_t partition(
    void *data, // in, out
    int nItemSize,
    size_t lStart,
    size_t lEnd,
    int (* compare)(void *, void *)
) {
    void *pPivot;
    size_t lIdx = lStart;

    // Take the last element as a pivot
    pPivot = (void *)((__SIZE_TYPE__) data + lEnd * nItemSize);
    
    for (size_t i = lStart; i <= lEnd; i++)
        // If the current item less than or equal the pivot, set it at the correct pos
        // And calculate the correct position of the pivot ( which will be the result of counting the smaller items  )
        if ( i == lEnd || compare((void *)((__SIZE_TYPE__) data + i * nItemSize), pPivot) <= 0 )
            GSwap(
                (void *)((__SIZE_TYPE__) data + lIdx++ * nItemSize),
                (void *)((__SIZE_TYPE__) data + i * nItemSize),
                nItemSize
            );


    return --lIdx; // return the index of the pivot
}

int quick_select(
    void *data, 
    size_t lSize, 
    int nItemSize, 
    int k,
    void *pResult, // out
    int (* compare)(void *, void *)
) {
    void *pTemp;
    size_t lFullSize;
    int nIdx;

    // invalid input
    if ( k >= lSize )
        return -1;

    // array size in bytes
    lFullSize = nItemSize * lSize;

    // a temporary array will hold the same data as input
    if ( !(pTemp = malloc(lFullSize)) )
        return -1;

    // copy the data to the temp array
    memcpy(pTemp, data, lFullSize);

    // find the index of the target in temp ( temp will be manipulated )
    nIdx = quick_select2(pTemp, nItemSize, k, 0, lSize-1, compare);

    // set the result
    memcpy(pResult, (void *)((__SIZE_TYPE__) pTemp + nIdx * nItemSize), nItemSize);

    // deallocate the temp array
    free(pTemp);

    // find the index of the target
    nIdx = -1;
    while ( compare((void *)((__SIZE_TYPE__) data + (++nIdx) * nItemSize), pResult) != 0 );

    return nIdx;
}

int quick_select2(
    void *data, 
    int nItemSize, 
    int k,
    size_t lStart,
    size_t lEnd,
    int (* compare)(void *, void *)
) {
    size_t lIdx;

    lIdx = partition(data, nItemSize, lStart, lEnd, compare);

    // If the position is same as k
    if ( lIdx - lStart == k )
        return lIdx;

    // If greater, process the left subarray
    if ( lIdx - lStart > k )
        return quick_select2(data, nItemSize, k, lStart, lIdx - 1, compare);

    // Else, process the right subarray
    return quick_select2(data, nItemSize, k - lIdx + lStart - 1, lIdx + 1, lEnd, compare);
}