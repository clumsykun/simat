#ifndef CORE_STATS_H
#define CORE_STATS_H
#include "dtypes.h"

double stats_mean(Vector *vec);
double stats_var(Vector *vec, unsigned int freedom);
double stats_std(Vector *vec, unsigned int freedom);
void vector_normalize(Vector *vec);

#endif /* CORE_STATS_H */
