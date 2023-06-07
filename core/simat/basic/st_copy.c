#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "st_copy.h"


void
__double_copy(void *dst, st_d64 *src, size_t n, st_dtype dtype)
{
    switch (dtype) {

        case st_dtype_d64: {
            memcpy(dst, src, n*sizeof(st_d64));
            break;
        }

        case st_dtype_u8: {
            unsigned st_i32 *head = dst;
            while (n--)
                *head++ = (unsigned st_i32)(*src++);

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
    memcpy(
        copy->data->head,
        vec->data->head,
        vec->data->nbyte * vec->data->size);

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
