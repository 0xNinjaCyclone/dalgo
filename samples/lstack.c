/*
    Linked Stack Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-12-2021
    Compile     => gcc -I../DS/ ../DS/lstack.c lstack.c -o lstack
*/

#include "lstack.h"

void print(void *data) { printf("%d", *(int *)data); }

int main(void)
{
    Stack *mystack;
    int value;
    
    mystack = lstack_init();

    value = 5;
    lstack_push(mystack, &value, sizeof(int), malloc, free, print);
    lstack_pop(mystack); /* Remove last item */

    value = 15;
    lstack_push(mystack, &value, sizeof(int), malloc, free, print);

    value = 5;
    lstack_push(mystack, &value, sizeof(int), malloc, free, print);

    value = 7;
    lstack_push(mystack, &value, sizeof(int), malloc, free, print);

    value = 9;
    lstack_push(mystack, &value, sizeof(int), malloc, free, print);


    value = 150;
    lstack_push(mystack, &value, sizeof(int), malloc, free, print);

    lstack_print(mystack);

    printf("\nTop item = %d, Size = %d\n", *(int *)lstack_getitem(mystack), lstack_size(mystack));

    lstack_cleanup(&mystack); /* We had better call this func */

    return 0;
}