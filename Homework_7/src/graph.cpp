#include "graph.h"

int infy = std::numeric_limits<int>::max();


int Graph::getWeight(int node1, int node2) {
    // scan the sublist and find the right weight
    std::vector<Node> nlist = adj_list[node1];
    for(auto nodes : nlist){
        // if I'm in the right node
        if(nodes.dest == node2)
            return nodes.weight;
    }
    return -1;
}

std::vector<int> Graph::getNeigh(int node) {
    // scan the sublist and create a vector with all the neighbours
    std::vector<int> res{};
    for(auto nod : getEdges(node))
        res.push_back(nod.dest);
    return res;
}

void Graph::addEdge(int src, int dest, int weight){
    if(adj_list.size() < src+1)
    // if I'm also adding a new node create room for it
        for(int i = adj_list.size()-1; i < src+1; ++i ){
            adj_list.push_back(std::vector<Node>{});
            distance.push_back(infy);
            predecessors.push_back(-1);
            color.push_back("white");
        }
    adj_list[src].push_back(Node(dest, weight));
}


