#ifndef CORE_MATRIX_H
#define CORE_MATRIX_H
#include "dtypes.h"

Matrix *create_matrix(unsigned int nrow, unsigned int ncol);
void free_matrix(Matrix *mat);

void matrix_view_row(View *view, Matrix *mat, unsigned int idx);
void matrix_view_col(View *view, Matrix *mat, unsigned int idx);
void matrix_display(Matrix *mat);

#endif /* CORE_MATRIX_H */
