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

void push(STACK **s,int item);
void pop(STACK **s);
int lstack_size(STACK *s);
int empty(STACK *s);
int getitem(STACK *s);
void print_values(STACK *s);
void lstack_cleanup(STACK **s);

#endif
