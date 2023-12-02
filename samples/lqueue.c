/*
    Linked Queue Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-12-2021
    Compile     => gcc -I../DS/ -I../Algo/ ../Algo/helpers.c ../DS/lqueue.c lqueue.c -o lqueue
*/


#include "lqueue.h"
#include "helpers.h"


int main(void)
{
    Queue *myqueue = lqueue_init(); /* Initiate Linked Queue */
    int value;

    value = 1;
    lqueue_en(myqueue, &value, sizeof(int), malloc, free, IntPrint);
    
    value = 21;
    lqueue_en(myqueue, &value, sizeof(int), malloc, free, IntPrint);
    
    value = 13;
    lqueue_en(myqueue, &value, sizeof(int), malloc, free, IntPrint);

    lqueue_de(myqueue); /* Remove first item */
    
    value = 14;
    lqueue_en(myqueue, &value, sizeof(int), malloc, free, IntPrint);

    lqueue_print(myqueue);
    printf("\nFront = %d, Rear = %d, Size = %d\n", *(int *) lqueue_getitem(myqueue),
                            *(int *) myqueue->rear->data, lqueue_size(myqueue));

    lqueue_cleanup( &myqueue ); /* We had better call this func */

    return 0;
}