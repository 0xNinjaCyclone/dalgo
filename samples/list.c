/*
    List Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-2-2022
    Compile     => gcc -I../DS/ -I../Algo/ ../Algo/move.c ../Algo/helpers.c ../DS/list.c list.c -o list
*/


#include "list.h"
#include "helpers.h"

void print(void *item) { printf("%d", *(int *)item); }

void main(void)
{
    List *mylist = list_init(10, sizeof(int)); /* initiate a list with max size equal 10 */
    int value, i;
    size_t found;

    while ( 1 )
    {
        if ( list_full(mylist) )
        {
            puts("\nList is full !!");
            break;
        } else {
            printf("Enter a number value :");
            scanf("%d", &value);

            /* Append to our list */
            list_insert(mylist, &value);
        }

    }

    /* Delete last item */
    list_delete(mylist);

    /* Delete first item */
    list_deleteAt(mylist, 0);

    /* Multiply the first 3 items by 10 */
    for (size_t i = 0; i < 3; i++)
    {
        value = *( (int *) list_getitemAt(mylist, i) ) * 10;
        list_updateAt(mylist, i,  &value);
    }
    
    /* Print all list items */
    puts("\nPrint :");
    list_print(mylist, print);

    /* Search */
    printf("\n(Search) Enter an item :");
    scanf("%d", &i);

    found = list_search(mylist, &i, IntCmp);

    if (found != -1) {
        /* We found it */
        printf("Item position (%d) = %d\n", i, found);
    } else {
        printf("Item (%d) not found\n", i);
    }

    /* Reverse list */
    puts("\nReverse :");
    list_reverse(mylist);

    /* Print again to see reversed list */
    list_print(mylist, print);

    /* Print some data */
    printf("\nLast value = %d, Size = %d\n", *(int *) list_getitem(mylist), list_size(mylist));

    /* We had better call this func to free memory */
    list_cleanup(&mylist);
}