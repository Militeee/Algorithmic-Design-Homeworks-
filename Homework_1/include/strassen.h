#ifndef __STRASSEN__

#include <stdlib.h>

void
strassen(float** C, float** A, float** B, const size_t n);

void
sub_matrix_blocks(float** C,
                  const size_t C_f_row,
                  const size_t C_f_col,
                  float** A,
                  const size_t A_f_row,
                  const size_t A_f_col,
                  float** B,
                  const size_t B_f_row,
                  const size_t B_f_col,
                  const size_t n);

void
sum_matrix_blocks(float** C,
                  const size_t C_f_row,
                  const size_t C_f_col,
                  float** A,
                  const size_t A_f_row,
                  const size_t A_f_col,
                  float** B,
                  const size_t B_f_row,
                  const size_t B_f_col,
                  const size_t n);

void
naive_aux(float** C,
          const size_t C_f_row,
          const size_t C_f_col,
          float** A,
          const size_t A_f_row,
          const size_t A_f_col,
          float** B,
          const size_t B_f_row,
          const size_t B_f_col,
          const size_t n);

#endif // __STRASSEN__
