/*
    Binary Search Tree Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 28-11-2023
    Compile     => gcc -I../DS/ -I../Algo ../Algo/helpers.c ../DS/bstree.c bstree.c -o bstree
*/

#include "bstree.h"
#include "helpers.h"

void print_int(void *item) { printf("%d", *(int *) item); }

int main()
{
    BinarySearchTree *t;
    int value;

    /* Initialize the binary search tree */
    t = bst_init( sizeof(int), malloc, free, print_int, IntCmp );

    value = 10;
    bst_insert(t, &value);

    value = 20;
    bst_insert(t, &value);

    value = 5;
    bst_insert(t, &value);

    value = 2;
    bst_insert(t, &value);

    value = 30;
    bst_insert(t, &value);

    value = 25;
    bst_insert(t, &value);

    value = 10;
    bst_delete(t, IN_ORDER, &value);
    
    bst_print(t, PRE_ORDER);

    bst_cleanup(&t);

    return 0;
}