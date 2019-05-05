#include <stdlib.h>
#include<stdio.h>
#include<limits.h>
#include "utils.h"
#include "heap.h"
#define INFINITY INT_MAX


// Implement an integer min heap with the methods seen during the lessons



size_t left(size_t i){
    return 2*i +1;
}

size_t right(size_t i){
    return 2*i + 2;
}

size_t get_root(){
    return 0;
}

size_t parent(size_t i){
    return i/2;
}

int is_root(size_t i){
    return i == 0;
}


int is_valid_node(min_heap* hp, size_t node){
    return hp->n >= node;
}

int min_heap_minimum(min_heap* hp){
    return hp->array[get_root()].second;
}

void swap_min_heap(min_heap* hp, size_t i, size_t m){
    pair tmp = hp->array[i];
    hp->array[i] = hp->array[m]; 
    hp->array[m] = tmp; 
}

/*
void min_heapify(min_heap* hp, size_t i){
    size_t m = i;
    size_t child[2] ={left(i), right(i)};
    for(size_t j = 0; j < 2 ; j++)
        if(is_valid_node(hp, child[j]) && hp->array[child[j]] <= hp->array[m])
            m = child[j];
    if (i != m){
       
        swap_min_heap(hp,i,m);
        min_heapify(hp,m);
    }

}
*/

void min_heapify(min_heap* hp, size_t i){
    size_t m = i,k = -1;
    while(k != m)
    {
        k = m;
        size_t child[2] ={left(k), right(k)};
        for(size_t j = 0; j < 2 ; j++)
            if(is_valid_node(hp, child[j]) && *(hp->array[child[j]].first) <= *(hp->array[m].first))
                m = child[j];
        if (k != m)
            swap_min_heap(hp,k,m);
    }
}


int remove_minimum(min_heap* hp){
    int min = hp->array[0].second;
    hp->array[0] = hp->array[hp->n];
    hp->n--;
    //min_heapify(hp,0); 
    return min;
}

void decrease_key_min_heap(min_heap* hp, size_t i, int value){
    if(*(hp->array[i].first) <= value)
        printf("%d is not smaller than %d\n",value, *(hp->array[i].first));
    *(hp->array[i].first) = value;
    while(!is_root(i) && *(hp->array[i].first) <= *(hp->array[parent(i)].first)){
        swap_min_heap(hp,i,parent(i));
        i = parent(i);
    }
}

void min_heap_insert(min_heap* hp, int value){
    hp->n++;
    *(hp->array[hp->n].first) = INFINITY;
    decrease_key_min_heap(hp,hp->n,value);
}


void print_min_heap(min_heap* hp){
    int arr[hp->n];
    for(int i = 0; i <= hp->n; i++)
        arr[i] = *(hp->array[i].first);
    print_array(arr, hp->n + 1);
}

min_heap min_heap_build(pair* array, size_t n){
    min_heap hp = {array,n};
    for(int i = n; i >= 0; i--)
        min_heapify(&hp,i);
    return hp;
    
}


