/*
    Search Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 19-11-2023
    Compile     => gcc -I../Algo/ ../Algo/search.c ../Algo/helpers.c search.c -o search -lm
*/

#include "search.h"
#include "helpers.h"

#define ARRLENGTH 5

int main()
{
    int numbers[ARRLENGTH] = { 10, 20, 30, 40, 50 };
    char *programming_languages[ARRLENGTH] = { "C", "Go", "Ruby", "Assembly", "Ring" };
    int nIdx, n;

    n = 50;
    printf("Search for number %d (Double Linear Search)\n", n);
    nIdx = dbl_linear_search((void *)numbers, (void *)&n, ARRLENGTH, sizeof(int), IntCmp);

    if ( nIdx == -1 )
        printf("The number %d doesn't exist in the array\n", n);
    else 
        printf("The number %d found at %d index\n", n, nIdx);

    n = 60;
    printf("\nSearch for number %d (Binary Search)\n", n);
    nIdx = binary_search((void *)numbers, (void *)&n, ARRLENGTH, sizeof(int), IntCmp);

    if ( nIdx == -1 )
        printf("The number %d doesn't exist in the array\n", n);
    else 
        printf("The number %d found at %d index\n", n, nIdx);

    n = 30;
    printf("\nSearch for number %d (Jump Search)\n", n);
    nIdx = jump_search((void *)numbers, (void *)&n, ARRLENGTH, sizeof(int), IntCmp);

    if ( nIdx == -1 )
        printf("The number %d doesn't exist in the array\n", n);
    else 
        printf("The number %d found at %d index\n", n, nIdx);

    char langname[] = "Rust";
    printf("\nSearch for %s language (Linear Search)\n", langname);
    nIdx = linear_search((void *)programming_languages, (void *)langname, ARRLENGTH, sizeof(char *), StrPtrCmpA);

    if ( nIdx == -1 )
        printf("The %s language doesn't exist in the array\n", langname);
    else 
        printf("The %s language found at %d index\n", langname, nIdx);
    
    return 0;
}