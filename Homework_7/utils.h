#ifndef __UTILZ__
#define __UTILZ__
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <time.h>
#define MAX_RAND 500



void random_fill_array(int* array, size_t n);

double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time);

void randomly_fill_matrix(float **A, const size_t A_rows, const size_t A_cols);

void copy_matrix(float** A, float** B,const size_t A_rows, const size_t A_cols);

void print_array(int* a, size_t size);

#endif //__UTILZ__

