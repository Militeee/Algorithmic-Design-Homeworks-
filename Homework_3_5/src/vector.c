#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Variable length array
typedef struct din_array
{
  float* array;
  int real_dim;
  int i;
} vector;

// "constructor"
vector
new_vector(int dim, int i)
{
  float* array = malloc(sizeof(float) * dim);
  vector res = { array, dim, i };
  return res;
}

// basically creates a vector of vectors
vector*
buckets_initialize(int dim)
{
  vector* res = (vector*)malloc(sizeof(vector) * dim);
  for (int i = 0; i < dim; i++)
    res[i] = new_vector(1, 0);
  return res;
}

// resize of a factor of 2
void
resize(vector* vec)
{
  float* new_array = malloc(sizeof(float) * vec->real_dim * 2);
  for (int i = 0; i < vec->real_dim; i++)
    new_array[i] = vec->array[i];

  vec->real_dim *= 2;
  float* tmp = vec->array;
  vec->array = new_array;
  free(tmp);
}

// append a new value and resize if I'm out of bound
void
append(vector* vec, float elem)
{
  if (vec->i == vec->real_dim - 1)
    resize(vec);
  vec->array[vec->i] = elem;
  vec->i++;
}