#ifndef __SORTING__
#define __SORTING__

#include <stdlib.h>
#include <stdio.h>
#include "heap.h"


void swap(int* array, int idx1, int idx2);

int partition(int* array, int begin, int end, int pivot);

void quickSort(int*  array, int begin, int end);

void heapSort(int* array, int dim);

void insertionSort(int*  array, int dim);

#endif //__SORTING__