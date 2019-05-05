#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "sorting.h"
#include <math.h>
#define LIMIT pow(2,22)

int main(){
    
    struct timespec b_time, e_time;
    for(size_t i = 128; i < LIMIT; i*=2){
        printf("Dimension of array = %ld\n", i);
        int* array1 = (int*) malloc(sizeof(int) * i);
        int* array2 = (int*) malloc(sizeof(int) * i);
        int* array3 = (int*) malloc(sizeof(int) * i);
        int* array4 = (int*) malloc(sizeof(int) * i);
        int* array5 = (int*) malloc(sizeof(int) * i);
        float* array6 = (float*) malloc(sizeof(float) * i);

        int* result1 = (int*) malloc(sizeof(int) * i);



        random_fill_array(array1, i);
        random_fill_array(array2, i);
        random_fill_array(array3, i);
        random_fill_array(array4, i);
        random_fill_array(array5, i);
        random_fill_arrayF(array6, i);


        //print_array(array1,i);

        if(i < 65537){
            clock_gettime(CLOCK_REALTIME, &b_time);
            insertionSort(array1, i);
            clock_gettime(CLOCK_REALTIME, &e_time);
            printf("Insertion sort\t%lf\n", get_execution_time(b_time, e_time) );
            //print_array(array1,i);
        }

        clock_gettime(CLOCK_REALTIME, &b_time);
        quickSort(array2,0 , i-1);
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("Quick sort\t%lf\n", get_execution_time(b_time, e_time) );
        //print_array(array2,i);


        clock_gettime(CLOCK_REALTIME, &b_time);
        heapSort(array3, i);
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("Heap sort\t%lf\n", get_execution_time(b_time, e_time) );
        //print_array(array3,i);

        clock_gettime(CLOCK_REALTIME, &b_time);
        countingSort(array4,result1, i,510);
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("Counting sort\t%lf\n", get_execution_time(b_time, e_time) );
        //print_array(result1,i);

        int max = find_max(array5,i);
        clock_gettime(CLOCK_REALTIME, &b_time);
        radixSort(array5,result1, i,max);
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("Radix sort\t%lf\n", get_execution_time(b_time, e_time) );
        //print_array(result1,i);

        
        clock_gettime(CLOCK_REALTIME, &b_time);
        bucketSort(array6,i);
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("Bucket sort\t%lf\n", get_execution_time(b_time, e_time) );
        //print_array_f(array6,i);
        

        free(array1);
        free(array2);
        free(array3);
        free(array4);
        free(array5);
        free(array6);

        free(result1);

    }
    return 0;
}