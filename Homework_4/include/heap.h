#ifndef __HEAP__
#define __HEAP__

#include <stdlib.h>
#include<stdio.h>
#include<limits.h>
#include "utils.h"
#define INFINITY INT_MAX



typedef struct heap{
    int* array;
    size_t n;
} min_heap;

size_t left(size_t i);

size_t right(size_t i);

size_t get_root();

size_t parent(size_t i);

int is_root(size_t i);

int is_valid_node(min_heap* hp, size_t node);

int min_heap_minimum(min_heap* hp);

void swap_min_heap(min_heap* hp, size_t i, size_t m);

//void min_heapify(min_heap* hp, size_t i){

void min_heapify(min_heap* hp, size_t i);

int remove_minimum(min_heap* hp);

void decrease_key_min_heap(min_heap* hp, size_t i, int value);

void min_heap_insert(min_heap* hp, int value);

void print_min_heap(min_heap* hp);

min_heap min_heap_build(int* array, size_t n);

# endif //___HEAP__