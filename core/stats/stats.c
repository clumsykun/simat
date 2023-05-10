#include <math.h>
#include <stdlib.h>
#include "dtypes.h"

double st_vec_mean(st_vector *vec)
{
    double sum = 0;

    for (size_t i = 0; i < vec->len; i++) {
        sum += st_vec_access(vec, i);
    }

    return sum / (double)vec->len;
}

double st_vec_var(st_vector *vec, size_t freedom)
{
    double mean = st_vec_mean(vec);
    double sum_sq_diff = 0;

    for (size_t i = 0; i < vec->len; i++)
        sum_sq_diff += (st_vec_access(vec, i) - mean) * (st_vec_access(vec, i) - mean);

    return sum_sq_diff / (double) (vec->len - freedom);
}

double st_vec_std(st_vector *vec, size_t freedom)
{
    return sqrt(st_vec_var(vec, freedom));
}

// /* scale the vector to make sure that its mean equals 0, its standard variance equals 1. */
// void vector_normalize(Vector *vec)
// {
//     double mean = stats_mean(vec);
//     double std = stats_std(vec, 0);

//     for (size_t i = 0; i < vec->len; i++) {
//         idx(vec, i) = (idx(vec, i) - mean) / std;
//     }
// }
