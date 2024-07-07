/*
    Json parser Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 06-07-2024
    Compile     => gcc -I../DS/ -I../Algo/ ../Algo/helpers.c ../DS/llist.c ../DS/hash.c ../Algo/json.c json_parse.c -o json_parse
    Note        => Use '-DUSE_DALGO_STRUCTURES' to allow the parser to use the dalgo data structures
*/

#include "json.h"

int main(int argc, char **argv)
{
    Json *pJson;
    int nRet;

    if ( argc < 2 )
        return puts("Usage :\n\t./json_parse <input.json>");

    nRet = EXIT_FAILURE;

    if ( pJson = json_init() ) {
        if ( json_parsefile(pJson, argv[1]) ) {
            json_print( pJson );
            nRet = EXIT_SUCCESS;
        } else {
            printf("[!] Failed to parse '%s'\n", argv[1]);
        }

        json_destroy( &pJson );
    }

    return nRet;
}