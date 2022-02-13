/*
    Sort Implementation
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 20-12-2021
*/

#include "sort.h"

void selection_sort(int arr[], size_t nSize)
{
    int idx, swapper;

    for (size_t i = 0; i < nSize - 1; i++)
    {
        idx = i;

        for (size_t j = i + 1; j < nSize; j++)
            if (arr[idx] > arr[j])
                idx = j;

        swapper = arr[i];
        arr[i] = arr[idx];
        arr[idx] = swapper;
    }
}

void bubble_sort(int arr[], size_t nSize)
{
    int swapper, counter = 0;

    while (++counter < nSize) 
    {  
        for (size_t i = 0; i < nSize - counter; i++)
            if (arr[i] > arr[i + 1])
            {
                swapper = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = swapper;
            }
        
    }
    
}

void insertion_sort(int arr[], size_t nSize)
{
    int key, idx;

    for (size_t i = 1; i < nSize; i++)
    {
        key = arr[i];
        idx = i - 1;

        /* Shift elements from left to right to put the item in the correct position */
        while (idx >= 0 && arr[idx] > key) 
        {
            arr[idx + 1] = arr[idx];
            idx--;
        }

        arr[idx + 1] = key;
        
    }
}