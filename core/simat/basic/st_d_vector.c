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
st_decimal
st_vec_dot(st_vector *a, st_vector *b)
{
    if (st_check_vec_len(a, b->len))
        __st_raise_length_error();

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

#define n_loops 100

static st_bool
__is_equal_d64(size_t n, st_d64 *a, st_d64 *b)
{
    size_t bsize     = st_m_size_d64;
    size_t batches   = n / bsize;
    size_t remainder = n % bsize;
    st_md *pa = (st_md *) a;
    st_md *pb = (st_md *) b;

    st_md pk_diff = st_m_zero_d();
    st_d64 diff[bsize];

    while (batches--) {
        st_md pk_a = st_load_d64((st_d64 *)pa++);
        st_md pk_b = st_load_d64((st_d64 *)pb++);
        st_md tmp = st_m_xor_d(pk_a, pk_b);
        pk_diff = st_m_or_d(pk_diff, tmp);

        if (batches % n_loops == 0) {
            st_store_d64(diff, pk_diff);

            for (size_t i = 0; i < bsize; i++)
                if (diff[i] != 0)
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

static st_bool
__is_equal_i32(size_t n, st_i32 *a, st_i32 *b)
{
    size_t bsize     = st_m_size_i32;
    size_t batches   = n / bsize;
    size_t remainder = n % bsize;
    st_mi *pa = (st_mi *) a;
    st_mi *pb = (st_mi *) b;

    st_mi pk_diff = st_m_zero_i();
    st_i32 diff[bsize];

    while (batches--) {
        st_mi pk_a = st_load_i32(pa++);
        st_mi pk_b = st_load_i32(pb++);
        st_mi tmp = st_m_xor_i(pk_a, pk_b);
        pk_diff = st_m_or_i(pk_diff, tmp);

        if (batches % n_loops == 0) {
            st_store_i32((st_mi *)diff, pk_diff);

            for (size_t i = 0; i < bsize; i++)
                if (diff[i] != 0)
                    return false;            
        }
    }

    a = (st_i32 *)pa;
    b = (st_i32 *)pb;

    /* check the remainder of element */
    while (remainder--)
        if ((*a++) != (*b++))
            return false;

    return true;
}

static st_bool
__is_equal_u8_bool(size_t n, st_u8 *a, st_u8 *b)
{
    size_t bsize     = st_m_size_u8;
    size_t batches   = n / bsize;
    size_t remainder = n % bsize;
    st_mi *pa = (st_mi *) a;
    st_mi *pb = (st_mi *) b;

    st_mi pk_diff = st_m_zero_i();
    st_u8 diff[bsize];

    while (batches--) {
        st_mi pk_a = st_load_i32(pa++);
        st_mi pk_b = st_load_i32(pb++);
        st_mi tmp = st_m_xor_i(pk_a, pk_b);
        pk_diff = st_m_or_i(pk_diff, tmp);

        if (batches % n_loops == 0) {
            st_store_i32((st_mi *)diff, pk_diff);

            for (size_t i = 0; i < bsize; i++)
                if (diff[i] != 0)
                    return false;            
        }
    }

    a = (st_u8 *)pa;
    b = (st_u8 *)pb;

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

    switch (a->dtype) {

        case st_dtype_d64:
            return __is_equal_d64(a->len, a->data->head, b->data->head);

        case st_dtype_i32:
            return __is_equal_i32(a->len, a->data->head, b->data->head);

        case st_dtype_u8:
            return __is_equal_u8_bool(a->len, a->data->head, b->data->head);

        case st_dtype_bool:
            return __is_equal_u8_bool(a->len, a->data->head, b->data->head);

        default:
            __st_raise_dtype_error();
    }
}
