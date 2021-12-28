/*
    Queue Implementation
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-12-2021
*/

#include "queue.h"


Queue *queue_init(int size)
{
    /* return initiated queue address */

    Queue *q = (Queue *) malloc(sizeof(Queue));

    if (q) {
        q->front = q->counter = 0;
        q->rear = -1;
        q->maxsize = size;
        q->values = (int *) malloc(sizeof(int) * q->maxsize);

        if (q->values) {
            return q;
        } else {
            /* free queue handler if malloc values failed */

            free(q);
            q = NULL;
            goto BADMEMALLOC;
        }
    } else {
        goto BADMEMALLOC;
    }
    

    BADMEMALLOC :
        fprintf(stderr,"Failed in memory allocation");
        exit(EXIT_FAILURE);
}

void queue_cleanup(Queue **q)
{
    free((*q)->values);
    free(*q);
    *q = NULL; /* Set ptr to null to avoid dangling */
}

int queue_size(Queue *q)
{
    return q->counter;
}

int empty(Queue *q)
{
    return queue_size(q) == 0;
}

int full(Queue *q)
{
    return queue_size(q) == q->maxsize;
}

int enqueue(Queue *q,int item)
{
    /* return 1 if success else return 0 */
    
    if (full(q))
        return 0;

    else {
        q->counter++;
        return ((q->values[++q->rear] = item) % 1) + 1; /* return 1 */
    }
}

int dequeue(Queue *q)
{
    /* return 1 if succeed else return 0 */
    
    if (empty(q))
        return 0;
    
    else {
        q->counter--;
        return (q->front++ % 1) + 1; /* return 1 */
    }
}

int getitem(Queue *q)
{
    if (!empty(q))
        return q->values[q->front];

    else {
        /* Error case */

        if(q) {
            /* handler is initiated, we must cleanup */
            
            queue_cleanup(&q);
        }

        fprintf(stderr,"Queue is empty");
        exit(EXIT_FAILURE);
    }
}

void print_values(Queue *q)
{
    for (int i = 0; i < queue_size(q); i++)
    {
        printf("Value %d => %d\n",i,q->values[i + q->front]);
    }   
}