#ifndef MATRIX_H
#define MATRIX_H

Matrix *create_matrix(unsigned int nrow, unsigned int ncol);
void free_matrix(Matrix *mat);
void loc_col(Vector *vec, Matrix *mat, unsigned int idx);
void matrix_display(Matrix *mat);

// double stats_mean(Array *arr);
// double stats_var(Array *arr, unsigned int freedom);
// double stats_std(Array *arr, unsigned int freedom);

#endif /* CORE_MATRIX_H */
