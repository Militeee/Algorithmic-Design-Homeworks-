#include "dijkstra.h"

void init_sssp(Graph& gr){
    for(int i = 0; i < gr.size() ; i++){
        gr.setDist(i,inf);
        gr.setPred(i,-1);
    }
}

void relax(Graph& gr, int src, int dest, int weight){
    if(gr.getDist(src) + gr.getWeight(src,dest) < gr.getDist(dest)){
        gr.setDist(dest,gr.getDist(src) + gr.getWeight(src,dest));
        gr.setPred(dest,src);
    }
}

void dijkstra(Graph& gr, int src){
    init_sssp(gr);
    gr.setDist(src,0);
    std::vector<int>& dst = gr.getDists();
    std::vector<pair> arr(gr.size());
    for(int i = 0; i < gr.size(); i++){
        arr[i].first = &dst[i];
        arr[i].second = i; 
    }

    pair* dist = &arr[0];
    min_heap queue = min_heap_build(dist, gr.size()-1);
    std::cout << std::endl;
    while(queue.n != 0){

        int min_node = remove_minimum(&queue);

                    

        for(auto nods : gr.getNeigh(min_node)){
            
            relax(gr, min_node, nods, gr.getWeight(min_node, nods));
        }
        min_heapify(&queue,0);
    }
}

void printPathAux(Graph gr, int dest){
    if (gr.getPred(dest) == -1){
        std::cout << dest << "->" ;
        return;
    }
    printPathAux(gr, gr.getPred(dest));
    std::cout << dest << "->" ;

}
void printPath(Graph gr, int dest, int src){
    std::cout << "Path from " << src << " to " << dest << std::endl ;
    printPathAux(gr, gr.getPred(dest));
    std::cout << dest << "\t" << "distance = " << gr.getDist(dest) << std::endl;
}



