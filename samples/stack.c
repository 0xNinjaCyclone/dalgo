/*
    Stack Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-12-2021
    Compile     => gcc -I../DS/ ../DS/stack.c stack.c -o stack
*/

#include "stack.h"

int main() {

    STACK *mystack = stack_init(10);
    int value;
    
    while (1)
    {
        if (full(mystack))
        {
            printf("Stack is full !!\n");
            break;
        } else {
            printf("Enter a number value :");
            scanf("%d",&value);
            push(mystack,value);
        }
    }

    print_values(mystack);
    printf("\nTop item = %d, Top value = %d, Size = %d\n",
            getitem(mystack),mystack->top,stack_size(mystack));

    stack_cleanup(&mystack); /* we had better call this func */
    return 0;
}