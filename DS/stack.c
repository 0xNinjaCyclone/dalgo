/*
    Stack Implementation
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-12-2021
*/

#include "stack.h"

STACK *stack_init(int size) {
    /* return initiated stack address */

    STACK *s = (STACK *) malloc(sizeof(STACK));
    
    if (s) {
        s->top = -1;
        s->maxsize = size;
        s->values = (int *) malloc(sizeof(int) * s->maxsize);

        if (s->values) {
            return s;
        } else {
            goto BADMEMALLOC;
        }
    } else {
        goto BADMEMALLOC;
    }

    BADMEMALLOC :
        fprintf(stderr,"Failed in memory allocation");
        exit(EXIT_FAILURE);
}

void stack_cleanup(STACK **s)
{
    free((*s)->values);
    free(*s);

    /* Set ptr to null to avoid dangling */
    *s = NULL;
}

int stack_size(STACK *s)
{
    return s->top + 1;
}

int empty(STACK *s)
{
    return s->top == -1;
}

int full(STACK *s)
{
    return s->top >= (s->maxsize - 1);
}

int push(STACK *s,int item)
{
    if(full(s))
        return 0;

    else 
        return ((s->values[++s->top] = item) % 1) + 1; /* return 1 */
}

int pop(STACK *s)
{
    if(empty(s))
        return 0;
    
    else
        return (s->top-- % 1) + 1; /* return 1 */
}

int getitem(STACK *s)
{
    if (!empty(s))
        return s->values[s->top];

    else {
        /* Error case */

        if (s) {
            /* handler is initiated, we must cleanup */
            stack_cleanup(&s);
        }

        fprintf(stderr,"Stack is empty");
        exit(EXIT_FAILURE);
    }
}

void print_values(STACK *s)
{
    int temp = s->top;

    while (!empty(s))
    {
        printf("Value %d => %d\n",s->top,s->values[s->top]);
        s->top--;
    }
    
    s->top = temp;
}