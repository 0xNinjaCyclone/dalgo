/*
    Search Implementation
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-2-2022
*/

#include "search.h"

int linear_search(int arr[], size_t nSize, int key)
{
    /* Return the position of the item or -1 if does not exist */

    for (size_t i = 0; i < nSize; i++)
        if (arr[i] == key)
            return i;

    return -1;
}

int binary_search(int arr[], size_t nSize, int key)
{
    /* Return the position of the item or -1 if does not exist */

    int found, mid, low, high;

    found = low = 0;
    high = nSize - 1;

    while (!found || low > high)
    {
        mid = (low + high) / 2;

        if (arr[mid] == key)
            found = 1;
        
        else if(arr[mid] > key)
            high = mid - 1;

        else
            low = mid + 1;
    }
    
    return found ? mid : -1;
}