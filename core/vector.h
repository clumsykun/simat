#ifndef CORE_VECTOR_H
#define CORE_VECTOR_H
#include "types.h"

Vector *create_vector(unsigned int len);
View *create_view(unsigned int len);
void free_vector(Vector *vec);
void free_view(View *view);
void vector_display(Vector *vec);
void vector_set_rand(Vector *vec);
double vector_max(Vector *vec);
double vector_min(Vector *vec);
void vector_scale(Vector *vec, double min, double max);
void vector_sort(Vector *vec);

#endif /* CORE_VECTOR_H */
