#ifndef CORE_VECTOR_H
#define CORE_VECTOR_H
#include "types.h"

Vector *create_vector(unsigned int len);
View   *create_view();
void free_vector(Vector *vec);
void free_view(View *view);

void vector_display(Vector *vec);
void view_display(View *view);

void vector_set_rand(Vector *vec);
void view_set_rand(View *view);

double vector_max(Vector *vec);
double vector_min(Vector *vec);
double view_max(View *view);
double view_min(View *view);

void vector_scale(Vector *vec, double min, double max);
void view_scale(View *view, double min, double max);

void vector_reverse(Vector *vec);
void view_reverse(View *view);

void vector_sort(Vector *vec, enum order order);
void view_sort(View *view, enum order order);

#endif /* CORE_VECTOR_H */
