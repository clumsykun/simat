#include <math.h>
#include <stdlib.h>
#include "types.h"

double stats_mean(Vector *vec)
{
    double sum = 0;

    for (size_t i = 0; i < vec->len; i++) {
        sum += idx(vec, i);
    }

    return sum / (double)vec->len;
}

double stats_var(Vector *vec, unsigned int freedom)
{
    double mean = stats_mean(vec);
    double sum_sq_diff = 0;

    for (size_t i = 0; i < vec->len; i++) {
        sum_sq_diff += (idx(vec, i) - mean) * (idx(vec, i) - mean);
    }

    return sum_sq_diff / (double) (vec->len - freedom);
}

double stats_std(Vector *vec, unsigned int freedom)
{
    return sqrt(stats_var(vec, freedom));
}

/* scale the vector to make sure that its mean equals 0, its standard variance equals 1. */
void vector_normalize(Vector *vec)
{
    double mean = stats_mean(vec);
    double std = stats_std(vec, 0);

    for (size_t i = 0; i < vec->len; i++) {
        idx(vec, i) = (idx(vec, i) - mean) / std;
    }
}
