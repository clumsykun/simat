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

// /* scale the vector to make sure that its max value and min value match param max and min. */
// void vector_scale(Vector *vec, double min, double max)
// {
//     double vec_min = vector_min(vec);
//     double scale = vector_max(vec) - vec_min;
//     double target_scale = max - min;

//     for st_iter(vec)
//         dassign(
//             p,
//             min + (st_access(vec->dtype, p) - vec_min) * target_scale / scale,
//             vec->dtype
//         );

//     __check();
// }

// void vector_reverse(Vector *vec)
// {
//     char *mid = vec->head + (vec->len/2)*(vec->byte);
//     char *r = vec->last;
//     for (char *l = vec->head; l <= mid; l += vec->byte, r -= vec->byte)
//         __swap(l, r, vec->byte);
// }
