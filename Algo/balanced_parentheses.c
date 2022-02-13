/*
    Balanced Parentheses Implementation
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-2-2022
*/

#include "balanced_parentheses.h"

int symbol_open(char symbol)
{
    return (symbol == '{' || symbol == '[' || symbol == '(');
}

int symbol_close(char symbol)
{
    return (symbol == '}' || symbol == ']' || symbol == ')');
}

int symbols_eq(char symbol1, char symbol2)
{
    return (
        symbol1 == '{' && symbol2 == '}' ||
        symbol1 == '[' && symbol2 == ']' ||
        symbol1 == '(' && symbol2 == ')'
    );
}

int balanced(char *expression)
{
    STACK *container = NULL; /* This is not the best, because it uses int */

    for (size_t i = 0; i < strlen(expression); i++)
    {
        /* If this is a {,[,( */
        if (symbol_open(expression[i])) 
            /* Push it to the container */
            lstack_push(&container, expression[i]);

        /* If this is a },],) */
        else if (symbol_close(expression[i]))
        {
            /* If stack container not empty and the symbol in container is compatible with the symbol that closes it */
            if (!lstack_empty(container) && symbols_eq(lstack_getitem(container), expression[i]))
                lstack_pop(&container);

            else /* Not Balanced */
                return 0;
        }
    }

    /* If the container has items that means the expression not balanced because there open symbol without close */
    return lstack_empty(container);
    
}

