#ifndef __SORTING__
#define __SORTING__

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

void
swap(int* array, int idx1, int idx2);

void
swapf(float* array, int idx1, int idx2);

int
find_max(int* array, int N);

int
partition(int* array, int begin, int end, int pivot);

void
quickSort(int* array, int begin, int end);

void
quickSort_half(int* array, int begin, int end);

void
heapSort(int* array, int dim);

void
insertionSort(int* array, int dim);

void
insertionSortF(float* array, int dim);

void
countingSort(int* array, int* result, int dim, int max);

void
radixSort(int* array, int* result, int dim, int max);

void
bucketSort(float* array, int dim);

int
select_i(int* array, int i, int begin, int end);

#endif //__SORTING__