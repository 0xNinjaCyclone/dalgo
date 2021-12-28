#ifndef _dalgo_lqueue
#define _dalgo_lqueue

#include <stdlib.h>
#include <stdio.h>


typedef struct Node QNode;

struct Node
{
    QNode *next;
    int value;
};

typedef struct QUEUE
{
    QNode *rear;
    QNode *front;
    int counter;
} Queue;


Queue *lqueue_init();
int lqueue_size(Queue *q);
void enqueue(Queue *q,int item);
void dequeue(Queue *q);
int empty(Queue *q);
int getitem(Queue *q);
void print_values(Queue *q);
void lqueue_cleanup(Queue **q);
void malloc_failed();

#endif