/*
    Graph Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 02-09-2024
    Compile     => gcc -I../DS/ -I../Algo ../Algo/helpers.c ../DS/llist.c ../DS/lqueue.c ../DS/lstack.c ../DS/tree.c ../DS/graph.c graph.c -o graph
    Note        => Use '-DUSE_DALGO_STRUCTURES' to allow the graph to use the dalgo data structures
*/

#include "graph.h"
#include "helpers.h"

#define CHARLEN 10

int main(void)
{
    Tree *pSpanTree;
    Graph *pGraph;
    int nRet;
    char characters[CHARLEN] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };

    nRet = EXIT_FAILURE;
    pGraph = graph_init(UNDIRECTED, sizeof(char), malloc, free, CharPrintA, CharCmpA);

    if ( pGraph ) {
        for ( int i = 0; i < CHARLEN; i++ )
            graph_insert( pGraph, &characters[i] );
        
        for ( int i = 0; i < CHARLEN; i++ )
            for ( int j = i+1; j < CHARLEN + i; j += rand() % (CHARLEN / 2) )
                if ( !graph_connectbyindexes( pGraph, i, j % CHARLEN ) )
                {
                    printf(
                        "[~] Failed to connect vertex(%d:%c) with vertex(%d:%c)\n", 
                        i, 
                        characters[i], 
                        j % CHARLEN, 
                        characters[j % CHARLEN]
                    );
                    goto CLEANUP;
                }


        graph_print( pGraph );
        printf("Total (Vertcies = %lu, Edges = %lu)\n", graph_vertcies(pGraph), graph_edges(pGraph));
        pSpanTree = graph_bfs( pGraph, -1 );
        if ( pSpanTree ) {
            puts("BFS Spanning Tree :");
            tree_print( pSpanTree );
            tree_cleanup( &pSpanTree );
        }
        nRet = EXIT_SUCCESS;
CLEANUP:
        graph_cleanup( &pGraph );
    }

    return nRet;
}