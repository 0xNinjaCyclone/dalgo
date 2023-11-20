/*
    Linked List Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-2-2022
    Compile     => gcc -I../DS/ ../DS/llist.c llist.c -o llist
*/

#include "llist.h"

void main(void)
{
    List *mylist = llist_init(); /* Initiate Linked List */
    int value, found;

    /* Append data to the end of the list */
    llist_insert(mylist, 10);
    llist_insert(mylist, 20);
    llist_insert(mylist, 30);
    llist_insert(mylist, 50);

    /* Append at the first of the list */
    llist_insertAtFirst(mylist, 5);

    /* Append at specified positions */
    llist_insertAt(mylist, 4, 40);
    llist_insertAt(mylist, 0, 0);

    /* Multiply the first 3 items by 10 */
    for (size_t i = 0; i < 3; i++)
        llist_updateAt(mylist, i, llist_getitemAt(mylist, i) * 10);
    
    /* Delete the last item */
    llist_delete(mylist);

    /* Delete the item in first */
    llist_deleteAtFirst(mylist);

    /* Delete the item in a specified position */
    llist_deleteAt(mylist, 2);

    puts("Print :");
    llist_print(mylist);

    puts("\nReverse list");
    llist_reverse(mylist);

    puts("Print again to show the changes :");
    llist_print(mylist);

    /* Print some data */
    printf("\nsize = %d, item(0) = %d\n", llist_size(mylist), llist_getitemAt(mylist, 0));

    /* Search in the list */
    value = 10; /* Find the position of this value */
    printf("\n(Search) Find the position of %d\n", value);

    if ((found = llist_search(mylist, value)) != -1)
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