#ifndef _dalgo_stack
#define _dalgo_stack

#include <stdlib.h>
#include <stdio.h>

typedef struct stack
{
    int maxsize;
    int top;
    int *values;
} STACK;


STACK *stack_init(int size);
void stack_cleanup(STACK **s);
int stack_size(STACK *s);
int empty(STACK *s);
int full(STACK *s);
int push(STACK *s,int item);
int pop(STACK *s);
int getitem(STACK *s);
void print_values(STACK *s);

#endif