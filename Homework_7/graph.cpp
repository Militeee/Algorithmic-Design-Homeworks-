#include "graph.h"


int Graph::getWeight(int node1, int node2) {
    std::vector<Node*> nlist = adj_list[node1];
    for(auto nodes : nlist){
        if(nodes->dest == node2)
            return nodes->weight;
    }
    return -1;
}

std::vector<int> Graph::getNeigh(int node) {
    std::vector<int> res{};
    for(auto nod : getEdges(node))
        res.push_back(nod->dest);
    return res;
}

void Graph::addEdge(int src, int dest, int weight){
    if(adj_list.size() < src+1)
        for(int i = adj_list.size()-1; i < src+1; ++i ){
            adj_list.push_back(std::vector<Node*>{});
            distance.push_back(inf);
            predecessors.push_back(-1);
            color.push_back("white");
        }
    adj_list[src].push_back(new Node(dest, weight));
}


