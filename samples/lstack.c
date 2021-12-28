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
    
    push(&mystack,5);
    pop(&mystack); /* Remove last item */
    push(&mystack,15);
    push(&mystack,5);
    push(&mystack,7);
    push(&mystack,9);
    push(&mystack,150);

    print_values(mystack);

    printf("\nTop item = %d, Size = %d\n",getitem(mystack),lstack_size(mystack));

    lstack_cleanup(&mystack); /* We had better call this func */

    return 0;
}