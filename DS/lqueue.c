/*
    Linked Queue Implementation
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-12-2021
*/


#include "lqueue.h"

Queue *lqueue_init()
{
    Queue *q = (Queue *) malloc(sizeof(Queue));

    if (!q) 
        malloc_failed();

    return q;
}

int lqueue_size(Queue *q)
{
    return q->counter + 1;
}

int empty(Queue *q)
{
    return !q || !q->front;
}

void enqueue(Queue *q,int item)
{
    QNode *temp = (QNode *) malloc(sizeof(QNode));

    if (temp) {
        temp->value = item;
        temp->next = NULL;

        if (empty(q))
        {
            q->counter = 0;
            q->front = q->rear = temp;
        } else {
            q->counter++;
            
            /* Change rear position */
            q->rear = q->rear->next = temp;   
        }
    } else {
        lqueue_cleanup(&q);
        malloc_failed();
    }

}

void dequeue(Queue *q)
{
    QNode *temp;

    if (!empty(q))
    {
        temp = q->front;
        q->front = q->front->next;
        q->counter--;
        temp->next = NULL;
        free(temp);

        if (empty(q)) /* if Queue becomes empty */
        {
            /* Set rear value to null because last front and rear is same */
            q->rear = NULL;
        }
    }
}

void lqueue_cleanup(Queue **q)
{

    while ((*q)->front) /* free all nodes */
    {
        dequeue(*q);
    }

    /* free Queue handler after free all nodes */
    free(*q);

    /* Set ptr to null to avoid dangling */
    (*q) = NULL;
}

int getitem(Queue *q)
{
    if (!empty(q))
        return q->front->value;
    else {
        /* Error case */

        lqueue_cleanup(&q);
        fprintf(stderr,"Error Can't getitem, Queue is empty");
        exit(EXIT_FAILURE);
    }
}

void print_values(Queue *q)
{
    QNode *temp = q->front;

    for (size_t i = 0; i < lqueue_size(q); i++)
    {
        printf("Value %d => %d\n",i,temp->value);
        temp = temp->next;
    }
}

void malloc_failed()
{
    fprintf(stderr,"Failed in memory allocation");
    exit(EXIT_FAILURE);
}
