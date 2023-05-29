#include "basic.h"

typedef double (*dist_fp)(st_vector *,  st_vector *);

double st_dist_euclid(st_vector *v1, st_vector *v2);
double st_dist_cosine(st_vector *v1, st_vector *v2);
double st_dist_cos_vw(st_vector *v, st_view *w);
double st_dist_cos_ww(st_view *w1, st_view *w2);
void st_dist_mat_row(st_matrix *re, st_matrix *mat, dist_fp);
