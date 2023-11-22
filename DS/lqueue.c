/*
    Linked Queue Implementation
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-12-2021
*/


#include "lqueue.h"

Queue *lqueue_init()
{
    Queue *q;

    if ( q = malloc( sizeof(Queue) ) )
    {
        q->lSize = 0;
        q->front = q->rear = NULL;
        return q;
    }

    return NULL;
}

size_t lqueue_size(Queue *q)
{
    return q->lSize;
}

int lqueue_empty(Queue *q)
{
    return !q->front;
}

int lqueue_en(Queue *q, void *item, int nItemSize, void *(* allocate)(size_t), void (* deallocate)(void *), void (* print)(void *))
{
    QNode *node;

    if ( node = malloc( sizeof(QNode) ) )
    {
        node->allocate = allocate;
        node->deallocate = deallocate;
        node->print = print;
        node->nSize = nItemSize;
        node->data = node->allocate( node->nSize );
        node->next = NULL;

        if ( !node->data )
            return 0;

        memcpy( node->data, item, node->nSize );

        if ( lqueue_empty(q) )
            q->front = q->rear = node;

        else
            q->rear = q->rear->next = node;

        q->lSize++;

        return 1;
    }

    return 0;
}

int lqueue_de(Queue *q)
{
    QNode *node;

    if ( lqueue_empty(q) )
        return 0;

    node = q->front;
    q->front = q->front->next;
    node->next = NULL;
    node->deallocate( node->data );
    free( node );
    q->lSize--;

    /* if the Queue becomes empty, Set rear to NULL, because last front and rear are same */
    if ( lqueue_empty(q) ) 
        q->rear = NULL;

    return 1;
}

void *lqueue_getitem(Queue *q)
{
    if ( lqueue_empty(q) )
        return NULL;

    return q->front->data;
}

void lqueue_cleanup(Queue **q)
{
    while ( !lqueue_empty( *q ) )
        lqueue_de( *q );

    free( *q );
    ( *q ) = NULL;
}

void lqueue_print(Queue *q)
{
    QNode *node;
    size_t lCtr;

    if ( !lqueue_empty(q) )
    {
        node = q->front;
        lCtr = 1;

        do {
            for (size_t i = 0; i < lCtr; i++) printf("-");
            printf( "> " );
            node->print( node->data );
            puts("");
            lCtr++;
        } while( node = node->next );
    }
}

