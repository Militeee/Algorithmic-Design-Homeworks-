#ifndef __DIJKSTRA__
#define __DIJKSTRA__

#include <iostream>
#include <list>
#include <limits>
#include "graph.h"
#ifdef __cplusplus
extern "C"
{
#endif
    #include "heap.h"
    #include "utils.h"
#ifdef __cplusplus
}
#endif


void init_sssp(Graph& gr);
void relax(Graph& gr, int src, int dest, int weight);
void dijkstra(Graph& gr, int src);
void dijkstra_array(Graph& gr, int src);
void printPathAux(Graph gr, int dest);
void printPath(Graph gr, int dest, int src);

#endif //__DIJKSTRA__