#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "vector.h"
#include "cblas.h"

st_vector *
st_vec_copy_cast(st_vector *vec, __st_dtype dtype)
{
    if (!__st_is_debug && vec->dtype > dtype) {

        if (dtype == st_pixel)
            printf("Warning: conversion may lose significant digits, "
                   "value will be trimmed to pixel of range [0,255].\n");
        else
            printf("Warning: conversion may lose significant digits.\n");
    }

    st_vector *copy = __st_new_vector(dtype, vec->len);
    size_t i;
    void *e_vec, *e_cp;
    double value;

    for __st_iter_vector2(i, e_vec, e_cp, vec, copy) {
        value = __st_access_p(e_vec, vec->dtype);
        __st_assign_p(e_cp, value, copy->dtype);
    }
    return copy;
}

/* scale the vector to make sure that its max value and min value match `max` and `min`. */
void
st_vec_scale(st_vector *vec, double min, double max)
{
    if st_is_bool(vec) /* do noting */
        return;

    double vec_min = st_vec_min(vec);
    double scale = st_vec_max(vec) - vec_min;
    double target_scale = max - min;
    double scaled;
    void *p;

    for __st_iter_data(p, vec->data) {
        scaled = min + (__st_access_p(p, vec->dtype) - vec_min) * target_scale / scale;
        __st_assign_p(p, scaled, vec->dtype);
    }
}

void
st_vec_sub_scalar(st_vector *vec, double value)
{
    void *p;
    for __st_iter_data(p, vec->data)
        __st_assign_p(p, __st_access_p(p, vec->dtype)-value, vec->dtype);
}

void
st_vec_mul_scalar(st_vector *vec, double value)
{
    void *p;
    for __st_iter_data(p, vec->data)
        __st_assign_p(p, __st_access_p(p, vec->dtype)*value, vec->dtype);
}

/* implement vector dot production a·b, return result */
double
st_vec_dot(st_vector *a, st_vector *b)
{
    st_check_vec_len(a, b->len);

    double re = 0;
    void *pa, *pb;
    size_t i;
    for __st_iter_vector2(i, pa, pb, a, b)
        re += __st_access_p(pa, a->dtype) * __st_access_p(pb, b->dtype);

    return re;
}

bool
st_vec_equal(st_vector *a, st_vector *b)
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
