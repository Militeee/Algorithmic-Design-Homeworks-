#ifndef __HEAP__
#define __HEAP__

#include <stdlib.h>
#include<stdio.h>
#include<limits.h>
#include "utils.h"
#include <math.h>



typedef struct heap{
    int* array;
    size_t n;
} max_heap;

size_t left(size_t i);

size_t right(size_t i);

size_t get_root();

size_t parent(size_t i);

int is_root(size_t i);

int is_valid_node(max_heap* hp, size_t node);

int max_heap_minimum(max_heap* hp);

void swap_max_heap(max_heap* hp, size_t i, size_t m);

//void max_heapify(max_heap* hp, size_t i){

void max_heapify(max_heap* hp, size_t i);

int remove_minimum(max_heap* hp);

void decrease_key_max_heap(max_heap* hp, size_t i, int value);

void max_heap_insert(max_heap* hp, int value);

void print_max_heap(max_heap* hp);

max_heap max_heap_build(int* array, size_t n);

# endif //___HEAP__