

#include "move.h"
#include "helpers.h"

void GSwap(void *x, void *y, size_t lSize)
{
    void *pTemp = NULL;

    if ( pTemp = malloc( lSize ) )
    {
        memcpy( pTemp, x, lSize );
        memcpy( x, y, lSize );
        memcpy( y, pTemp, lSize );
        free( pTemp );
    }
}

void GLeftRotate(void *data, size_t lSize, size_t lNumberOfItems, int nItemSize)
{
    void *pTemp;
    size_t lRotateSize;

    lRotateSize = lNumberOfItems * nItemSize;

    if ( pTemp = malloc(lRotateSize) )
    {
        memcpy( pTemp, data, lRotateSize );
        memcpy( data, (void *)((__SIZE_TYPE__) data + lRotateSize), (lSize * nItemSize) - lRotateSize );
        memcpy( (void *)((__SIZE_TYPE__) data + (lSize * nItemSize) - lRotateSize), pTemp, lRotateSize );
        free( pTemp );
    }
}

void GRightRotate(void *data, size_t lSize, size_t lNumberOfItems, int nItemSize)
{
    void *pTemp;
    size_t lRotateSize;

    lRotateSize = lNumberOfItems * nItemSize;

    if ( pTemp = malloc(lRotateSize) )
    {
        memcpy( pTemp, (void *)((__SIZE_TYPE__) data + (lSize * nItemSize) - lRotateSize), lRotateSize );
        memcpy( (void *)((__SIZE_TYPE__) data + lRotateSize), data, (lSize * nItemSize) - lRotateSize );
        memcpy( data, pTemp, lRotateSize );
        free( pTemp );
    }
}

void GLeftShift(void *data, size_t lSize, size_t lTimes, int nItemSize)
{
    void *pTemp;
    size_t i, j, k, gcd;

    if( lSize <= 1 || !lTimes ) return; // cannot mod by zero
    lTimes %= lSize;

    gcd = calc_GCD(lSize, lTimes);
    pTemp = malloc( nItemSize );

    // i is initial starting position
    // Copy from k -> j, stop if k == i, since arr[i] already overwritten
    for(i = 0; i < gcd; i++) 
    {
        memcpy(pTemp, (void *)((__SIZE_TYPE__) data + nItemSize * i), nItemSize); // tmp = arr[i]

        for(j = i ;; j = k) {
            k = j + lTimes;
            if( k >= lSize ) k -= lSize;
            if( k == i ) break;
            memcpy((void *)((__SIZE_TYPE__) data + nItemSize * j), (void *)((__SIZE_TYPE__) data + nItemSize * k), nItemSize); // arr[j] = arr[k];
        }

        memcpy((void *)((__SIZE_TYPE__) data + nItemSize * j), pTemp, nItemSize); // arr[j] = tmp;
    }

    free( pTemp );
    
}

void GRightShift(void *data, size_t lSize, size_t lTimes, int nItemSize)
{
    if( lSize <= 1 || !lTimes ) return; // cannot mod by zero
    lTimes %= lSize;
    
    // cycle right by `s` is equivalent to cycle left by `n - s`
    GLeftShift(data, lSize, lSize - lTimes, nItemSize);
}