#ifndef MATRIX_H
#define MATRIX_H

Matrix *create_matrix(unsigned int len, unsigned int num);

void loc_array(Array *arr, Matrix *mat, unsigned int idx);
void matrix_display(Matrix *mat);

double stats_mean(Array *arr);
double stats_var(Array *arr, unsigned int freedom);
double stats_std(Array *arr, unsigned int freedom);

#endif /* CORE_MATRIX_H */
