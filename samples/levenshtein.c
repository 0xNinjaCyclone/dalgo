/*
    Levenshtein Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 5-12-2023
    Compile     => gcc -I../Algo/ ../Algo/helpers.c ../Algo/levenshtein.c levenshtein.c -o levenshtein
*/


#include "levenshtein.h"
#include "helpers.h"

int main()
{
    long lDistance;
    char cpStr1[] = "Book";
    char cpStr2[] = "Back";

    lDistance = levenshtein_distance(cpStr1, strlen(cpStr1), cpStr2, strlen(cpStr2), sizeof(char), CharCmpA);
    printf("Distance of '%s' and '%s' is %lu\n", cpStr1, cpStr2, lDistance);

    return 0;
}