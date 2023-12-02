/*
    Linked Stack Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-12-2021
    Compile     => gcc -I../DS/ -I../Algo/ ../Algo/helpers.c ../DS/lstack.c lstack.c -o lstack
*/

#include "lstack.h"
#include "helpers.h"


int main(void)
{
    Stack *mystack;
    int value;
    
    mystack = lstack_init();

    value = 5;
    lstack_push(mystack, &value, sizeof(int), malloc, free, IntPrint);
    lstack_pop(mystack); /* Remove last item */

    value = 15;
    lstack_push(mystack, &value, sizeof(int), malloc, free, IntPrint);

    value = 5;
    lstack_push(mystack, &value, sizeof(int), malloc, free, IntPrint);

    value = 7;
    lstack_push(mystack, &value, sizeof(int), malloc, free, IntPrint);

    value = 9;
    lstack_push(mystack, &value, sizeof(int), malloc, free, IntPrint);


    value = 150;
    lstack_push(mystack, &value, sizeof(int), malloc, free, IntPrint);

    lstack_print(mystack);

    printf("\nTop item = %d, Size = %d\n", *(int *)lstack_getitem(mystack), lstack_size(mystack));

    lstack_cleanup(&mystack); /* We had better call this func */

    return 0;
}