/*
    Linked Queue Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-12-2021
    Compile     => gcc -I../DS/ ../DS/lqueue.c lqueue.c -o lqueue
*/


#include "lqueue.h"


int main(void)
{
    Queue *myqueue = lqueue_init(); /* Initiate Linked Queue */

    lqueue_en(myqueue,1);
    lqueue_en(myqueue,21);
    lqueue_en(myqueue,13);
    lqueue_de(myqueue); /* Remove first item */
    lqueue_en(myqueue,14);

    lqueue_print(myqueue);
    printf("\nFront = %d, Rear = %d, Size = %d\n",lqueue_getitem(myqueue),
                            myqueue->rear->value,lqueue_size(myqueue));

    lqueue_cleanup(&myqueue); /* We had better call this func */

    return 0;
}