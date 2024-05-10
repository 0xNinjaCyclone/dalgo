/*
    Sort Test
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 10-05-2024
    Compile     => gcc -I../Algo/ -I../DS/ ../DS/heap.c ../Algo/helpers.c ../Algo/move.c ../Algo/sort.c sort_test.c -o sort_test
*/

#include "sort.h"
#include "helpers.h"
#include <time.h>

#define ARR_LEN 2000

#define TEST_SUCCESS(arr, n, cAlgName) \
    if ( test_sort_success(arr, n) ) \
        printf(cAlgName " PASSED - (%d)\n", n); \
    else { \
        printf(cAlgName " FAILED - (%d) - ", n); \
        PrintArray(arr, n, sizeof(int), IntPrint); \
    } \
    putchar('\n') \

int test_sort_success(int *arr, int n) {
    int i;
    
    while ( --n )
    {
        i = *arr++;

        if ( i > *arr )
            return 0;
    }

    return 1;
}

void test_sort_perf(
    int *arr,
    int n,
    void (* sort)(void *, size_t, int, int(*)(void *, void *))
)
{
    clock_t start, end;
    start = clock();
    sort( arr, n, sizeof(int), IntCmp );
    end = clock();
    printf( "Total Time = %0.2f\n", (end - start) / (double) CLOCKS_PER_SEC );
}

void test() {
    int arr[ARR_LEN] = { 0 };
    int tmp[ARR_LEN];
    int n;
    

    for ( int i = 0; i < ARR_LEN; i++ )
    {
        do {
            n = rand() % ARR_LEN;
        } while ( n == 0 );

        for ( int j = 0; j < n; j++ )
            arr[ j ] = rand() % 10000;
        
        
        memcpy( tmp, arr, n * sizeof(int) );
        test_sort_perf(arr, n, selection_sort);
        TEST_SUCCESS( arr, n, "Selection" );

        memcpy( arr, tmp, n * sizeof(int) );
        test_sort_perf(arr, n, bubble_sort);
        TEST_SUCCESS( arr, n, "Bubble" );

        memcpy( arr, tmp, n * sizeof(int) );
        test_sort_perf(arr, n, double_sort);
        TEST_SUCCESS( arr, n, "Double" );

        memcpy( arr, tmp, n * sizeof(int) );
        test_sort_perf(arr, n, insertion_sort);
        TEST_SUCCESS( arr, n, "Inserion" );

        memcpy( arr, tmp, n * sizeof(int) );
        test_sort_perf(arr, n, quick_sort);
        TEST_SUCCESS( arr, n, "Quick" );

        memcpy( arr, tmp, n * sizeof(int) );
        test_sort_perf(arr, n, merge_sort);
        TEST_SUCCESS( arr, n, "Merge" );

        memcpy( arr, tmp, n * sizeof(int) );
        test_sort_perf(arr, n, heap_sort);
        TEST_SUCCESS( arr, n, "Heap" );
    }

    
}

void main(void) {
    test();
}