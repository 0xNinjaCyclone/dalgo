#ifndef _dalgo_lstack
#define _dalgo_lstack


#include <stdlib.h>
#include <stdio.h>


typedef struct stack STACK;

struct stack
{
    STACK *next;
    int counter;
    int value;
};

void lstack_push(STACK **s,int item);
void lstack_pop(STACK **s);
int lstack_size(STACK *s);
int lstack_empty(STACK *s);
int lstack_getitem(STACK *s);
void lstack_print(STACK *s);
void lstack_cleanup(STACK **s);

#endif
