#ifndef _dalgo_graph
#define _dalgo_graph

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "llist.h"
#include "lqueue.h"
#include "lstack.h"
#include "tree.h"

typedef struct _Vertex Vertex;
typedef struct _Edge Edge;
typedef enum { DIRECTED, UNDIRECTED } GraphType;

struct _Edge {
    Vertex *pVertex;
    size_t ulWeight;
#if !defined(USE_DALGO_STRUCTURES)
    Edge *pNextEdge;
#endif
};

struct _Vertex {
    void *data;
    void *pEdge;
    size_t ulIdx;
#if !defined(USE_DALGO_STRUCTURES)  
    size_t ulEdges;
#endif
    void (* deallocate)(void *);
    void (* print)(void *);
    int (* compare)(void *, void *);
};

typedef struct {
    GraphType type;
    size_t ulEdges;
    List *pAdjacencyList;
    int nItemSize;
    void *(* allocate)(size_t);
    void (* deallocate)(void *);
    void (* print)(void *);
    int (* compare)(void *, void *);
} Graph;

Graph *graph_init(GraphType type, int nItemSize, void *(* allocate)(size_t), void (* deallocate)(void *), void (* print)(void *), int (* compare)(void *, void *));
size_t graph_vertcies(Graph *g);
size_t graph_edges(Graph *g);
bool graph_insert(Graph *g, void *data);
bool graph_connected(Graph *g, Vertex *pFirstVertix, Vertex *pSecondVertix);
bool graph_connect_w(Graph *g, Vertex *pFirstVertix, Vertex *pSecondVertix, size_t ulWeight);
bool graph_connectbyindexes_w(Graph *g, size_t ulFirstVertixIdx, size_t ulSecondVertixIdx, size_t ulWeight);
bool graph_connectbyvalues_w(Graph *g, void *pFirstVertixValue, void *pSecondVertixValue, size_t ulWeight);
bool graph_connect(Graph *g, Vertex *pFirstVertix, Vertex *pSecondVertix);
bool graph_connectbyindexes(Graph *g, size_t ulFirstVertixIdx, size_t ulSecondVertixIdx);
bool graph_connectbyvalues(Graph *g, void *pFirstVertixValue, void *pSecondVertixValue);
Vertex *graph_getbyindex(Graph *g, size_t ulIdx);
Vertex *graph_getbyvalue(Graph *g, void *pValue);
void graph_print(Graph *g);
Tree *graph_bfs(Graph *g, size_t ulStart);
Tree *graph_dfs(Graph *g, size_t ulStart);
void graph_cleanup(Graph **g);

int edge_compare(void *e, void *data);
int vertex_compare(void *v, void *data);
size_t vertex_edges(Vertex *pVertex);
void vertex_print(void *v);
void vertex_free(void *v);

#endif