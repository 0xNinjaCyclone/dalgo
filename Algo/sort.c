/*
    Sort Implementation
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 20-12-2021
*/

#include "sort.h"
#include "move.h"

void selection_sort(void *data, size_t lSize, int nItemSize, int (* compare)(void *, void *))
{
    int idx;

    for (size_t i = 0; i < lSize - 1; i++)
    {
        idx = i;

        for (size_t j = i + 1; j < lSize; j++)
            
            if (compare(
                (void *)((__SIZE_TYPE__) data + idx * nItemSize),
                (void *)((__SIZE_TYPE__) data + j * nItemSize)
            ) > 0)
                idx = j;

        GSwap(
            (void *)((__SIZE_TYPE__) data + i * nItemSize),
            (void *)((__SIZE_TYPE__) data + idx * nItemSize),
            nItemSize
        );
    }
}

void bubble_sort(void *data, size_t lSize, int nItemSize, int (* compare)(void *, void *))
{
    int counter = 0;

    while (++counter < lSize) 
    {  
        for (size_t i = 0; i < lSize - counter; i++)
            
            if (compare(
                (void *)((__SIZE_TYPE__) data + i * nItemSize),
                (void *)((__SIZE_TYPE__) data + (i + 1) * nItemSize)
            ) > 0)
                GSwap(
                    (void *)((__SIZE_TYPE__) data + i * nItemSize),
                    (void *)((__SIZE_TYPE__) data + (i + 1) * nItemSize),
                    nItemSize
                );
        
    }
    
}

void insertion_sort(void *data, size_t lSize, int nItemSize, int (* compare)(void *, void *))
{
    void *pKey;
    size_t lIdx; 

    if ( !(pKey = malloc(nItemSize)) )
        return;

    for (size_t i = 1; i < lSize; i++)
    {
        memcpy( pKey, (void *)((__SIZE_TYPE__) data + i * nItemSize), nItemSize );
        lIdx = i;
        
        /* Shift elements from left to right to put the item in the correct position */
        while ( lIdx-- && compare((void *)((__SIZE_TYPE__) data + lIdx * nItemSize), pKey ) > 0 ) 
            memmove(
                (void *)((__SIZE_TYPE__) data + (lIdx + 1) * nItemSize),
                (void *)((__SIZE_TYPE__) data + lIdx * nItemSize),
                nItemSize
            );

        /* Put the item at the correct pos */
        memmove(
            (void *)((__SIZE_TYPE__) data + (lIdx + 1) * nItemSize),
            pKey,
            nItemSize
        );
    }

    free( pKey );
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
    
    for (size_t i = lStart; i < lEnd; i++)
        // If the current item less than or equal the pivot, set it at the correct pos
        // And calculate the correct position of the pivot ( which will be the result of counting the smaller items )
        if ( compare((void *)((__SIZE_TYPE__) data + i * nItemSize), pPivot) <= 0 )
            GSwap(
                (void *)((__SIZE_TYPE__) data + lIdx++ * nItemSize),
                (void *)((__SIZE_TYPE__) data + i * nItemSize),
                nItemSize
            );


    // If the pivot was not in the correct position
    if ( lIdx != lStart )
        GSwap(
            (void *)((__SIZE_TYPE__) data + lIdx * nItemSize),
            (void *)((__SIZE_TYPE__) data + lEnd * nItemSize),
            nItemSize
        );

    return lIdx; // return the index of the pivot
}

void quick_sort(void *data, size_t lSize, int nItemSize, int (* compare)(void *, void *))
{
    if ( lSize == 0 ) return;
    quick_sort2(data, nItemSize, 0, lSize - 1, compare);
}

void quick_sort2(void *data, int nItemSize, size_t lStart, size_t lEnd, int (* compare)(void *, void *))
{
    if ( lStart >= lEnd ) return;

    size_t lPivotIdx;

    lPivotIdx = partition(data, nItemSize, lStart, lEnd, compare);

    // sort the left subarray.
    quick_sort2(data, nItemSize, lStart, lPivotIdx - 1, compare);

    // sort the right subarray.
    quick_sort2(data, nItemSize, lPivotIdx, lEnd, compare);
}