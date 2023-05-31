#ifndef CORE_VECTOR_H
#define CORE_VECTOR_H
#include "dtypes.h"

double st_vec_min(st_vector *vec);
double st_vec_max(st_vector *vec);
double st_vec_norm(st_vector *vec);
void   st_vec_scale(st_vector *vec, double min, double max);

void   st_vec_sub_value(st_vector *vec, double value);

void   st_vec_add(st_vector *re, st_vector *a, st_vector *b);
void   st_vec_sub(st_vector *re, st_vector *a, st_vector *b);
void   st_vec_mul(st_vector *re, st_vector *a, st_vector *b);
void   st_vec_div(st_vector *re, st_vector *a, st_vector *b);
double st_vec_dot(st_vector *a, st_vector *b);
bool   st_vec_equal(st_vector *a, st_vector *b);

#endif /* CORE_VECTOR_H */
