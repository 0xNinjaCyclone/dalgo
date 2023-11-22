/*
    Linked Stack Implementation

    Author      => Abdallah Mohamed Elsharif
    Date        => 12-12-2021
*/


#include "lstack.h"

Stack *lstack_init()
{
    Stack *s;

    if ( s = (Stack *) malloc( sizeof(Stack) ) )
    {
        s->lSize = 0;
        s->top = NULL;
        return s;
    }

    return NULL;
}

int lstack_push(Stack *s, void *item, int nItemSize, void *(* allocate)(size_t), void (* deallocate)(void *), void (* print)(void *))
{
    StackNode *node;

    if ( !(node = malloc( sizeof(StackNode) )) )
        return 0;

    node->nSize = nItemSize;
    node->allocate = allocate;
    node->deallocate = deallocate;
    node->print = print;
    node->data = node->allocate(nItemSize);

    if ( !node->data )
        return 0;

    memcpy( node->data, item, nItemSize );
    node->next = s->top;
    s->top = node;
    s->lSize++;

    return 1;
}

int lstack_pop(Stack *s)
{
    StackNode *node;

    if ( lstack_empty(s) )
        return 0;

    node = s->top;
    s->top = s->top->next;
    node->next = NULL;
    node->deallocate( node->data );
    free( node );
    s->lSize--;

    return 1;
}

size_t lstack_size(Stack *s)
{
    return s->lSize;
}

int lstack_empty(Stack *s)
{
    return s->lSize == 0;
}

void *lstack_getitem(Stack *s)
{
    return s->top->data;
}

void lstack_print(Stack *s)
{
    StackNode *node;
    size_t lSize;

    node = s->top;
    lSize = lstack_size(s);

    if ( !lstack_empty(s) ) 
        do {
            for (size_t i = 0; i < lSize; i++) printf("-");
            printf("> ");
            node->print( node->data );
            puts("");
            lSize--;
        } while( node = node->next );
}

void lstack_cleanup(Stack **s)
{
    while ( !lstack_empty( *s ) )
        lstack_pop( *s );

    free( *s );
    ( *s ) = NULL;
}
