/*
    Balanced Parentheses Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-2-2022
    Compile     => gcc -I../DS/ -I../Algo/ ../DS/lstack.c ../Algo/balanced_parentheses.c balanced_parentheses.c -o balanced_parentheses
*/

#include "balanced_parentheses.h"

void main(void)
{
    char expression[100];
    printf("Enter your expression ex '5*(2/{4-1*10})-2+[5+10/3]': ");
    scanf("%s", &expression);
    printf("\nexpression '%s' is %s\n", expression, balanced(expression) ? "Balanced" : "Not Balanced");
}