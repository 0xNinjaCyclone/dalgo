

#include "levenshtein.h"

long levenshtein_distance(void *pStr1, size_t lStr1Size, void *pStr2, size_t lStr2Size, int nItemSize, int (* charcmp)(void *, void *))
{
    void *pSmaller, *pLargger;
    size_t *pPrev, *pCurr, *pTemp;
    size_t lSmallerSize, lLarggerSize, lDistance, lSubstitutions;

    if ( lStr1Size > lStr2Size )
    {
        pLargger = pStr1;
        pSmaller = pStr2;
        lLarggerSize = lStr1Size;
        lSmallerSize = lStr2Size;
    } else {
        pLargger = pStr2;
        pSmaller = pStr1;
        lLarggerSize = lStr2Size;
        lSmallerSize = lStr1Size;
    }

    if ( !(pPrev = (size_t *) malloc( (lSmallerSize + 1) * sizeof(size_t) )) )
        return -1;

    for (size_t i = 0; i <= lSmallerSize; i++)
        pPrev[i] = i;

    for (size_t lIdx1 = 0; lIdx1 < lLarggerSize; lIdx1++)
    {
        if ( !(pCurr = (size_t *) malloc( (lSmallerSize + 1) * sizeof(size_t) )) )
            return -1;

        memset(pCurr + 1, 0x00, lSmallerSize * sizeof(size_t));
        pCurr[0] = lIdx1 + 1;

        for (size_t lIdx2 = 0; lIdx2 < lSmallerSize; lIdx2++)
        {
            lDistance = pPrev[lIdx2 + 1] + 1;

            if ( lDistance > (pCurr[lIdx2] + 1) )
                lDistance = pCurr[lIdx2] + 1;

            lSubstitutions = pPrev[lIdx2] + ( charcmp(
                (void *)((__SIZE_TYPE__) pLargger + lIdx1 * nItemSize),
                (void *)((__SIZE_TYPE__) pSmaller + lIdx2 * nItemSize)
            ) != 0 );

            if ( lDistance > lSubstitutions )
                lDistance = lSubstitutions;

            pCurr[lIdx2 + 1] = lDistance;
            
        }

        pTemp = pPrev;
        pPrev = pCurr;

        free( pTemp );
    }

    lDistance = pPrev[lSmallerSize];
    free(pPrev);
    
    return lDistance;
}