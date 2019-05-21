#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_ELEM_VALUE 1
#define MAX_RAND 500

void
random_fill_array(int* array, size_t n)
{
  for (size_t i = 0; i < n; i++)
    array[i] = rand() % MAX_RAND + 10;
}

double
get_execution_time(const struct timespec b_time, const struct timespec e_time)
{
  return (e_time.tv_sec - b_time.tv_sec) +
         (e_time.tv_nsec - b_time.tv_nsec) / 1E9;
}

void
randomly_fill_matrix(float** A, const size_t A_rows, const size_t A_cols)
{
  for (size_t i = 0; i < A_rows; i++) {
    for (size_t j = 0; j < A_cols; j++) {
      A[i][j] = rand() % (2 * MAX_ELEM_VALUE) - MAX_ELEM_VALUE;
    }
  }
}

void
copy_matrix(float** A, float** B, const size_t A_rows, const size_t A_cols)
{
  for (size_t i = 0; i < A_rows; i++) {
    for (size_t j = 0; j < A_cols; j++) {
      B[i][j] = A[i][j];
    }
  }
}

void
print_array(int* a, size_t size)
{
  for (size_t j = 0; j < size; j++) {
    printf("%d\t", a[j]);
  }
  printf("\n");
}