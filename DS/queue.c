/*
    Queue Implementation
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-12-2021
*/

#include "queue.h"


Queue *queue_init(size_t lMaxSize, int nItemSize)
{
    /* return initiated queue address */

    Queue *q = (Queue *) malloc( sizeof(Queue) );

    if ( q ) {
        q->lFront = q->lCtr = 0;
        q->lRear = -1;
        q->lMaxSize = lMaxSize;
        q->nItemSize = nItemSize;
        q->data = malloc( q->nItemSize * q->lMaxSize );

        if ( q->data ) 
            return q;
         
        /* Free queue handler if data alloc failed */
        free(q);

    } 
    
    return NULL;
}

void queue_cleanup(Queue **q)
{
    free( (*q)->data );
    free( *q );
    *q = NULL; /* Set ptr to null to avoid dangling */
}

size_t queue_size(Queue *q)
{
    return q->lCtr;
}

int queue_empty(Queue *q)
{
    return !q || queue_size(q) == 0;
}

int queue_full(Queue *q)
{
    return queue_size(q) == q->lMaxSize;
}

int queue_en(Queue *q, void *item)
{
    /* return 1 if success else return 0 */
    
    if ( queue_full(q) )
        return 0;

    
    q->lCtr++;
    memcpy( (void *)((__SIZE_TYPE__) q->data + (++q->lRear) * q->nItemSize), item, q->nItemSize );
    
    return 1;   
}

int queue_de(Queue *q)
{
    /* return 1 if succeed else return 0 */
    
    if ( queue_empty(q) )
        return 0;
    
    q->lCtr--;
    q->lFront++;

    return 1;
}

void *queue_getitem(Queue *q)
{
    if ( queue_empty(q) )
        return NULL;
    
    return (void *)((__SIZE_TYPE__) q->data + q->lFront * q->nItemSize);
}

void queue_print(Queue *q, void (* print)(void *))
{
    for (size_t i = 0; i < queue_size(q); i++)
    {
        for (size_t j = 0; j <= i; j++) printf("-");
        printf("> ");
        //printf("Value %d => %d\n",i,q->values[i + q->front]);
        print( (void *)((__SIZE_TYPE__) q->data + (q->lFront + i) * q->nItemSize) );
        puts("");
    }   
}

