#ifndef _dalgo_stack
#define _dalgo_stack

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct
{
    size_t lMaxSize;
    size_t lTop;
    int nItemSize;
    unsigned char bEmpty;
    void *data;
} Stack;


Stack *stack_init(size_t lMaxSize, int nItemSize);
void stack_cleanup(Stack **s);
size_t stack_size(Stack *s);
int stack_empty(Stack *s);
int stack_full(Stack *s);
int stack_push(Stack *s, void *item);
int stack_pop(Stack *s);
void *stack_getitem(Stack *s);
void stack_print(Stack *s, void (* print)(void *));


#endif