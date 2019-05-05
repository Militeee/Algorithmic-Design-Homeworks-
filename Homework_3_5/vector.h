#ifndef __VECTOR__
#define __VECTOR__

#include <stdlib.h>
#include <stdio.h>
#include<math.h>

// Variable length array
typedef struct din_array{
    float* array;
    int real_dim;
    int i;
} vector;

vector new_vector();

vector* buckets_initialize(int dim);

void resize(vector* vec);

void append(vector* vec, float elem);

#endif //__VECTOR__