#ifndef CORE_VECTOR_H
#define CORE_VECTOR_H
#include "dtypes.h"

double st_vec_min(st_vector *vec);
double st_vec_max(st_vector *vec);
void st_vec_scale(st_vector *vec, double min, double max);

// void vector_reverse(Vector *vec);

#endif /* CORE_VECTOR_H */
