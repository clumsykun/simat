#ifndef CORE_VECTOR_H
#define CORE_VECTOR_H
#include "elemental.h"

void       st_vec_scale(st_vector *vec, double min, double max);
void       st_vec_sub_scalar(st_vector *vec, double value);
void       st_vec_mul_scalar(st_vector *vec, double value);

double     st_vec_dot(st_vector *a, st_vector *b);
bool       st_vec_equal(st_vector *a, st_vector *b);

#endif /* CORE_VECTOR_H */
