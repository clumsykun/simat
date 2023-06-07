#ifndef CORE_STATS_H
#define CORE_STATS_H
#include "basic/st_basic.h"

double st_vec_mean(st_vector *vec);
double st_vec_var(st_vector *vec, size_t freedom);
double st_vec_std(st_vector *vec, size_t freedom);
void   st_vec_normalize(st_vector *vec);

double st_stats_cov(st_vector *a, st_vector *b, size_t freedom);
double st_stats_corr(st_vector *a, st_vector *b);

#endif /* CORE_STATS_H */
