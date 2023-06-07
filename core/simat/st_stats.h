#ifndef CORE_STATS_H
#define CORE_STATS_H
#include "basic/st_basic.h"

st_d64 st_vec_mean(st_vector *vec);
st_d64 st_vec_var(st_vector *vec, size_t freedom);
st_d64 st_vec_std(st_vector *vec, size_t freedom);
void   st_vec_normalize(st_vector *vec);

st_d64 st_stats_cov(st_vector *a, st_vector *b, size_t freedom);
st_d64 st_stats_corr(st_vector *a, st_vector *b);

#endif /* CORE_STATS_H */
