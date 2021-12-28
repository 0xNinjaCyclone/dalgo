/*
    Fibonacci Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 26-12-2021
    Compile     => gcc -I../Algo/ ../Algo/fib.c fib.c -o fib
*/

#include <stdio.h>
#include <time.h>
#include "fib.h"


void calculate_time(long (*func)(int),int p) /* Will take function address and parameter of that function */
{
    clock_t start , end;
    start = clock();
    printf("func value = %ld\n",(*func)(p)); /* Call the function which passed as a parameter */
    end = clock();
    printf("Total Time = %f\n",(end - start) / (double) CLOCKS_PER_SEC);
}

int main(void)
{
    printf("Linear :\n");
    calculate_time(linear_fib,45);
    printf("\nRecursive :\n");
    calculate_time(recursive_fib,45);
    return 0;
}