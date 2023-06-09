#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <immintrin.h>
#include "st_c_copy.h"


static void 
__copy_d64(st_d64 *dst, st_d64 *src, size_t n)
{
    size_t bsize     = st_m_size_d64;
    size_t batches   = n / bsize;
    size_t remainder = n % bsize;

    st_md *ps = (st_md *) src;
    st_md *pd = (st_md *) dst;

    while (batches--)
        st_store_d64((st_d64 *)pd++, st_load_d64((st_d64 *)ps++));

    src = (st_d64 *)ps;
    dst = (st_d64 *)pd;

    while (remainder--)
        *dst++ = *src++;
}

static void 
__copy_i32(st_i32 *dst, st_i32 *src, size_t n)
{
    size_t bsize     = st_m_size_i32;
    size_t batches   = n / bsize;
    size_t remainder = n % bsize;

    st_mi *ps = (st_mi *) src;
    st_mi *pd = (st_mi *) dst;

    while (batches--)
        st_store_i32(pd++, st_load_i32(ps++));

    src = (st_i32 *)ps;
    dst = (st_i32 *)pd;

    while (remainder--)
        *dst++ = *src++;
}

static void 
__copy_u8_bool(st_u8 *dst, st_u8 *src, size_t n)
{
    size_t bsize     = st_m_size_u8;
    size_t batches   = n / bsize;
    size_t remainder = n % bsize;

    st_mi *ps = (st_mi *) src;
    st_mi *pd = (st_mi *) dst;

    while (batches--)
        st_store_i32(pd++, st_load_i32(ps++));

    src = (st_u8 *)ps;
    dst = (st_u8 *)pd;

    while (remainder--)
        *dst++ = *src++;
}

static void
__cast_d64(void *dst, st_d64 *src, size_t n, st_dtype dtype)
{
    switch (dtype) {

        case st_dtype_d64: {
            __copy_d64(dst, src, n*sizeof(st_d64));
            break;
        }

        case st_dtype_i32: {
            st_i32 *head = dst;
            while (n--)
                *head++ = (st_i32)(*src++);

            break;
        }

        case st_dtype_u8: {
            st_u8 *head = dst;
            while (n--)
                *head++ = (st_u8)(*src++);

            break;
        }

        case st_dtype_bool: {
            st_bool *head = dst;
            while (n--)
                *head++ = (st_bool)(*src++);

            break;
        }

        default:
            __st_raise_dtype_error();
    }
}

void
__double_to_pixel(size_t n, st_u8 *dst, st_d64 *src)
{
    while (n--)
        *dst++ = (st_u8)(*src++);
}

void
__double_to_bool(size_t n, st_bool *dst, st_d64 *src)
{
    while (n--)
        *dst++ = (st_bool)(*src++);
}

st_vector *
st_vec_copy(st_vector *vec)
{
    st_vector *copy = __st_new_vector(vec->dtype, vec->len);
    void *dst = copy->data->head;
    void *src = vec->data->head;
    size_t n  = vec->len;

    switch (vec->dtype) {
        case st_dtype_d64:
            __copy_d64(dst, src, n);
            break;

        case st_dtype_i32:
            __copy_i32(dst, src, n);
            break;

        case st_dtype_u8:
            __copy_u8_bool(dst, src, n);
            break;

        case st_dtype_bool:
            __copy_u8_bool(dst, src, n);
            break;

        default:
            __st_raise_dtype_error();
    }

    return copy;
}

st_vector *
st_vec_copy_cast(st_vector *vec, st_dtype dtype)
{
    __st_check_valid(vec);

    if (vec->dtype == dtype)
        return st_vec_copy(vec);

    if (!__st_is_debug && vec->dtype > dtype)
        printf("Warning: conversion may lose significant digits.\n");

    st_vector *copy = __st_new_vector(dtype, vec->len);
    size_t i;
    void *e_vec, *e_cp;
    st_d64 value;

    for __st_iter_vector2(i, e_vec, e_cp, vec, copy) {
        value = __st_access_p(e_vec, vec->dtype);
        __st_assign_p(e_cp, value, copy->dtype);
    }
    return copy;
}
