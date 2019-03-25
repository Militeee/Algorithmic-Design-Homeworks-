#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

// implement the three sorting alghoritm seen at lesson, for array of int type 

void swap(int* array, int idx1, int idx2){
    int tmp = array[idx1];
    array[idx1] = array[idx2];
    array[idx2] = tmp;
}

int partition(int* array, int begin, int end, int pivot){
    // swap(array, start, pivot);
    while(begin <= end){
        if(array[begin] < array[pivot]){
            swap(array,begin,end);
            end--;
        }
        else
            begin++;
    }
    swap(array,pivot,end);
    return end;
}

void quickSort(int*  array, int begin, int end){
    while(begin < end){
        int p = partition(array, begin, end, begin);

        quickSort(array, begin, p-1);
        begin = p+1;
    }
}

void heapSort(int* array, int dim){
    min_heap hp = min_heap_build(array, dim-1);
    for(int i = dim-1; i > 0; i--){
        array[i] = remove_minimum(&hp);
    }
}

void insertionSort(int*  array, int dim){
    for(int i = 0; i < dim; i++){
        int j = i;
        while(j > 0 && array[j] > array[j-1])
        {
            swap(array,j-1,j);
            j--;
        }
    }
}