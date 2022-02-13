/*
    Linked Stack Implementation

    Author      => Abdallah Mohamed Elsharif
    Date        => 12-12-2021
*/


#include "lstack.h"


void lstack_push(STACK **s,int item)
{
    STACK *temp = (STACK *) malloc(sizeof(STACK));

    if (temp) {
        if (lstack_empty(*s))   
            temp->counter = 0;

        else 
            temp->counter = (*s)->counter + 1;
        
        temp->value = item;
        temp->next = *s;
        (*s) = temp;
    } else {
        if (!lstack_empty(*s)) {
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

void lstack_pop(STACK **s)
{
    STACK *temp;

    if(!lstack_empty(*s))
    {
        temp = *s;
        (*s) = (*s)->next;
        temp->next = NULL;
        free(temp);
    }
}

int lstack_size(STACK *s) {
    return s->counter + 1;
}

int lstack_empty(STACK *s)
{
    return s == NULL;
}

int lstack_getitem(STACK *s)
{
    if (lstack_empty(s)) {
        fprintf(stderr,"Error Can't getitem, Linked Stack is empty");
        exit(EXIT_FAILURE);
    } else {
        return s->value;
    }
    
}

void lstack_print(STACK *s)
{
    STACK *temp = s;

    while (!lstack_empty(temp))
    {
        printf("Value %d => %d\n",temp->counter,lstack_getitem(temp));
        temp = temp->next;    
    }
    
}

void lstack_cleanup(STACK **s)
{
    while(!lstack_empty(*s))
    {
        lstack_pop(s);
    }

}
