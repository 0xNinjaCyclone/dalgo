#ifndef _dalgo_lstack
#define _dalgo_lstack


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _StackNode StackNode;

struct _StackNode 
{
    StackNode *next;
    void *data;
    int nSize;
    void *(* allocate)(size_t);
    void (* deallocate)(void *);
    void (* print)(void *);
};

typedef struct
{
    StackNode *top;
    size_t lSize;
} Stack;


Stack *lstack_init();
int lstack_push(Stack *s, void *item, int nItemSize, void *(* allocate)(size_t), void (* deallocate)(void *), void (* print)(void *));
int lstack_pop(Stack *s);
size_t lstack_size(Stack *s);
int lstack_empty(Stack *s);
void *lstack_getitem(Stack *s);
void lstack_print(Stack *s);
void lstack_cleanup(Stack **s);


#endif
