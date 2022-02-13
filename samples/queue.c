/*
    Queue Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-12-2021
    Compile     => gcc -I../DS/ ../DS/queue.c queue.c -o queue
*/

#include "queue.h"

int main(void)
{
    Queue *myqueue = queue_init(10);
    int value;

    while (1)
    {
        if (queue_full(myqueue))
        {
            printf("\nQueue is full !!\n\n");
            break;
        } else {
            printf("Enter a number value :");
            scanf("%d",&value);
            queue_en(myqueue,value);
        }

    }

    queue_print(myqueue);
    printf("\nFront value = %d, Size = %d\n",queue_getitem(myqueue),queue_size(myqueue));

    queue_cleanup(&myqueue); /* we had better call this func */
    return 0;
}