#include <stdlib.h>
#include<stdio.h>
#include "utils.h"
#include "heap.h"


int main(int argc , char* argv[]){
    if (argc < 2) {
        printf("missing argument\n");
        exit(-1);
    }
    struct timespec b_time, e_time;

    size_t dim = atoi(argv[1]);
    int* array = (int*) malloc(sizeof(int)* dim);
    random_fill_array(array,dim);
    //print_array(array, dim);
    size_t min_heap_dim = dim-1;
    
    clock_gettime(CLOCK_REALTIME, &b_time);
    min_heap hp = min_heap_build(array,min_heap_dim);
    clock_gettime(CLOCK_REALTIME, &e_time);
    printf("Building heap time for dim=%ld\t%lf\n", dim,get_execution_time(b_time, e_time) );
    //print_min_heap(&hp);

    /*
    clock_gettime(CLOCK_REALTIME, &b_time);
    remove_minimum(&hp);
    clock_gettime(CLOCK_REALTIME, &e_time);
    printf("Remove minimum time for dim=%ld\t%lf\n", dim,get_execution_time(b_time, e_time) );
    
    clock_gettime(CLOCK_REALTIME, &b_time);
    min_heap_insert(&hp,250);
    clock_gettime(CLOCK_REALTIME, &e_time);
    printf("Heap insert time for dim=%ld\t%lf\n", dim,get_execution_time(b_time, e_time) );
    //print_min_heap(&hp);
    
    clock_gettime(CLOCK_REALTIME, &b_time);
    decrease_key_min_heap(&hp,5,0);
    clock_gettime(CLOCK_REALTIME, &e_time);
    printf("Decrease key time for dim=%ld\t%lf\n", dim,get_execution_time(b_time, e_time) );
    //print_min_heap(&hp);
    */
    free(array);

}
