#ifndef __CHAIN_MATRIX__
#define __CHAIN_MATRIX__

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "utils.h"
#include "matrix.h"
#define INFINITY INT_MAX



// fiils the m and s matrix with the optimal subsequence multiplication ost

void matrixChainAux(int* P, int** m, int** s, size_t i, size_t j);

void matrixChain(int*** res,int* P, size_t n);

void print_parenthesis(int** S,int i, int j);

void multiply_rec(float** result, float*** tensor, int **S,
                     int *dim_num,int i, int j, int naive);


#endif //__CHAIN_MATRIX__
