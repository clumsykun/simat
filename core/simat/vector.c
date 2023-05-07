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

// /**
//  * choosing the last value as pivot
//  * @head: address of the first number of the vector
//  * @len: length of the vector
//  * @candidate: the candidate position of pivot
//  */
// static char *__partition(enum st_dtype dtype, char *start, char *end)
// {
//     size_t size = st_byteof(dtype);
//     double pivot = st_access(dtype, end);
//     char *candidate = start - size;

//     for (char *p = start; p < end; p+=size) {
//         if (st_access(dtype, p) < pivot) {

//             candidate += size;
//             __swap(candidate, p, size);
//         }
//     }

//     candidate += size;
//     __swap(candidate, end, size);
//     return candidate;
// }

// static void __quick_sort(enum st_dtype dtype, char *start, char *end)
// {
//     if (start < end) {
//         /**
//          * [p, p + len*size] -->
//          * [p, p + pi*size], [p + (pi+1)*size, p+len*size]
//          */
//         char* p = __partition(dtype, start, end);
//         __quick_sort(dtype, start, p-st_byteof(dtype));
//         __quick_sort(dtype, p+st_byteof(dtype), end);
//     }
// }

// void vector_sort(Vector *vec, enum order order)
// {
//     __quick_sort(vec->dtype, vec->head, vec->last);
//     if (order == descend) {
//         vector_reverse(vec);
//     }
//     __check();
// }
