#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "heap.h"
#include "vector.h"

// implement the sorting alghoritms seen at lesson, plus the selection 




// swap two entries in an integer array
void swap(int* array, int idx1, int idx2){
    int tmp = array[idx1];
    array[idx1] = array[idx2];
    array[idx2] = tmp;
}

// swap two entries in a float array
void swapf(float* array, int idx1, int idx2){
    float tmp = array[idx1];
    array[idx1] = array[idx2];
    array[idx2] = tmp;
}

// partition an integer array around a pivot
int partition(int* array, int begin, int end, int pivot){
    // put the pivot at the begin
    swap(array, begin, pivot);
    // change the indexes to correctly find the pivot
    pivot = begin;
    // start from comparing begin and end till they end goes after begin
    while(begin <= end){
        //if I'm in the first part and I'm grater than pivot, swap me to the end
        if(array[begin] > array[pivot]){
            swap(array,begin,end);
            // reduce the end index
            end--;
        }
        // else I'm in the right place
        else
            begin++;
    }
    // put the pivot in the middle
    swap(array,pivot,end);
    return end;
}

// find the max in an integer array
int find_max(int* array, int N){
    int max = array[0];
    for(int i = 1;i < N; i++)
        if(array[i] > max)
            max = array[i];
    return max;
}

// quicksort for an integer array, note end is 1-arraydim
void quickSort(int*  array, int begin, int end){
    while(begin < end){
        int p = partition(array, begin, end, begin);

        quickSort(array, begin, p-1);
        begin = p+1;
    }
}


// quicksort that selects the pivot in the middle
void quickSort_half(int*  array, int begin, int end){
    while(begin < end){
        int p = partition(array, begin, end, (begin+end)/2);

        quickSort_half(array, begin, p-1);
        begin = p+1;
    }
}

// heap sort for an integer array
void heapSort(int* array, int dim){
    max_heap hp = max_heap_build(array, dim-1);
    for(int i = dim-1; i > 0; i--){
        array[i] = remove_minimum(&hp);
    }
}

// insertion sort for an integer array
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

// insertion sort for a float array
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

// counting sort, you need to feed the max of the array and the result array
void countingSort(int* array,int* result, int dim, int max){
    // create the buckets
    int* C = (int*) calloc(max,sizeof(int));
    // fill the buckets
    for(int i=0; i< dim; i++)
        C[array[i]]++;
    // create the index in the result
    for(int j = 1; j < max; j++)
        C[j] += C[j-1];
    // put things in the right place, pay attention to the -1 in result[*]
    for(int i=dim-1; i>= 0; i--){
        result[C[array[i]] - 1] = array[i];
        C[array[i]]--;
    }
    free(C);
}

// radix sort, basically is implemented as a counting sort on the single digits
void radixSort(int* array, int* result, int dim, int max){
    // iterate through the decimal digits
    for(int i = 1; max/i > 0; i*=10 ) {
        // counting sort with digits 
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

//bucket sort
void bucketSort(float* array, int dim){
    // create buckets with a c-copy of the c++ vector
    vector* B = buckets_initialize(dim);
    for(int i = 0; i<dim; i++)
    // with the first part we create the bucket index from the float element
        append(&B[(int)(array[i]*dim)], array[i]);
    // I've opted for insertionSort for the buckets, maybe for semplicity and because
    // I do not expect a large number of elemnts per bucket
    for(int i = 0; i<dim; i++)
        insertionSortF(B[i].array,B[i].i);
    int i = 0;
    // order the result
    for(int j = 0; j<dim; j++)
        for(int v = 0; v < B[j].i; v++){
            array[i] = B[j].array[v];
            i++;
        }
    // free the buckets
    for(int i = 0; i<dim; i++)
        free(B[i].array);   
    free(B);
}

// select the approx median pivot
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