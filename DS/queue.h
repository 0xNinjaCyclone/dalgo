#ifndef _dalgo_queue
#define _dalgo_queue

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct
{
    size_t lMaxSize;
    size_t lRear;
    size_t lFront;
    size_t lCtr;
    int nItemSize;
    void *data;
} Queue;

Queue *queue_init(size_t lMaxSize, int nItemSize);
void queue_cleanup(Queue **q);
size_t queue_size(Queue *q);
int queue_empty(Queue *q);
int queue_full(Queue *q);
int queue_en(Queue *q, void *item);
int queue_de(Queue *q);
void *queue_getitem(Queue *q);
void queue_print(Queue *q, void (* print)(void *));


#endif