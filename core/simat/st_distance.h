#ifndef CORE_DISTANCE_H
#define CORE_DISTANCE_H

#include "basic/st_basic.h"

typedef st_d64 (*dist_fp)(st_vector *,  st_vector *);

st_decimal st_dist_euclid(st_vector *a, st_vector *b);
st_decimal st_dist_cosine(st_vector *a, st_vector *b);
st_decimal st_dist_manhattan(st_vector *a, st_vector *b);
st_decimal st_dist_chebyshev(st_vector *a, st_vector *b);

st_decimal st_dist_cos_ww(st_view *w1, st_view *w2);
void st_dist_mat_row(st_matrix *re, st_matrix *mat, dist_fp fp);

#endif /* CORE_DISTANCE_H */
