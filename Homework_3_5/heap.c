#include <stdlib.h>
#include<stdio.h>
#include<limits.h>
#include "utils.h"
#include <math.h>


// Implement an integer min heap with the methods seen during the lessons


typedef struct heap{
    int* array;
    size_t n;
} max_heap;

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


int is_valid_node(max_heap* hp, size_t node){
    return hp->n >= node;
}

int max_heap_minimum(max_heap* hp){
    return hp->array[get_root()];
}

void swap_max_heap(max_heap* hp, size_t i, size_t m){
    int tmp = hp->array[i];
    hp->array[i] = hp->array[m]; 
    hp->array[m] = tmp; 
}

/*
void max_heapify(max_heap* hp, size_t i){
    size_t m = i;
    size_t child[2] ={left(i), right(i)};
    for(size_t j = 0; j < 2 ; j++)
        if(is_valid_node(hp, child[j]) && hp->array[child[j]] <= hp->array[m])
            m = child[j];
    if (i != m){
       
        swap_max_heap(hp,i,m);
        max_heapify(hp,m);
    }

}
*/

void max_heapify(max_heap* hp, size_t i){
    size_t m = i,k = -1;
    while(k != m)
    {
        k = m;
        size_t child[2] ={left(k), right(k)};
        for(size_t j = 0; j < 2 ; j++)
            if(is_valid_node(hp, child[j]) && hp->array[child[j]] >= hp->array[m])
                m = child[j];
        if (k != m)
            swap_max_heap(hp,k,m);
    }
}


int remove_minimum(max_heap* hp){
    int min = hp->array[0];
    hp->array[0] = hp->array[hp->n];
    hp->n--;
    max_heapify(hp,0); 
    return min;
}

void decrease_key_max_heap(max_heap* hp, size_t i, int value){
    if(hp->array[i] >= value)
        printf("%d is not smaller than %d\n",value, hp->array[i]);
    hp->array[i] = value;
    while(!is_root(i) && hp->array[i] >= hp->array[parent(i)]){
        swap_max_heap(hp,i,parent(i));
        i = parent(i);
    }
}

void max_heap_insert(max_heap* hp, int value){
    hp->n++;
    hp->array[hp->n] = INT_MAX;
    decrease_key_max_heap(hp,hp->n,value);
}


void print_max_heap(max_heap* hp){
    print_array(hp->array, hp->n + 1);
}

max_heap max_heap_build(int* array, size_t n){
    max_heap hp = {array,n};
    for(int i = n; i >= 0; i--)
        max_heapify(&hp,i);
    return hp;
    
}


