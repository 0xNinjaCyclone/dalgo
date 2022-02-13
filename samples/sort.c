/*
    Sort Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 20-12-2021
    Compile     => gcc -I../Algo/ ../Algo/sort.c sort.c -o sort
*/

#include "sort.h"

void print_arr(int arr[],int nSize) 
{
    printf("[");
    for (size_t i = 0; i < nSize; i++)
    {
        printf("%d",arr[i]);

        if (i == nSize - 1) /* Last item */
            continue;

        else
            printf(",");
    }  

    printf("]\n");
}

int main(void) 
{
    int arr[] = {1,7,15,2,64,82,1,46,48,01,23,14,5,36,3};
    size_t nSize = sizeof(arr) / sizeof(int);

    printf("Original array = ");
    print_arr(arr, nSize);

    /* Sort array */
    bubble_sort(arr, nSize);

    printf("Sorted array   = ");
    print_arr(arr, nSize);

    return 0;
}