/*
    Queue Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-12-2021
    Compile     => gcc -I../DS/ -I../Algo/ ../Algo/helpers.c ../DS/queue.c queue.c -o queue
*/

#include "queue.h"
#include "helpers.h"


int main(void)
{
    Queue *myqueue = queue_init(10, sizeof(int));
    int value;

    while ( 1 )
    {
        if ( queue_full(myqueue) )
        {
            printf("\nQueue is full !!\n\n");
            break;
        } else {
            printf("Enter a number value :");
            scanf("%d", &value);
            queue_en(myqueue, &value);
        }

    }

    queue_print(myqueue, IntPrint);
    printf("\nFront value = %d, Size = %d\n", *(int *) queue_getitem(myqueue), queue_size(myqueue));

    queue_cleanup(&myqueue); /* we had better call this func */
    return 0;
}