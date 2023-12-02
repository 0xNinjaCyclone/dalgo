/*
    Select Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 1-12-2023
    Compile     => gcc -I../Algo/ ../Algo/helpers.c ../Algo/move.c ../Algo/select.c select.c -o select
*/

#include "select.h"
#include "helpers.h"

int main()
{
    int arr[] = {1,7,15,2,64,82,1,46,48,01,23,14,5,36,3};
    size_t lSize = sizeof(arr) / sizeof(int);
    int k, n, i;

    k = 10;
    i = quick_select(arr, lSize, sizeof(int), k, &n, IntCmp);

    if ( i == -1 )
    {
        puts("Invalid input");
        return EXIT_FAILURE;
    }

    printf("The array = ");
    PrintArray(arr, lSize, sizeof(int), IntPrint);
    printf("%dth smallest element = %d, index = %d\n", k, n, i);

    return EXIT_SUCCESS;
}