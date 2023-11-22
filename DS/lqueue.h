#ifndef _dalgo_lqueue
#define _dalgo_lqueue

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct _QNode QNode;

struct _QNode
{
    QNode *next;
    void *data;
    int nSize;
    void *(* allocate)(size_t);
    void (* deallocate)(void *);
    void (* print)(void *);
};

typedef struct
{
    QNode *rear;
    QNode *front;
    size_t lSize;
} Queue;


Queue *lqueue_init();
size_t lqueue_size(Queue *q);
int lqueue_empty(Queue *q);
int lqueue_en(Queue *q, void *item, int nItemSize, void *(* allocate)(size_t), void (* deallocate)(void *), void (* print)(void *));
int lqueue_de(Queue *q);
void *lqueue_getitem(Queue *q);
void lqueue_cleanup(Queue **q);
void lqueue_print(Queue *q);


#endif