#ifndef CORE_MATRIX_H
#define CORE_MATRIX_H

Matrix *create_matrix(unsigned int nrow, unsigned int ncol);
void free_matrix(Matrix *mat);
void loc_col(Vector *vec, Matrix *mat, unsigned int idx);
void matrix_display(Matrix *mat);

#endif /* CORE_MATRIX_H */
