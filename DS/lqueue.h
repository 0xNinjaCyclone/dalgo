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

typedef struct
{
    QNode *rear;
    QNode *front;
    int counter;
} Queue;


Queue *lqueue_init();
int lqueue_size(Queue *q);
void lqueue_en(Queue *q,int item);
void lqueue_de(Queue *q);
int lqueue_empty(Queue *q);
int lqueue_getitem(Queue *q);
void lqueue_print(Queue *q);
void lqueue_cleanup(Queue **q);
void lqueue_oom();

#endif