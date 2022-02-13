/*
    Linked Stack Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-12-2021
    Compile     => gcc -I../DS/ ../DS/lstack.c lstack.c -o lstack
*/

#include "lstack.h"

int main(void)
{
    STACK *mystack = NULL; /* We must set pointer to NULL */
    
    lstack_push(&mystack,5);
    lstack_pop(&mystack); /* Remove last item */
    lstack_push(&mystack,15);
    lstack_push(&mystack,5);
    lstack_push(&mystack,7);
    lstack_push(&mystack,9);
    lstack_push(&mystack,150);

    lstack_print(mystack);

    printf("\nTop item = %d, Size = %d\n",lstack_getitem(mystack),lstack_size(mystack));

    lstack_cleanup(&mystack); /* We had better call this func */

    return 0;
}