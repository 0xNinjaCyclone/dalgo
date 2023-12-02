/*
    Linked List Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-2-2022
    Compile     => gcc -I../DS/ -I../Algo ../Algo/helpers.c ../DS/llist.c llist.c -o llist
*/

#include "llist.h"
#include "helpers.h"


void main(void)
{
    List *mylist = llist_init(); /* Initiate Linked List */
    int value, found;

    /* Append data to the end of the list */
    value = 10;
    llist_insert(mylist, &value, sizeof(int), malloc, free, IntPrint, IntCmp);

    value = 20;
    llist_insert(mylist, &value, sizeof(int), malloc, free, IntPrint, IntCmp);

    value = 30;
    llist_insert(mylist, &value, sizeof(int), malloc, free, IntPrint, IntCmp);

    value = 50;
    llist_insert(mylist, &value, sizeof(int), malloc, free, IntPrint, IntCmp);

    /* Append at the first of the list */
    value = 5;
    llist_insert(mylist, &value, sizeof(int), malloc, free, IntPrint, IntCmp);

    /* Append at specified positions */
    value = 4;

    llist_insertAt(mylist, 4, &value, sizeof(int), malloc, free, IntPrint, IntCmp);

    value = 0;
    llist_insertAt(mylist, 4, &value, sizeof(int), malloc, free, IntPrint, IntCmp);

    /* Multiply the first 3 items by 10 */
    for (size_t i = 0; i < 3; i++)
    {
        value = *(int *)(llist_getitemAt(mylist, i)) * 10;
        llist_updateAt(mylist, i, &value);
    }

    /* Delete the last item */
    llist_delete(mylist);

    /* Delete the item in first */
    llist_deleteAtFirst(mylist);

    /* Delete the item in a specified position */
    llist_deleteAt(mylist, 2);

    /* Add string item */
    char name[] = "Abdallah";
    llist_insertAtFirst(mylist, name, strlen(name) + 1, malloc, free, StrPrintA, StrCmpA);

    puts("Print :");
    llist_print(mylist);

    puts("\nReverse list");
    llist_reverse(mylist);

    puts("Print again to show the changes :");
    llist_print(mylist);

    /* Print some data */
    printf("\nsize = %d, item(0) = %d\n", llist_size(mylist), *(int *)llist_getitemAt(mylist, 0));

    /* Search in the list */
    value = 100; /* Find the position of this value */
    printf("\n(Search) Find the position of %d\n", value);

    if ((found = llist_search(mylist, &value, sizeof(int))) != -1)
        printf("The position of %d is %d\n", value, found);

    else
        printf("Value %d does not exist in the list\n", value);

    puts("\nClear List");
    llist_clear(mylist);

    /* Check if the list cleared or not */
    puts(llist_empty(mylist) ? "Cleared successfully" : "Not cleared");

    /* We had better call this func after finsh to free memory */
    llist_cleanup(&mylist);
}