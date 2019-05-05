#include <stdlib.h>
#include <stdio.h>
#include<math.h>
#include "heap.h"
#include "vector.h"

// implement the three sorting alghoritm seen at lesson, for array of int type 





void swap(int* array, int idx1, int idx2){
    int tmp = array[idx1];
    array[idx1] = array[idx2];
    array[idx2] = tmp;
}

void swapf(float* array, int idx1, int idx2){
    float tmp = array[idx1];
    array[idx1] = array[idx2];
    array[idx2] = tmp;
}

int partition(int* array, int begin, int end, int pivot){
    swap(array, begin, pivot);
    pivot = begin;
    while(begin <= end){
        if(array[begin] > array[pivot]){
            swap(array,begin,end);
            end--;
        }
        else
            begin++;
    }
    swap(array,pivot,end);
    return end;
}

int find_max(int* array, int N){
    int max = array[0];
    for(int i = 1;i < N; i++)
        if(array[i] > max)
            max = array[i];
    return max;
}

void quickSort(int*  array, int begin, int end){
    while(begin < end){
        int p = partition(array, begin, end, begin);

        quickSort(array, begin, p-1);
        begin = p+1;
    }
}

void quickSort_half(int*  array, int begin, int end){
    while(begin < end){
        int p = partition(array, begin, end, (begin+end)/2);

        quickSort_half(array, begin, p-1);
        begin = p+1;
    }
}


void heapSort(int* array, int dim){
    max_heap hp = max_heap_build(array, dim-1);
    for(int i = dim-1; i > 0; i--){
        array[i] = remove_minimum(&hp);
    }
}

void insertionSort(int*  array, int dim){
    for(int i = 0; i < dim; i++){
        int j = i;
        while(j > 0 && array[j] < array[j-1])
        {
            swap(array,j-1,j);
            j--;
        }
    }
}

void insertionSortF(float*  array, int dim){
    for(int i = 0; i < dim; i++){
        int j = i;
        while(j > 0 && array[j] < array[j-1])
        {
            swapf(array,j-1,j);
            j--;
        }
    }
}

void countingSort(int* array,int* result, int dim, int max){
    int* C = (int*) calloc(max,sizeof(int));
    for(int i=0; i< dim; i++)
        C[array[i]]++;
    for(int j = 1; j < max; j++)
        C[j] += C[j-1];
    for(int i=dim-1; i>= 0; i--){
        result[C[array[i]] - 1] = array[i];
        C[array[i]]--;
    }
    free(C);
}

void radixSort(int* array, int* result, int dim, int max){
    for(int i = 1; max/i > 0; i*=10 ) {
        int* C = (int*) calloc(10,sizeof(int));
        for(int j=0; j< dim; j++)
            C[(array[j]/i)%10]++;
        for(int j = 1; j < 10; j++)
            C[j] += C[j-1];
        for(int j=dim-1; j>= 0; j--){
            result[C[(array[j]/i)%10]-1] = array[j];
            C[(array[j]/i)%10]--;
        }
        for (int j = 0; j < dim; j++)
            array[j] = result[j];
        free(C);
    }
    
}

void bucketSort(float* array, int dim){
    vector* B = buckets_initialize(dim);
    for(int i = 0; i<dim; i++)
        append(&B[(int)(array[i]*dim)], array[i]);
    for(int i = 0; i<dim; i++)
        insertionSortF(B[i].array,B[i].i);
    int i = 0;
    for(int j = 0; j<dim; j++)
        for(int v = 0; v < B[j].i; v++){
            array[i] = B[j].array[v];
            i++;
        }
    for(int i = 0; i<dim; i++)
        free(B[i].array);   
    free(B);
}


int select_pivot(int* array, int begin, int end){
    int chunks = (end - begin)/5 + 1;
    if(end-begin+1 <= 5){
        quickSort(array, begin, end);

        return (begin+end)/2;

    }
    int cc=begin+4;
    while( cc < end - 5){
        quickSort(array,cc-4,cc);
        if(cc+5 >= end - 5) cc=end;
        else cc+=5;

    }
            
    int j = begin+5;
    for(int i = begin; i < chunks; i++){
        swap(array, i, (j+i*5)/ 2 );
        if(j+5 >= end)   j = end;
        else j+=5;

    }

    int res;
    res = select_pivot(array,begin,begin+chunks);
    return res;
}

int select_i(int* array, int i, int begin, int end){
    int j = select_pivot(array, begin,end);
    int k = partition(array,begin,end,j);
    if(i == k+1)
        return array[k];
    if(i < k+1)
        return select_i(array, i , begin, k-1);
    return select_i(array,i,k+1,end);
       
}