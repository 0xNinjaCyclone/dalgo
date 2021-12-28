/*
    Sort Implementation
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 20-12-2021
*/

#include "sort.h"


void linear_sort(int arr[],size_t nSize)
{
    int swaper, counter = 0;

    do
    {  
        for (size_t i = 0; i < nSize; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                swaper = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = swaper;
            }
        }
        
    } while (++counter < nSize);
    
}
