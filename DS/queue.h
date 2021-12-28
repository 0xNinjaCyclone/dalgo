#ifndef _dalgo_queue
#define _dalgo_queue

#include <stdlib.h>
#include <stdio.h>


typedef struct QUEUE
{
    int maxsize;
    int rear;
    int front;
    int counter;
    int *values;
} Queue;


Queue *queue_init(int size);
void queue_cleanup(Queue **q);
int queue_size(Queue *q);
int empty(Queue *q);
int full(Queue *q);
int enqueue(Queue *q,int item);
int dequeue(Queue *q);
int getitem(Queue *q);
void print_values(Queue *q);

#endif