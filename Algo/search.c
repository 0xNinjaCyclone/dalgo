/*
    Search Implementation
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-2-2022
*/

#include "search.h"

int linear_search(void *data, void *key, size_t lSize, int nItemSize, int (*compare)(void *, void *))
{
    /* Return the position of the item or -1 if does not exist */
    
    for (size_t i = 0; i < lSize; i++)
        if ( compare( ((void *)(__SIZE_TYPE__) data + i * nItemSize ), key) == 0 )
            return i;

    return -1;
}

int binary_search(void *data, void *key, size_t lSize, int nItemSize, int (*compare)(void *, void *))
{
    /* Return the position of the item or -1 if does not exist */

    unsigned char found;
    int mid, low, high, res;

    found = low = 0;
    high = lSize - 1;

    while (!found || low > high)
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