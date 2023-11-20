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

// HAS A BUG NEED TO BE FIXED
void insertion_sort(void *data, size_t lSize, int nItemSize, int (* compare)(void *, void *))
{
    void *pKey;
    size_t lIdx;

    for (size_t i = 1; i < lSize; i++)
    {
        pKey = (void *)((__SIZE_TYPE__) data + i * nItemSize);
        lIdx = i - 1;
        

        /* Shift elements from left to right to put the item in the correct position */
        while ( lIdx >= 0 && compare((void *)((__SIZE_TYPE__) data + lIdx * nItemSize), pKey ) > 0 ) 
        {
            memcpy(
                (void *)((__SIZE_TYPE__) data + (lIdx + 1) * nItemSize),
                (void *)((__SIZE_TYPE__) data + lIdx * nItemSize),
                nItemSize
            );
            lIdx--;
        }

        /* Put the item at the correct pos */
        memcpy(
            (void *)((__SIZE_TYPE__) data + (lIdx + 1) * nItemSize),
            pKey,
            nItemSize
        );
    }
}