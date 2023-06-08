#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "st_d_vector.h"

/* scale the vector to make sure that its max value and min value match `max` and `min`. */
void
st_vec_scale(st_vector *vec, st_d64 min, st_d64 max)
{
    if st_is_bool(vec) /* do noting */
        return;

    st_d64 vec_min = st_vec_min(vec);
    st_d64 scale = st_vec_max(vec) - vec_min;
    st_d64 target_scale = max - min;
    st_d64 scaled;
    void *p;

    for __st_iter_data(p, vec->data) {
        scaled = min + (__st_access_p(p, vec->dtype) - vec_min) * target_scale / scale;
        __st_assign_p(p, scaled, vec->dtype);
    }
}

void
st_vec_sub_scalar(st_vector *vec, st_d64 value)
{
    void *p;
    for __st_iter_data(p, vec->data)
        __st_assign_p(p, __st_access_p(p, vec->dtype)-value, vec->dtype);
}

void
st_vec_mul_scalar(st_vector *vec, st_d64 value)
{
    void *p;
    for __st_iter_data(p, vec->data)
        __st_assign_p(p, __st_access_p(p, vec->dtype)*value, vec->dtype);
}

/* implement vector dot production a·b, return result */
st_d64
st_vec_dot(st_vector *a, st_vector *b)
{
    st_check_vec_len(a, b->len);

    st_d64 re = 0;
    void *pa, *pb;
    size_t i;
    for __st_iter_vector2(i, pa, pb, a, b)
        re += __st_access_p(pa, a->dtype) * __st_access_p(pb, b->dtype);

    return re;
}

/* Return true if a equals b. */
st_bool
st_vec_equal(st_vector *a, st_vector *b)
{
    if (&a == &b)
        return true;

    if (a->len != b->len)
        return false;

    st_bool is_equal = true;

    for (size_t i = 0; i < a->len; i++)
        if (st_vec_access(a, i) != st_vec_access(b, i))
            is_equal = false;
    
    return is_equal;
}
