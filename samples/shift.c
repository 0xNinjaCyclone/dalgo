/*
    Shift Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 20-11-2023
    Compile     => gcc -I../Algo/ ../Algo/helpers.c ../Algo/move.c shift.c -o shift
*/

#include "move.h"
#include "helpers.h"

void print_number(void *n) { printf("%d", *(int *) n); }

int main(void) 
{
    int arr[] = {1,7,15,2,64,82,1,46,48,01,23,14,5,36,3};
    size_t lSize = sizeof(arr) / sizeof(int);

    printf("Original array = ");
    PrintArray(arr, lSize, sizeof(int), print_number);

    /* Shift the array to left */
    GLeftShift(arr, lSize, 3, sizeof(int));

    printf("array left     = ");
    PrintArray(arr, lSize, sizeof(int), print_number);

    /* Shift the array to right */
    GRightShift(arr, lSize, 5, sizeof(int));

    printf("array right    = ");
    PrintArray(arr, lSize, sizeof(int), print_number);

    /* Rotate the array to right */
    GRightRotate(arr, lSize, 5, sizeof(int));

    printf("rotate right   = ");
    PrintArray(arr, lSize, sizeof(int), print_number);

    /* Rotate the array to left */
    GLeftRotate(arr, lSize, 5, sizeof(int));

    printf("rotate left    = ");
    PrintArray(arr, lSize, sizeof(int), print_number);

    return 0;
}