#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "dtypes.h"


double st_vec_min(st_vector *vec)
{
    double min = st_vec_access(vec, 0);
    for (size_t i = 0; i < vec->len; i++)
        min = (min <= st_vec_access(vec, i) ? min : st_vec_access(vec, i));

    __st_check();
    return min;
}

double st_vec_max(st_vector *vec)
{
    double max = st_vec_access(vec, 0);
    for (size_t i = 0; i < vec->len; i++)
        max = (max >= st_vec_access(vec, i) ? max : st_vec_access(vec, i));

    __st_check();
    return max;
}

double st_vec_norm(st_vector *vec)
{
    double sum_square = 0;
    for (size_t i = 0; i < vec->len; i++) {
        sum_square += st_vec_access(vec, i)*st_vec_access(vec, i);
    }
    return sqrt(sum_square);
}

/* implement vector subtraction `a`-`b`, save result to vector `re` */
void st_vec_subtract(st_vector *re, st_vector *a, st_vector *b)
{
    if ((a->len != re->len) || (b->len != re->len)) {
        __st_raise_length_error();
        return;
    }

    void *p;
    size_t i=0;
    for st_iter_vector(p, re) {
        __st_assign_p(p, st_vec_access(a, i) - st_vec_access(b, i), a->dtype);
        i++;
    }

    __st_check();
}

/* implement vector dot production a·b, return result */
double st_vec_dot(st_vector *a, st_vector *b)
{
    if (a->len != b->len) {
        __st_raise_length_error();
        return 0;
    }

    double re = 0;
    for (size_t i = 0; i < a->len; i++)
        re += st_vec_access(a, i) * st_vec_access(b, i);

    __st_check();
    return re;
}

/* scale the vector to make sure that its max value and min value match `max` and `min`. */
void st_vec_scale(st_vector *vec, double min, double max)
{
    if st_is_bool(vec) /* do noting */
        return;

    double vec_min = st_vec_min(vec);
    double scale = st_vec_max(vec) - vec_min;
    double target_scale = max - min;
    double scaled;
    void *p;

    for st_iter_vector(p, vec) {
        scaled = min + (__st_access_p(p, vec->data->dtype) - vec_min) * target_scale / scale;
        __st_assign_p(p, scaled, vec->data->dtype);
    }

    __st_check();
}
