#ifndef CORE_BASIC_H
#define CORE_BASIC_H

#include <math.h>
#include "vector.h"
#include "matrix.h"
#include "view.h"
#include "dataset.h"

double st_precise(double x, size_t ndigits);

void st_vec_rand(const st_vector *vec);
void st_vec_sort(st_vector *vec);
void st_vec_reverse(st_vector *vec);

void st_mat_rand(const st_matrix *mat);

void st_view_rand(st_view *view);
void st_view_sort(st_view *view);
void st_view_reverse(st_view *view);

#endif /* CORE_BASIC_H */
