#ifndef CORE_VECTOR_H
#define CORE_VECTOR_H
#include "elemental.h"

st_vector *st_vec_copy_cast(st_vector *vec, __st_dtype dtype);
void       st_vec_scale(st_vector *vec, double min, double max);
void       st_vec_sub_scalar(st_vector *vec, double value);
void       st_vec_mul_scalar(st_vector *vec, double value);

double     st_vec_dot(st_vector *a, st_vector *b);
bool       st_vec_equal(st_vector *a, st_vector *b);
st_vector *st_vec_add(st_vector *a, st_vector *b);
st_vector *st_vec_sub(st_vector *a, st_vector *b);
st_vector *st_vec_mul(st_vector *a, st_vector *b);
st_vector *st_vec_div(st_vector *a, st_vector *b);

#endif /* CORE_VECTOR_H */
