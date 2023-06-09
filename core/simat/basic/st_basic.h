#ifndef CORE_BASIC_H
#define CORE_BASIC_H

#include "st_d_matrix.h"
#include "st_d_vector.h"
#include "st_d_view.h"

st_decimal st_precise(st_d64 x, size_t ndigits);

void st_vec_rand(const st_vector *vec);
void st_vec_sort(st_vector *vec);
void st_vec_reverse(st_vector *vec);

void st_mat_rand(const st_matrix *mat);

void st_view_rand(st_view *view);
void st_view_sort(st_view *view);
void st_view_reverse(st_view *view);

#endif /* CORE_BASIC_H */
