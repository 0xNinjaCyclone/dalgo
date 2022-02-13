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
            /* Free queue handler if malloc values failed */

            free(q);
            goto OOM;
        }
    } else {
        goto OOM;
    }
    

    OOM :
        fprintf(stderr,"Out Of Memory");
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

int queue_empty(Queue *q)
{
    return !q || queue_size(q) == 0;
}

int queue_full(Queue *q)
{
    return queue_size(q) == q->maxsize;
}

int queue_en(Queue *q,int item)
{
    /* return 1 if success else return 0 */
    
    if (queue_full(q))
        return 0;

    else {
        q->counter++;
        q->values[++q->rear] = item;
        
        return 1;
    }
}

int queue_de(Queue *q)
{
    /* return 1 if succeed else return 0 */
    
    if (queue_empty(q))
        return 0;
    
    else {
        q->counter--;
        q->front++;

        return 1;
    }
}

int queue_getitem(Queue *q)
{
    if (!queue_empty(q))
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

void queue_print(Queue *q)
{
    for (int i = 0; i < queue_size(q); i++)
    {
        printf("Value %d => %d\n",i,q->values[i + q->front]);
    }   
}