#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "sorting.h"
#define LIMIT 10000000

int main(){
    for(size_t i = 10; i < LIMIT; i*=10){
        printf("Dimension of array = %ld\n", i);
        int* array1 = (int*) malloc(sizeof(int) * i);
        int* array2 = (int*) malloc(sizeof(int) * i);
        int* array3 = (int*) malloc(sizeof(int) * i);

        random_fill_array(array1, i);
        random_fill_array(array2, i);
        random_fill_array(array3, i);

        //print_array(array1,i);
        struct timespec b_time, e_time;

        if(i < 10000){
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

        free(array1);
        free(array2);
        free(array3);
    }
    return 0;
}