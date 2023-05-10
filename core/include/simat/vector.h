#ifndef CORE_VECTOR_H
#define CORE_VECTOR_H
#include "dtypes.h"

double st_vec_min(st_vector *vec);
double st_vec_max(st_vector *vec);
double st_vec_norm(st_vector *vec);
void   st_vec_scale(st_vector *vec, double min, double max);
void   st_vec_subtract(st_vector *a, st_vector *b);

#endif /* CORE_VECTOR_H */
