#ifndef CORE_VECTOR_H
#define CORE_VECTOR_H
#include "dtypes.h"

Vector *create_bool_vector(unsigned int len);
Vector *create_pixel_vector(unsigned int len);
Vector *create_int_vector(unsigned int len);
Vector *create_double_vector(unsigned int len);
void free_vector(Vector *vec);

double vector_max(Vector *vec);
double vector_min(Vector *vec);

void vector_display(Vector *vec);
void vector_set_rand(Vector *vec);
void vector_scale(Vector *vec, double min, double max);
void vector_reverse(Vector *vec);
void vector_sort(Vector *vec, enum order order);

#endif /* CORE_VECTOR_H */
