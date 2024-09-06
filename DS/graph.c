/*
    Graph Implementation
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 01-09-2024
*/

#include "graph.h"

Graph *graph_init(GraphType type, int nItemSize, void *(* allocate)(size_t), void (* deallocate)(void *), void (* print)(void *), int (* compare)(void *, void *))
{
    Graph *g;

    if ( g = (Graph *) malloc(sizeof(Graph)) )
    {
        g->type = type;
        g->ulEdges = 0;
        g->nItemSize = nItemSize;
        g->allocate = allocate;
        g->deallocate = deallocate;
        g->print = print;
        g->compare = compare;

        if ( g->pAdjacencyList = llist_init() )
            return g;

        free( g );
    }

    return NULL;
}

size_t graph_vertcies(Graph *g)
{
    return ( g->pAdjacencyList ) ? llist_size( g->pAdjacencyList ) : 0;
}

size_t graph_edges(Graph *g)
{
    return g->ulEdges;
}

bool graph_insert(Graph *g, void *data)
{
    Vertex *pVertex;

    if ( pVertex = (Vertex *) malloc(sizeof(Vertex)) )
    {
        pVertex->ulIdx = llist_size( g->pAdjacencyList );
        pVertex->pEdge = NULL;
        pVertex->compare = g->compare;
        pVertex->deallocate = g->deallocate;
        pVertex->print = g->print;

        if ( pVertex->data = g->allocate(g->nItemSize) )
        {
            memcpy( pVertex->data, data, g->nItemSize );

            return (bool) llist_insert(
                g->pAdjacencyList,
                &pVertex,
                sizeof(Vertex *),
                malloc,
                vertex_free,
                NULL,
                vertex_compare
            );
        }

        free( pVertex );
    }

    return false;
}

bool graph_connected(Graph *g, Vertex *pFirstVertix, Vertex *pSecondVertix)
{
#ifdef USE_DALGO_STRUCTURES
    if ( pFirstVertix->pEdge )
        if ( ~llist_search((List *) pFirstVertix->pEdge, pSecondVertix->data, sizeof(Edge)) )
            return true;
#else
    for ( Edge *pEdge = (Edge *) pFirstVertix->pEdge; pEdge; pEdge = pEdge->pNextEdge )
        if ( edge_compare((void *) pEdge, pSecondVertix->data) == 0 )
            return true;
#endif

    return false;
}

bool graph_connect_w(Graph *g, Vertex *pFirstVertix, Vertex *pSecondVertix, size_t ulWeight)
{
    Edge edge = { 0 };
#ifndef USE_DALGO_STRUCTURES
    Edge *pEdge;
#endif

    if ( graph_connected(g, pFirstVertix, pSecondVertix) )
        return true;

    edge.pVertex = pSecondVertix;
    edge.ulWeight = ulWeight;
    
    if ( !pFirstVertix->pEdge )
    {
#ifdef USE_DALGO_STRUCTURES
        if ( !(pFirstVertix->pEdge = (void *) llist_init()) )
            return false;
#else
        if ( !(pFirstVertix->pEdge = malloc(sizeof(Edge))) ) 
            return false;
        
        memcpy( pFirstVertix->pEdge, &edge, sizeof(Edge) );
#endif
    }

#ifndef USE_DALGO_STRUCTURES
    else
    {
        for ( pEdge = (Edge *) pFirstVertix->pEdge; pEdge->pNextEdge; pEdge = pEdge->pNextEdge );

        if ( !(pEdge->pNextEdge = (Edge *) malloc(sizeof(Edge))) )
            return false;

        memcpy( pEdge->pNextEdge, &edge, sizeof(Edge) );
    }

    pFirstVertix->ulEdges++;
#else
    if ( !llist_insert(
        (List *) pFirstVertix->pEdge,
        &edge,
        sizeof(Edge),
        malloc,
        free,
        NULL,
        edge_compare
    ) )
        return false;

#endif
    
    g->ulEdges++;
        
    if ( g->type == DIRECTED )
        return true;

    else if ( g->type == UNDIRECTED )
        return graph_connect_w( g, pSecondVertix, pFirstVertix, ulWeight );

    return false;
}

bool graph_connectbyindexes_w(Graph *g, size_t ulFirstVertixIdx, size_t ulSecondVertixIdx, size_t ulWeight)
{
    Vertex *pFirstVertix, *pSecondVertix;

    if ( pFirstVertix = graph_getbyindex(g, ulFirstVertixIdx) )
        if ( pSecondVertix = graph_getbyindex(g, ulSecondVertixIdx) )
            return graph_connect_w( g, pFirstVertix, pSecondVertix, ulWeight );

    return false;
}

bool graph_connectbyvalues_w(Graph *g, void *pFirstVertixValue, void *pSecondVertixValue, size_t ulWeight)
{
    Vertex *pFirstVertix, *pSecondVertix;

    if ( pFirstVertix = graph_getbyvalue(g, pFirstVertixValue) )
        if ( pSecondVertix = graph_getbyvalue(g, pSecondVertixValue) )
            return graph_connect_w( g, pFirstVertix, pSecondVertix, ulWeight );

    return false;
}

bool graph_connect(Graph *g, Vertex *pFirstVertix, Vertex *pSecondVertix)
{
    return graph_connect_w( g, pFirstVertix, pSecondVertix, -1 );
}

bool graph_connectbyindexes(Graph *g, size_t ulFirstVertixIdx, size_t ulSecondVertixIdx)
{
    return graph_connectbyindexes_w( g, ulFirstVertixIdx, ulSecondVertixIdx, -1 );
}

bool graph_connectbyvalues(Graph *g, void *pFirstVertixValue, void *pSecondVertixValue)
{
    return graph_connectbyvalues_w( g, pFirstVertixValue, pSecondVertixValue, -1 );
}

Vertex *graph_getbyindex(Graph *g, size_t ulIdx)
{
    return ( ulIdx < graph_vertcies(g) ) ? *(Vertex **) llist_getitemAt(g->pAdjacencyList, ulIdx) : NULL;
}

Vertex *graph_getbyvalue(Graph *g, void *pValue)
{
    Vertex *pVertex;

    if ( ~llist_search2(g->pAdjacencyList, pValue, sizeof(Vertex *), (void **) &pVertex) )
        pVertex = *(Vertex **) pVertex;

    return pVertex;
}

void graph_print(Graph *g)
{
    Vertex *pVertex;
    Edge *pEdge;

    for ( size_t ulIdx = 0; ulIdx < graph_vertcies(g); ulIdx++ )
    {
        pVertex = graph_getbyindex(g, ulIdx);
        printf("(edges = %lu, data = ", vertex_edges(pVertex));
        g->print( pVertex->data );
        putchar(')');

        if ( pVertex->pEdge ) {
            printf(" => { ");
#ifdef USE_DALGO_STRUCTURES
            for ( size_t ulEdgeIdx = 0; ulEdgeIdx < llist_size((List *)pVertex->pEdge); ulEdgeIdx++ )
            {
                pEdge = (Edge *) llist_getitemAt( (List *)pVertex->pEdge, ulEdgeIdx );
                printf("(data = ");
                g->print( pEdge->pVertex->data );
                if ( ~pEdge->ulWeight )
                    printf(", weight = %lu", pEdge->ulWeight);
                putchar(')');

                if ( ulEdgeIdx != llist_size((List *)pVertex->pEdge)-1 )
                    printf(", ");
            }
#else
            pEdge = (Edge *) pVertex->pEdge;

            while ( pEdge )
            {
                printf("(data = ");
                g->print( pEdge->pVertex->data );
                if ( ~pEdge->ulWeight )
                    printf(", weight = %lu", pEdge->ulWeight);
                putchar(')');

                if ( pEdge = pEdge->pNextEdge )
                    printf(", ");
            }
#endif
            printf(" }");
        }

        putchar('\n');
    }
}

Tree *graph_bfs(Graph *g, size_t ulStart)
{
    Vertex *pVertex;
    TreeNode *pTreeNode, *pChild;
    void *pEdge;
    Tree *pSpanningTree = NULL;
    Queue *q = NULL;
    bool *pVisited = NULL;

    if ( graph_vertcies(g) == 0 )
        return NULL;

    if ( !(q = lqueue_init()) )
        goto LEAVE;

    if ( !(pVisited = (bool *) calloc(graph_vertcies(g), sizeof(bool))) )
        goto LEAVE;

    pSpanningTree = tree_init( sizeof(Vertex), malloc, free, vertex_print, NULL );

    if ( pSpanningTree ) {
        pVertex = graph_getbyindex( g, (~ulStart && ulStart < graph_vertcies(g)) ? ulStart : (size_t) rand() % graph_vertcies(g) );
        pTreeNode = tree_insert( pSpanningTree, NULL, pVertex );
        pVisited[ pVertex->ulIdx ] = true;

        if ( !lqueue_en(q, &pTreeNode, sizeof(TreeNode *), malloc, free, NULL) ) {
            tree_cleanup( &pSpanningTree );
            goto LEAVE;
        }

        while ( !lqueue_empty(q) ) {
            pTreeNode = *(TreeNode **) lqueue_getitem( q );
            pVertex = (Vertex *) pTreeNode->data;
            
            if ( pEdge = pVertex->pEdge ) {                
#ifdef USE_DALGO_STRUCTURES
                for ( size_t ulIdx = 0; ulIdx < llist_size((List *) pEdge); ulIdx++ ) {
                    pVertex = ( (Edge *) llist_getitemAt( (List *) pEdge, ulIdx ) )->pVertex;
#else
                for ( pEdge = pVertex->pEdge; pEdge; pEdge = (void *)( (Edge *) pEdge )->pNextEdge ) {
                    pVertex = ( (Edge *) pEdge )->pVertex;
#endif
                    if ( !pVisited[pVertex->ulIdx] ) {
                        pChild = tree_insert( pSpanningTree, pTreeNode, pVertex );
                        pVisited[ pVertex->ulIdx ] = true;
                        if ( !lqueue_en(q, &pChild, sizeof(TreeNode *), malloc, free, NULL) ) {
                            tree_cleanup( &pSpanningTree );
                            goto LEAVE;
                        }
                    }
                }
            }

            if ( !lqueue_de(q) ) {
                tree_cleanup( &pSpanningTree );
                break;
            }
        }
    }

LEAVE:
    if ( pVisited )
        free( pVisited );

    if ( q )
        lqueue_cleanup( &q );

    return pSpanningTree;
}

Tree *graph_dfs(Graph *g, size_t ulStart)
{
    Vertex *pVertex;
    TreeNode *pTreeNode, *pChild;
    void *pEdge;
    bool bNoWay;
    Tree *pSpanningTree = NULL;
    Stack *s = NULL;
    bool *pVisited = NULL;

    if ( graph_vertcies(g) == 0 )
        return NULL;

    if ( !(s = lstack_init()) )
        goto LEAVE;

    if ( !(pVisited = (bool *) calloc(graph_vertcies(g), sizeof(bool))) )
        goto LEAVE;

    pSpanningTree = tree_init( sizeof(Vertex), malloc, free, vertex_print, NULL );

    if ( pSpanningTree ) {
        pVertex = graph_getbyindex( g, (~ulStart && ulStart < graph_vertcies(g)) ? ulStart : (size_t) rand() % graph_vertcies(g) );
        pTreeNode = tree_insert( pSpanningTree, NULL, pVertex );
        pVisited[ pVertex->ulIdx ] = true;

        if ( !lstack_push(s, &pTreeNode, sizeof(TreeNode *), malloc, free, NULL) ) {
            tree_cleanup( &pSpanningTree );
            goto LEAVE;
        }

        while ( !lstack_empty(s) ) {
            pTreeNode = *(TreeNode **) lstack_getitem( s );
            pVertex = (Vertex *) pTreeNode->data;
            bNoWay = true;

            if ( pEdge = pVertex->pEdge ) {                
#ifdef USE_DALGO_STRUCTURES
                for ( size_t ulIdx = 0; ulIdx < llist_size((List *) pEdge); ulIdx++ ) {
                    pVertex = ( (Edge *) llist_getitemAt( (List *) pEdge, ulIdx ) )->pVertex;
#else
                for ( pEdge = pVertex->pEdge; pEdge; pEdge = (void *)( (Edge *) pEdge )->pNextEdge ) {
                    pVertex = ( (Edge *) pEdge )->pVertex;
#endif
                    if ( !pVisited[pVertex->ulIdx] ) {
                        pVisited[ pVertex->ulIdx ] = true;
                        pChild = tree_insert( pSpanningTree, pTreeNode, pVertex );
                        if ( !lstack_push(s, &pChild, sizeof(TreeNode *), malloc, free, NULL) ) {
                            tree_cleanup( &pSpanningTree );
                            goto LEAVE;
                        }

                        bNoWay = false;
                        break;
                    }
                }
            }

            if ( bNoWay ) {
                lstack_pop( s );                
            }
        }
    }

LEAVE:
    if ( pVisited )
        free( pVisited );

    if ( s )
        lstack_cleanup( &s );

    return pSpanningTree;
}

void graph_cleanup(Graph **g)
{
    llist_cleanup( &(*g)->pAdjacencyList );
    free( *g );
    ( *g ) = NULL;
}

int edge_compare(void *e, void *data)
{
    return vertex_compare( (void *) &((Edge *) e)->pVertex, data );
}

int vertex_compare(void *v, void *data)
{
    return ( *(Vertex **) v )->compare( (*(Vertex **) v)->data, data );
}

size_t vertex_edges(Vertex *pVertex)
{
#ifdef USE_DALGO_STRUCTURES
    return ( pVertex->pEdge ) ? llist_size((List *)pVertex->pEdge) : 0;
#else
    return pVertex->ulEdges;
#endif
}

void vertex_print(void *v)
{
    ( (Vertex *) v )->print( ( (Vertex *) v )->data );
}

void vertex_free(void *v)
{
#ifndef USE_DALGO_STRUCTURES
    Edge *pEdge, *pNext;
#endif

    if ( (*(Vertex **) v)->pEdge )
    {
#ifdef USE_DALGO_STRUCTURES
        llist_cleanup( (List **)&( *(Vertex **) v )->pEdge );
#else
        pEdge = (Edge *) ( *(Vertex **) v )->pEdge;
        
        while( pEdge )
        {
            pNext = pEdge->pNextEdge;
            free( pEdge );
            pEdge = pNext;
        }
#endif
    }

    ( *(Vertex **) v )->deallocate( ( *(Vertex **) v )->data );
    free( *(void **) v );
    free( v );
}