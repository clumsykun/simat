#ifndef VECTOR_H
#define VECTOR_H
#include "types.h"

Vector *create_vector(unsigned int len);
void free_vector(Vector *vec);
void vector_display(Vector *vec);
void vector_set_rand(Vector *arr);
// double array_max(Vector *arr);
// double array_min(Vector *arr);
// void array_scale(Vector *arr, double min, double max);
// void array_sort(Vector *arr);

#endif
