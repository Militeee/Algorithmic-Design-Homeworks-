#ifndef __GRAPH__
#define __GRAPH__

#include <iostream>
#include <string>
#include <vector>
#include <limits>

// node struct for the graph
struct Node{
    int dest;
    int weight;
    Node(int d, int w): dest{d}, weight{w} {};
};

// class that implements a graph with an adjacency list

class Graph{
    // graph implemented as adjacency list and each attribute is a std::vector
    //  I've choosen to utilize a std::cointainer here mostly to simplify the 
    // memory management
    std::vector<std::string> color;
    std::vector<int> predecessors;
    std::vector<int> distance; 
    
    public:
    std::vector<std::vector<Node>> adj_list;
    std::string getColor(int node) { return color[node];}
    // return the ditsance of a specific node
    int getDist(int node) {return distance[node];}
    // return the predecessor of a specific node
    int getPred(int node) {return predecessors[node];}
    int getWeight(int node1, int node2);
    // return a reference to the whole distance vector
    std::vector<int>& getDists() {return distance;}
    // Nodes number
    int size() {return adj_list.size();}
    // return the edges of a node (actually only the final number of the pair (source,dest))
    std::vector<Node> getEdges(int node){return adj_list[node];}
    // get nodes reachable by an edge
    std::vector<int> getNeigh(int node);
    void addEdge(int src, int dest, int weight);
    void setColor(int node , std::string col) {color[node] = col; return;}
    void setPred(int node, int pred) {predecessors[node] = pred; return;}
    void setDist(int node, int dist) {distance[node] = dist; return;}

};

#endif //__GRAPH__