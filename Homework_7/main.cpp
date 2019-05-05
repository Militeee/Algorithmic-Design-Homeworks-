#include <iostream>
#include "graph.h"
#include "dijkstra.h"

int main(){

    Graph gp{};
    gp.addEdge(0,1,1);
    gp.addEdge(0,2,5);
    gp.addEdge(1,5,15);
    gp.addEdge(2,3,2);
    gp.addEdge(3,4,1);
    gp.addEdge(4,5,3);

    dijkstra(gp,0);
    for(int i = 1; i < gp.size(); i++)
        printPath(gp, i,0);
}
