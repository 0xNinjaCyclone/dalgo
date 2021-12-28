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

    enqueue(myqueue,1);
    enqueue(myqueue,21);
    enqueue(myqueue,13);
    dequeue(myqueue); /* Remove first item */
    enqueue(myqueue,14);

    print_values(myqueue);
    printf("\nFront = %d, Rear = %d, Size = %d\n",getitem(myqueue),
                            myqueue->rear->value,lqueue_size(myqueue));

    lqueue_cleanup(&myqueue); /* We had better call this func */

    return 0;
}