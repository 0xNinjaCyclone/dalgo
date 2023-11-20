/*
    Sort Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 20-12-2021
    Compile     => gcc -I../Algo/ ../Algo/helpers.c ../Algo/move.c ../Algo/sort.c sort.c -o sort
*/

#include "sort.h"
#include "helpers.h"

void print_number(void *n) { printf("%d", *(int *) n); }

int main(void) 
{
    int arr[] = {1,7,15,2,64,82,1,46,48,01,23,14,5,36,3};
    size_t lSize = sizeof(arr) / sizeof(int);

    printf("Original array = ");
    PrintArray(arr, lSize, sizeof(int), print_number);

    /* Sort array */
    selection_sort(arr, lSize, sizeof(int), IntCmp);

    printf("Sorted array   = ");
    PrintArray(arr, lSize, sizeof(int), print_number);

    return 0;
}