#ifndef __GRAPH__
#define __GRAPH__

#include <iostream>
#include <string>
#include <vector>
#include <limits>


int inf = std::numeric_limits<int>::max();

struct Node{
    int dest;
    int weight;
    Node(int d, int w): dest{d}, weight{w} {};
};


class Graph{
    
    std::vector<std::string> color;
    std::vector<int> predecessors;
    std::vector<int> distance; 
    
    public:
    std::vector<std::vector<Node*>> adj_list;
    std::string getColor(int node) { return color[node];}
    int getDist(int node) {return distance[node];}
    int getPred(int node) {return predecessors[node];}
    int getWeight(int node1, int node2);
    std::vector<int>& getDists() {return distance;}
    int size() {return adj_list.size();}
    std::vector<Node*> getEdges(int node){return adj_list[node];}
    std::vector<int> getNeigh(int node);
    void addEdge(int src, int dest, int weight);
    void setColor(int node , std::string col) {color[node] = col; return;}
    void setPred(int node, int pred) {predecessors[node] = pred; return;}
    void setDist(int node, int dist) {distance[node] = dist; return;}

};

#endif //__GRAPH__