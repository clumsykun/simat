#ifndef CORE_DISTANCE_H
#define CORE_DISTANCE_H

#include "basic.h"

typedef double (*dist_fp)(st_vector *,  st_vector *);

double st_dist_euclid(st_vector *v1, st_vector *v2);
double st_dist_cosine(st_vector *v1, st_vector *v2);
double st_dist_manhattan(st_vector *a, st_vector *b);

double st_dist_cos_ww(st_view *w1, st_view *w2);
void st_dist_mat_row(st_matrix *re, st_matrix *mat, dist_fp fp);

#endif /* CORE_DISTANCE_H */
