#ifndef __MATRIX__

#include <stdio.h>
#include <stdlib.h>

int
naive_matrix_mult(float** C,
                  float** A,
                  float** B,
                  const size_t A_rows,
                  const size_t A_cols,
                  const size_t B_rows,
                  const size_t B_cols);

float**
allocate_matrix_f(const size_t rows, const size_t cols);

void
deallocate_matrix_f(float** A, const size_t rows);

int**
allocate_matrix(const size_t rows, const size_t cols);

void
deallocate_matrix(int** A, const size_t rows);

int
same_matrix(float** A,
            const size_t A_rows,
            const size_t A_cols,
            float** B,
            const size_t B_rows,
            const size_t B_cols);

void
print_matrix(int** m, int size);
void
print_matrix_2(float** m, int size, int size2);

#endif // __MATRIX__
