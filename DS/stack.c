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
            /* Free handler */
            free(s);

            goto OOM;
        }
    } else {
        goto OOM;
    }

    OOM :
        fprintf(stderr,"Out Of Memory");
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

int stack_empty(STACK *s)
{
    return s->top == -1;
}

int stack_full(STACK *s)
{
    return s->top >= (s->maxsize - 1);
}

int stack_push(STACK *s,int item)
{
    if(stack_full(s))
        return 0;

    else {
        s->values[++s->top] = item;
        return 1;
    } 
}

int stack_pop(STACK *s)
{
    if(stack_empty(s))
        return 0;
    
    else {
        s->top--;
        return 1;
    }
}

int stack_getitem(STACK *s)
{
    if (!stack_empty(s))
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

void stack_print(STACK *s)
{
    int temp = s->top;

    while (!stack_empty(s))
    {
        printf("Value %d => %d\n",s->top,s->values[s->top]);
        s->top--;
    }
    
    s->top = temp;
}