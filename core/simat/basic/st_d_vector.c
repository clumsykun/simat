#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <immintrin.h>
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

/* =================================================================================================
 * check if vector a and b are equal
 */

st_bool
__is_equal_d64(size_t n, st_d64 *a, st_d64 *b)
{
    st_simd_d128 *pa = (st_simd_d128 *) a;
    st_simd_d128 *pb = (st_simd_d128 *) b;

    size_t batches = n / 2;
    size_t remainder = n % 2;
    st_bool is_equal = false;

    st_simd_d128 pk_sum_diff = {0, 0};
    double sum_diff[2];

    while (batches--) {
        st_simd_d128 pk_a = st_access_d128((st_d64 *)pa++);
        st_simd_d128 pk_b = st_access_d128((st_d64 *)pb++);
        st_simd_d128 pk_diff = _mm_xor_pd(pk_a, pk_b);
        pk_sum_diff = _mm_or_pd(pk_sum_diff, pk_diff);

        /* check result every 100 loops */
        if (batches%100 == 0) {
            st_assign_d128(sum_diff, pk_sum_diff);

            if ((sum_diff[0]!=0)||(sum_diff[1]!=0))
                return false;
        }
    }

    a = (st_d64 *)pa;
    b = (st_d64 *)pb;

    /* check the remainder of element */
    while (remainder--)
        if ((*a++) != (*b++))
            return false;
    
    return true;
}

/* Return true if a equals b. */
st_bool
st_vec_is_equal(st_vector *a, st_vector *b)
{
    if (&a == &b)
        return true;

    if (a->len != b->len)
        return false;

    if (a->dtype != b->dtype)
        return false;

    // for (size_t i = 0; i < a->len; i++)
    // if (st_vec_access(a, i) != st_vec_access(b, i))
    //     is_equal = false;

    switch (a->dtype) {

        case st_dtype_d64:
            return __is_equal_d64(a->len, a->data->head, b->data->head);

        default:
            return true;
    }
}
