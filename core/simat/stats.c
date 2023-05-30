#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "dtypes.h"

static void check_vec_length(st_vector *a, st_vector *b)
{
    if (a->len != b->len)
        __st_raise_length_error();

    __st_check();
}

double st_vec_mean(st_vector *vec)
{
    double sum = 0;

    for (size_t i = 0; i < vec->len; i++)
        sum += st_vec_access(vec, i);

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

/* scale the vector to make sure that its mean equals 0, its standard variance equals 1. */
void st_vec_normalize(st_vector *vec)
{
    if (vec->dtype != __st_double) {
        printf("only decimal vector support normalization, so this action was omitted.\n");
        return;
    }

    double mean = st_vec_mean(vec);
    double std = st_vec_std(vec, 0);
    double scaled;

    for (size_t i = 0; i < vec->len; i++) {
        scaled = (st_vec_access(vec, i) - mean) / std;
        st_vec_assign(vec, i, scaled);
    }
}

double st_stats_cov(st_vector *a, st_vector *b, size_t freedom)
{
    check_vec_length(a, b);
    double mean_a = st_vec_mean(a);
    double mean_b = st_vec_mean(b);
    double diff = 0;

    for (size_t i = 0; i < a->len; i++) {
        diff += (st_vec_access(a, i) - mean_a)*(st_vec_access(b, i) - mean_b);
    }

    return diff / (a->len-freedom);
}
