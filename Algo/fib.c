/*
    Fibonacci Implementation
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 26-12-2021
*/

#include "fib.h"

long recursive_fib(int n)
{
    if ( n <= 1)
        return n;

    return recursive_fib(n - 1) + recursive_fib(n - 2);
}

long linear_fib(int n)
{
    long sum = 0, prevPrevious = 0 , previous = 1;

    for (size_t i = 0; i <= n; i++)
    {
        if (i <= 1)
            sum = i;
        else {
            sum = prevPrevious + previous;
            prevPrevious = previous;
            previous = sum;
        }
    }

    return sum;
}
