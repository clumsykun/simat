#ifndef CORE_MATRIX_H
#define CORE_MATRIX_H
#include "st_c_elemental.h"

void   st_mat_scale(st_matrix *mat, st_d64 min, st_d64 max);

st_matrix *st_mat_copy_t(st_matrix *mat);
st_matrix *st_mat_dot(st_matrix *a, st_matrix *b);

#endif /* CORE_MATRIX_H */
