#ifndef CORE_STATS_H
#define CORE_STATS_H
#include "dtypes.h"

double st_vec_mean(st_vector *vec);
double st_vec_var(st_vector *vec, size_t freedom);
double st_vec_std(st_vector *vec, size_t freedom);
void   st_vec_normalize(st_vector *vec);

#endif /* CORE_STATS_H */
