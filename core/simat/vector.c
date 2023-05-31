#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "dtypes.h"

static void check_vec_length(st_vector *a, st_vector *b)
{
    if (a->len != b->len)
        __st_raise_length_error();

    __st_check();
}

double st_vec_min(st_vector *vec)
{
    double min = st_access_p(vec->data->head, vec->dtype);
    void *p;

    for __st_iter_vector(p, vec)
        min = (min <= st_access_p(p, vec->dtype)
               ? min
               : st_access_p(p, vec->dtype));

    __st_check();
    return min;
}

double st_vec_max(st_vector *vec)
{
    double max = st_access_p(vec->data->head, vec->dtype);
    void *p;

    for __st_iter_vector(p, vec)
        max = (max >= st_access_p(p, vec->dtype)
               ? max
               : st_access_p(p, vec->dtype));

    __st_check();
    return max;
}

double st_vec_norm(st_vector *vec)
{
    double sum_square = 0;
    void *p;
    for __st_iter_vector(p, vec)
        sum_square += st_access_p(p, vec->dtype)*st_access_p(p, vec->dtype);

    return sqrt(sum_square);
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

    for __st_iter_vector(p, vec) {
        scaled = min + (st_access_p(p, vec->dtype) - vec_min) * target_scale / scale;
        __st_assign_p(p, scaled, vec->dtype);
    }

    __st_check();
}

void st_vec_sub_value(st_vector *vec, double value)
{
    for (size_t i = 0; i < vec->len; i++)
        st_vec_assign(vec, i, st_vec_access(vec, i)-value);
}

/* implement vector subtraction a-b, save result to vector re */
void st_vec_add(st_vector *re, st_vector *a, st_vector *b)
{
    check_vec_length(re, a);
    check_vec_length(re, b);

    void *p;
    size_t i=0;
    for __st_iter_vector(p, re) {
        __st_assign_p(p, st_vec_access(a, i) + st_vec_access(b, i), re->dtype);
        i++;
    }

    __st_check();
}

/* implement vector subtraction a-b, save result to vector re */
void st_vec_sub(st_vector *re, st_vector *a, st_vector *b)
{
    check_vec_length(re, a);
    check_vec_length(re, b);

    void *p;
    size_t i=0;
    for __st_iter_vector(p, re) {
        __st_assign_p(p, st_vec_access(a, i) - st_vec_access(b, i), re->dtype);
        i++;
    }

    __st_check();
}

/* implement vector dot production a·b, return result */
double st_vec_dot(st_vector *a, st_vector *b)
{
    check_vec_length(a, b);

    double re = 0;
    for (size_t i = 0; i < a->len; i++)
        re += st_vec_access(a, i) * st_vec_access(b, i);

    __st_check();
    return re;
}

bool st_vec_equal(st_vector *a, st_vector *b)
{
    if (&a == &b)
        return true;

    if (a->len != b->len)
        return false;

    bool is_equal = true;

    for (size_t i = 0; i < a->len; i++)
        if (st_vec_access(a, i) != st_vec_access(b, i))
            is_equal = false;
    
    return is_equal;
}
