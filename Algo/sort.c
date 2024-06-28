/*
    Sort Implementation
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 20-12-2021
*/

#include "sort.h"
#include "move.h"
#include "heap.h"

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

void double_sort(void *data, size_t lSize, int nItemSize, int (* compare)(void *, void *))
{
    for (size_t lCtr = 0; lCtr < (lSize - 1) / 2 + 1; lCtr++)
    {
        for (size_t lIdx = 0; lIdx < lSize - lCtr - 1; lIdx++)
        {
            if (compare(
                (void *)((__SIZE_TYPE__) data + lIdx * nItemSize),
                (void *)((__SIZE_TYPE__) data + (lIdx + 1) * nItemSize)
            ) > 0)
                GSwap(
                    (void *)((__SIZE_TYPE__) data + lIdx * nItemSize),
                    (void *)((__SIZE_TYPE__) data + (lIdx + 1) * nItemSize),
                    nItemSize
                );

            if (compare(
                (void *)((__SIZE_TYPE__) data + (lSize - 2 - lIdx) * nItemSize),
                (void *)((__SIZE_TYPE__) data + (lSize - 1 - lIdx) * nItemSize)
            ) > 0)
                GSwap(
                    (void *)((__SIZE_TYPE__) data + (lSize - 2 - lIdx) * nItemSize),
                    (void *)((__SIZE_TYPE__) data + (lSize - 1 - lIdx) * nItemSize),
                    nItemSize
                );
        }
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
    
    for (size_t i = lStart; i <= lEnd; i++)
        // If the current item less than or equal the pivot, set it at the correct pos
        // And calculate the correct position of the pivot ( which will be the result of counting the smaller items )
        if ( i == lEnd || compare((void *)((__SIZE_TYPE__) data + i * nItemSize), pPivot) <= 0 )
            GSwap(
                (void *)((__SIZE_TYPE__) data + lIdx++ * nItemSize),
                (void *)((__SIZE_TYPE__) data + i * nItemSize),
                nItemSize
            );


    return --lIdx; // return the index of the pivot
}

void quick_sort(void *data, size_t lSize, int nItemSize, int (* compare)(void *, void *))
{
    if ( lSize == 0 || lSize == 1 ) return;
    quick_sort2(data, lSize, nItemSize, 0, lSize - 1, compare);
}

void quick_sort2(void *data, size_t lSize, int nItemSize, size_t lStart, size_t lEnd, int (* compare)(void *, void *))
{
    if ( lStart >= lEnd || lEnd >= lSize ) return;

    size_t lPivotIdx;

    lPivotIdx = partition(data, nItemSize, lStart, lEnd, compare);

    // sort the left subarray.
    quick_sort2(data, lSize, nItemSize, lStart, lPivotIdx - 1, compare);

    // sort the right subarray.
    quick_sort2(data, lSize, nItemSize, lPivotIdx, lEnd, compare);
}

void merge(
    void *data, // out
    int nItemSize,
    size_t lStart,
    size_t lMiddle,
    size_t lEnd,
    int (* compare)(void *, void *)
) {
    void *pLeft, *pRight;
    size_t lLeftIdx, lRightIdx, lLeftSize, lRightSize, lIdx;

    // Calculate the size of each subarray
    lLeftSize = lMiddle - lStart + 1;
    lRightSize = lEnd - lMiddle;

    // Initial value for indexes
    lLeftIdx = lRightIdx = 0;
    lIdx = lStart;

    if ( !(pLeft = malloc(lLeftSize * nItemSize)) )
        return;

    if ( !(pRight = malloc(lRightSize * nItemSize)) )
        return;

    /* Seperate the array to left and right */
    memcpy(pLeft, (void *)((__SIZE_TYPE__) data + lStart * nItemSize), lLeftSize * nItemSize);
    memcpy(pRight, (void *)((__SIZE_TYPE__) data + (lMiddle + 1) * nItemSize), lRightSize * nItemSize);


    while ( lLeftIdx < lLeftSize && lRightIdx < lRightSize )
    {
        if (compare(
            (void *)((__SIZE_TYPE__) pLeft + lLeftIdx * nItemSize),
            (void *)((__SIZE_TYPE__) pRight + lRightIdx * nItemSize)
        ) <= 0)
            memcpy(
                (void *)((__SIZE_TYPE__) data + lIdx * nItemSize),
                (void *)((__SIZE_TYPE__) pLeft + lLeftIdx++ * nItemSize),
                nItemSize
            );

        else 
            memcpy(
                (void *)((__SIZE_TYPE__) data + lIdx * nItemSize),
                (void *)((__SIZE_TYPE__) pRight + lRightIdx++ * nItemSize),
                nItemSize
            );

        lIdx++;
    }

    // Copy the remaining elements of the left subarray
    while ( lLeftIdx < lLeftSize )
        memcpy(
            (void *)((__SIZE_TYPE__) data + lIdx++ * nItemSize),
            (void *)((__SIZE_TYPE__) pLeft + lLeftIdx++ * nItemSize),
            nItemSize
        );
    
    // Copy the remaining elements of the right subarray
    while ( lRightIdx < lRightSize )
        memcpy(
            (void *)((__SIZE_TYPE__) data + lIdx++ * nItemSize),
            (void *)((__SIZE_TYPE__) pRight + lRightIdx++ * nItemSize),
            nItemSize
        );

    free(pLeft);
    free(pRight);
    
}

void merge_sort(void *data, size_t lSize, int nItemSize, int (* compare)(void *, void *))
{
    if ( lSize == 0 || lSize == 1 ) return;
    merge_sort2(data, nItemSize, 0, lSize - 1, compare);
}

void merge_sort2(void *data, int nItemSize, size_t lStart, size_t lEnd, int (* compare)(void *, void *))
{
    if ( lStart >= lEnd ) return;

    size_t lMiddle;
    lMiddle = (lStart + lEnd) / 2;
    merge_sort2(data, nItemSize, lStart, lMiddle, compare);
    merge_sort2(data, nItemSize, lMiddle + 1, lEnd, compare);
    merge(data, nItemSize, lStart, lMiddle, lEnd, compare);

}

void heap_sort(void *data, size_t ulSize, int nItemSize, int (* compare)(void *, void *))
{
    Heap *htree;

    if ( ! (htree = heap_init(ulSize, nItemSize, MAXHEAP, malloc, free, NULL, compare)) )
        goto LEAVE;

    if ( ! heap_build(htree, data, ulSize) )
        goto LEAVE;

    
    while ( ulSize-- )
    {
        memcpy( (void *) data + ulSize * nItemSize, heap_rootdata(htree), nItemSize );
        heap_pop( htree );
    }

LEAVE:
    if ( htree ) 
        heap_cleanup( &htree );
}