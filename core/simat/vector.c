#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "dtypes.h"


double st_vec_min(st_vector *vec)
{
    double min = st_vec_access(vec, 0);
    void *p;
    for (size_t i = 0; i < vec->len; i++)
        min = (min <= st_vec_access(vec, i) ? min : st_vec_access(vec, i));

    __st_check();
    return min;
}

double st_vec_max(st_vector *vec)
{
    double max = st_vec_access(vec, 0);
    void *p;
    for (size_t i = 0; i < vec->len; i++)
        max = (max >= st_vec_access(vec, i) ? max : st_vec_access(vec, i));

    __st_check();
    return max;
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

// void vector_reverse(Vector *vec)
// {
//     char *mid = vec->head + (vec->len/2)*(vec->nbyte);
//     char *r = vec->last;
//     for (char *l = vec->head; l <= mid; l += vec->nbyte, r -= vec->nbyte)
//         __swap(l, r, vec->nbyte);
// }
