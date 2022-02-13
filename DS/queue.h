#ifndef _dalgo_queue
#define _dalgo_queue

#include <stdlib.h>
#include <stdio.h>


typedef struct
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
int queue_empty(Queue *q);
int queue_full(Queue *q);
int queue_en(Queue *q,int item);
int queue_de(Queue *q);
int queue_getitem(Queue *q);
void queue_print(Queue *q);

#endif