/*
    Stack Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-12-2021
    Compile     => gcc -I../DS/ -I../Algo/ ../Algo/helpers.c  ../DS/stack.c stack.c -o stack
*/

#include "stack.h"
#include "helpers.h"


int main() {

    Stack *mystack = stack_init(10, sizeof(int));
    int value;
    
    while ( 1 )
    {
        if ( stack_full(mystack) )
        {
            printf("\nStack is full !!\n\n");
            break;
        } else {
            printf("Enter a number value :");
            scanf("%d", &value);
            stack_push(mystack, &value);
        }
    }

    stack_print(mystack, IntPrint);
    printf("\nTop item = %d, Top value = %d, Size = %d\n",
            *(int *)stack_getitem(mystack), mystack->lTop, stack_size(mystack));

    stack_cleanup(&mystack); /* we had better call this func */
    return 0;
}