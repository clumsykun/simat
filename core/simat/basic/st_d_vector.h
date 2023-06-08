#ifndef CORE_VECTOR_H
#define CORE_VECTOR_H
#include "st_c_elemental.h"

void       st_vec_scale(st_vector *vec, st_d64 min, st_d64 max);
void       st_vec_sub_scalar(st_vector *vec, st_d64 value);
void       st_vec_mul_scalar(st_vector *vec, st_d64 value);

st_d64     st_vec_dot(st_vector *a, st_vector *b);
st_bool       st_vec_equal(st_vector *a, st_vector *b);

#endif /* CORE_VECTOR_H */
