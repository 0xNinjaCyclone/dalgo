/*
    Stack Implementation
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-12-2021
*/

#include "stack.h"

Stack *stack_init(size_t lMaxSize, int nItemSize) {
    /* return initiated stack address */

    Stack *s = (Stack *) malloc( sizeof(Stack) );
    
    if ( s ) {
        s->lTop = -1;
        s->lMaxSize = lMaxSize;
        s->nItemSize = nItemSize;
        s->bEmpty = 1;
        s->data = malloc( s->nItemSize * s->lMaxSize);

        if ( s->data ) 
            return s;
        
        /* Free handler */
        free( s );

    } 

    return NULL;
}

void stack_cleanup(Stack **s)
{
    free( (*s)->data );
    free( *s );

    /* Set ptr to null to avoid dangling */
    *s = NULL;
}

size_t stack_size(Stack *s)
{
    return s->lTop + 1;
}

int stack_empty(Stack *s)
{
    return !s || s->bEmpty;
}

int stack_full(Stack *s)
{
    return !stack_empty(s) && s->lTop == (s->lMaxSize - 1);
}

int stack_push(Stack *s, void *item)
{
    if( stack_full(s) )
        return 0;

    memcpy( (void *)((__SIZE_TYPE__) s->data + (++s->lTop) * s->nItemSize), item, s->nItemSize );
    s->bEmpty = 0;
    return 1;
    
}

int stack_pop(Stack *s)
{
    if( stack_empty(s) )
        return 0;
    
    
    s->bEmpty = ( s->lTop-- == 0 );
    return 1;
    
}

void *stack_getitem(Stack *s)
{
    if ( stack_empty(s) )
        return NULL;

    return (void *)((__SIZE_TYPE__) s->data + s->lTop * s->nItemSize);
}

void stack_print(Stack *s, void (* print)(void *))
{
    size_t temp = s->lTop;

    while ( s->lTop != -1 )
    {
        for (size_t i = 0; i <= s->lTop && s->lTop != -1; i++) printf("-");
        printf("> ");
        print( (void *)((__SIZE_TYPE__) s->data + s->lTop * s->nItemSize) );
        puts("");
        s->lTop--;
    }
    
    s->lTop = temp;
}
