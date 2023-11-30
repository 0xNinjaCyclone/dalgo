/*
    Search Implementation
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-2-2022
*/

#include "search.h"
#include <math.h>

int linear_search(void *data, void *key, size_t lSize, int nItemSize, int (*compare)(void *, void *))
{
    /* Return the position of the item or -1 if does not exist */
    
    for (size_t i = 0; i < lSize; i++)
        if ( compare( ((void *)(__SIZE_TYPE__) data + i * nItemSize ), key) == 0 )
            return i;

    return -1;
}

int dbl_linear_search(void *data, void *key, size_t lSize, int nItemSize, int (*compare)(void *, void *))
{
    /* Return the position of the item or -1 if does not exist */

    size_t lStart, lEnd;

    lStart = -1;
    lEnd = lSize;

    while ( ++lStart <= --lEnd )
    {
        if ( compare( ((void *)(__SIZE_TYPE__) data + lStart * nItemSize ), key) == 0 )
            return lStart;

        else if ( compare( ((void *)(__SIZE_TYPE__) data + lEnd * nItemSize ), key) == 0 )
            return lEnd;
    }

    return -1;
}

int binary_search(void *data, void *key, size_t lSize, int nItemSize, int (*compare)(void *, void *))
{
    /* Return the position of the item or -1 if does not exist */

    unsigned char found;
    int mid, low, high, res;

    found = low = 0;
    high = lSize - 1;

    while ( !found && low <= high )
    {
        mid = (low + high) / 2;
        res = compare( (void *)(__SIZE_TYPE__) data + mid * nItemSize, key );

        if ( res == 0 )
            found = 1;
        
        else if( res > 0 )
            high = mid - 1;

        else
            low = mid + 1;
    }
    
    return found ? mid : -1;
}

int jump_search(void *data, void *key, size_t lSize, int nItemSize, int (*compare)(void *, void *))
{
    /* Return the position of the item or -1 if does not exist */

    size_t lStep, lBlockSize, lIdx;

    lStep = lBlockSize = sqrt(lSize);

    while ( compare( ((void *)(__SIZE_TYPE__) data + (MIN(lStep, lSize) - 1) * nItemSize), key ) < 0 )
    {
        if ( lStep >= lSize )
            return -1;

        lStep += lBlockSize;
    }

    while ( lBlockSize-- )
    {
        lIdx = lStep - 1 - lBlockSize;

        if ( compare( ((void *)(__SIZE_TYPE__) data + lIdx * nItemSize ), key) == 0 )
            return lIdx;
    }
    
    return -1;
}