#include <stdbool.h>
#include <stdlib.h>
#include "copy.h"


void
__double_copy(void *dst, double *src, size_t n, st_dtype dtype)
{
    switch (dtype) {

        case st_dtype_d64: {
            memcpy(dst, src, n*sizeof(double));
            break;
        }

        case st_dtype_u8: {
            unsigned int *head = dst;
            while (n--)
                *head++ = (unsigned int)(*src++);

            break;
        }

        case st_dtype_bool: {
            bool *head = dst;
            while (n--)
                *head++ = (bool)(*src++);

            break;
        }

        default:
            __st_raise_dtype_error();
    }
}

void
__double_to_pixel(size_t n, unsigned char *dst, double *src)
{
    while (n--)
        *dst++ = (unsigned char)(*src++);
}

void
__double_to_bool(size_t n, bool *dst, double *src)
{
    while (n--)
        *dst++ = (bool)(*src++);
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
    double value;

    for __st_iter_vector2(i, e_vec, e_cp, vec, copy) {
        value = __st_access_p(e_vec, vec->dtype);
        __st_assign_p(e_cp, value, copy->dtype);
    }
    return copy;
}
