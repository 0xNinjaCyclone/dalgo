#ifndef _dalgo_stack
#define _dalgo_stack

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int maxsize;
    int top;
    int *values;
} STACK;


STACK *stack_init(int size);
void stack_cleanup(STACK **s);
int stack_size(STACK *s);
int stack_empty(STACK *s);
int stack_full(STACK *s);
int stack_push(STACK *s,int item);
int stack_pop(STACK *s);
int stack_getitem(STACK *s);
void stack_print(STACK *s);

#endif