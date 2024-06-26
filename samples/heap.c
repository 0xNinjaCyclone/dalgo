/*
    Heap Tree Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 26-06-2024
    Compile     => gcc -I../DS/ -I../Algo ../Algo/helpers.c ../DS/heap.c heap.c -o heap
*/

#include "heap.h"
#include "helpers.h"

#define MAX_HEAP_SIZE 15
#define HEAP_ARR_SIZE MAX_HEAP_SIZE/2


int main()
{
    Heap *pHeapTree;
    int arr[HEAP_ARR_SIZE];
    int nValue, nIdx;

    // Fill the array with random data
    for ( nIdx = 0; nIdx < HEAP_ARR_SIZE; nIdx++ )
        arr[ nIdx ] = rand() % 0xffff;

    // Initialize the heap tree
    pHeapTree = heap_init( MAX_HEAP_SIZE, sizeof(int), MINHEAP, malloc, free, IntPrint, IntCmp );

    // Failed?
    if ( !pHeapTree )
        return 1;

    // Constructing the tree
    if ( !heap_build(pHeapTree, arr, HEAP_ARR_SIZE) ) {
        // Failed!
        heap_cleanup( &pHeapTree );
        return 1;
    }

    // Dynamic insertion
    while ( nIdx-- )
    {
        nValue = rand() % 0xffff;
        heap_insert( pHeapTree, &nValue );
    }

    printf("Heap size = %d\n", heap_size(pHeapTree));
    heap_print( pHeapTree, true );
    heap_print( pHeapTree, false );
    heap_cleanup( &pHeapTree );

    return 0;
}