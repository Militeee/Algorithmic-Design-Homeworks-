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


        for(int j = 0 ; j<i; j++){
            // insertion sort worst case, all the value in reverse order
            array1[j] = i-j;
            // insertion sort best case, all the value already ordered
            array3[j] = j+1;
            // for quick sort we have all the value ordered 
            // we are just gonna change the pivot choice
            array2[j] = j+1;
            array4[j] = j+1;

        }
        // it becomes too slow
        if(i < 131073){
            clock_gettime(CLOCK_REALTIME, &b_time);
            insertionSort(array1,i);
            clock_gettime(CLOCK_REALTIME, &e_time);
            printf("Insertion sort worst \t%lf\n", get_execution_time(b_time, e_time) );
            //print_array(array1,i);
        }

        // choose the first element as a pivot
        clock_gettime(CLOCK_REALTIME, &b_time);
        quickSort(array2, 0, i-1);
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("Quick sort worst  \t%lf\n", get_execution_time(b_time, e_time) );
        //print_array(array2,i);

        clock_gettime(CLOCK_REALTIME, &b_time);
        insertionSort(array3,i);
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("Insertion sort best \t%lf\n", get_execution_time(b_time, e_time) );
        //print_array(array3,i);

        // choose the element in the middle
        clock_gettime(CLOCK_REALTIME, &b_time);
        quickSort_half(array4,0, i-1);
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("Quick sort best \t%lf\n", get_execution_time(b_time, e_time) );
        //print_array(array4,i);

        free(array1);
        free(array2);
        free(array3);
        free(array4);
    }
}