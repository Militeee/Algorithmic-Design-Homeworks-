#include "dijkstra.h"

// set inf as the max integer number
int inf = std::numeric_limits<int>::max();


// just swap two elements of an array
void swap(pair* array, int i, int j){
    
    pair tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

// scan an array to find its minimum starting from an index(idx variable)
int find_min(pair* arr, int dim, int idx){
    int min = arr[idx].second;
    for(int i = idx+1; i < dim; i++){
        if(*(arr[i].first)  < min)
            min = arr[i].second;
    }
    swap(arr,min,idx);
    return arr[idx].second;
}

// set distances and predecessor for the starting of the dijktra algorithm
void init_sssp(Graph& gr){
    for(int i = 0; i < gr.size() ; i++){
        gr.setDist(i,inf);
        gr.setPred(i,-1);
    }
}

// change the distance and update the predecessor if the new distance is smaller
// than the older one
void relax(Graph& gr, int src, int dest, int weight){
    if(gr.getDist(src) + gr.getWeight(src,dest) < gr.getDist(dest)){
        gr.setDist(dest,gr.getDist(src) + gr.getWeight(src,dest));
        gr.setPred(dest,src);
    }
}

// dijkstra algorithm as seen in class
void dijkstra(Graph& gr, int src){
    // set the dist and pred to inf and -1
    init_sssp(gr);
    // set the source dist to 0
    gr.setDist(src,0);
    // basically some pointers movement to ensure
    // that the change made by relax happens also in the queue
    // and to delegate to the std::vector the memory management
    std::vector<int>& dst = gr.getDists();
    std::vector<pair> arr(gr.size());
    for(int i = 0; i < gr.size(); i++){
        arr[i].first = &dst[i];
        arr[i].second = i; 
    }
    pair* dist = &arr[0];
    // build the queue
    min_heap queue = min_heap_build(dist, gr.size()-1);
    // while the queue isnot empty
    while(queue.n != 0){
        // find the node with minimum distance        
        int min_node = remove_minimum(&queue);

        // and relax his neighbours
        for(auto nods : gr.getNeigh(min_node)){
            
            relax(gr, min_node, nods, gr.getWeight(min_node, nods));
        }
        // we heapify after, after the dist values are updated
        min_heapify(&queue,0);
    }
}

// same as before but this time we use just an array
void dijkstra_array(Graph& gr, int src){
    init_sssp(gr);
    gr.setDist(src,0);
    std::vector<int>& dst = gr.getDists();
    // counter to know when to stop and to set 
    // a boundary for the removed node in the array
   int counter = 0;
    std::vector<pair> arr(gr.size());
    for(int i = 0; i < gr.size(); i++){
        arr[i].first = &dst[i];
        arr[i].second = i; 
    }

    pair* dist = &arr[0];
    while(counter < gr.size()){

        int min_node = find_min(dist, gr.size(),counter);
        counter++;
        for(auto nods : gr.getNeigh(min_node)){
            
            relax(gr, min_node, nods, gr.getWeight(min_node, nods));
        }

    }

}

// aux function to print the path discovered
void printPathAux(Graph gr, int dest){
    if (gr.getPred(dest) == -1){
        std::cout << dest << "->" ;
        return;
    }
    printPathAux(gr, gr.getPred(dest));
    std::cout << dest << "->" ;

}

// function to print the path discovered
void printPath(Graph gr, int dest, int src){
    std::cout << "Path from " << src << " to " << dest << std::endl ;
    printPathAux(gr, gr.getPred(dest));
    std::cout << dest << "\t" << "distance = " << gr.getDist(dest) << std::endl;
}



