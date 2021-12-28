/*
    Linked Stack Implementation

    Author      => Abdallah Mohamed Elsharif
    Date        => 12-12-2021
*/


#include "lstack.h"


void push(STACK **s,int item)
{
    STACK *temp = (STACK *) malloc(sizeof(STACK));

    if (temp) {
        if (empty(*s))   
            temp->counter = 0;

        else 
            temp->counter = (*s)->counter + 1;
        
        temp->value = item;
        temp->next = *s;
        (*s) = temp;
    } else {
        if (!empty(*s)) {
            /* stack initiated before, we must call cleanup func */

            lstack_cleanup(s);
            goto BADMEMALLOC;

        } else {
            goto BADMEMALLOC;
        }

        BADMEMALLOC :
            fprintf(stderr,"Failed in memory allocation");
            exit(EXIT_FAILURE);
    }

}

void pop(STACK **s)
{
    STACK *temp;

    if(!empty(*s))
    {
        temp = *s;
        (*s) = (*s)->next;
        temp->next = NULL;
        free(temp);
    }
}

int lstack_size(STACK *s) {
    //printf("%p\n",s);
    return s->counter + 1;
}

int empty(STACK *s)
{
    return s == NULL;
}

int getitem(STACK *s)
{
    if (empty(s)) {
        fprintf(stderr,"Error Can't getitem, Linked Stack is empty");
        exit(EXIT_FAILURE);
    } else {
        return s->value;
    }
    
}

void print_values(STACK *s)
{
    STACK *temp = s;

    while (!empty(temp))
    {
        printf("Value %d => %d\n",temp->counter,getitem(temp));
        temp = temp->next;    
    }
    
}

void lstack_cleanup(STACK **s)
{
    while(!empty(*s))
    {
        pop(s);
    }

}
