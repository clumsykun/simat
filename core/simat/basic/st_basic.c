#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "st_basic.h"

static void
__swap(char *a, char *b, size_t len)
{
    char tmp;
    while (len--) {
        tmp = *a;
        *a++ = *b;
        *b++ = tmp;
    }
}

static void
__swap_double(st_d64 *left, st_d64 *right)
{
    st_d64 tmp = *left;
    *left = *right;
    *right = tmp;
}

/**
 * generate random st_d64 number (2 decimals) between
 * integer `min` and `max`, both end are inclusive
 */
static st_d64
__rand(st_i32 min, st_i32 max)
{
    st_d64 integer = rand() % (max - min);
    st_d64 decimal = (100 *( (st_d64)rand() / RAND_MAX) ) / 100;
    return integer + decimal;
}

static st_d64
__scale_value(st_d64 value, st_dtype dtype)
{
    switch (dtype) {

        case st_dtype_bool:
            value = ((st_i32)value == 0 ? 0 : 1);
            break;
        
        case st_dtype_u8:
            value = (value < 0 ? 0 : (value > 255 ? 255 : (st_i32)value));
            break;

        case st_dtype_i32:
            value = (st_i32)value;
            break;

        case st_dtype_d64:
            value = (st_d64)value;
            break;

        default:
            __st_raise_dtype_error();
            break;
    }
    return value;
}

st_d64
st_precise(st_d64 x, size_t ndigits)
{
    ndigits = (ndigits >= 15 ? 15 : ndigits);  /* max precision of st_d64 */
    return trunc(x*pow(10, ndigits))/pow(10, ndigits);
}

/**
 * set random value to vector, random range is intersection of
 * [-RAND_MAX/2, RAND_MAX/2] and support range of data type
 */
void
st_vec_rand(const st_vector *vec)
{
    st_d64 value, min, max;

    switch (vec->dtype) {

        case st_dtype_bool:
            min = 0;
            max = 2;
            break;

        case st_dtype_u8:
            min = 0;
            max = 255;
            break;

        case st_dtype_i32:
            min = -RAND_MAX / 2;
            max = RAND_MAX / 2;
            break;

        case st_dtype_d64:
            min = -RAND_MAX / 2;
            max = RAND_MAX / 2;
            break;

        default:
            __st_raise_dtype_error();
    }

    for (size_t i = 0; i < vec->len; i++) {
        value = __scale_value(__rand(min, max), vec->dtype);
        st_vec_assign(vec, i, value);
    }
}

/**
 * choosing the last value as pivot
 * @head: address of the first number of the vector
 * @len: length of the vector
 * @candidate: the candidate position of pivot
 */
static void *
__partition(void *start, void *end, st_dtype dtype, size_t nbyte)
{
    st_d64 pivot = __st_access_p(end, dtype);
    void *candidate = start - nbyte;

   for (void *p = start; p < end; p+=nbyte) {
        if (__st_access_p(p, dtype) < pivot) {

            candidate += nbyte;
            __swap(candidate, p, nbyte);
        }
    }

    candidate += nbyte;
    __swap(candidate, end, nbyte);
    return candidate;
}

static void
__quick_sort(void *start, void *end, st_dtype dtype, size_t nbyte)
{
    if (start < end) {
        /**
         * [p, p + len*size] -->
         * [p, p + pi*size], [p + (pi+1)*size, p+len*size]
         */
        char *p = __partition(start, end, dtype, nbyte);
        __quick_sort(start, p - nbyte, dtype, nbyte);
        __quick_sort(p + nbyte, end, dtype, nbyte);
    }
}

void
st_vec_sort(st_vector *vec)
{
    __quick_sort(
        vec->data->head,
        vec->data->last,
        vec->dtype,
        vec->data->nbyte
    );
}

void
st_vec_reverse(st_vector *vec)
{
    size_t nbyte = vec->data->nbyte;
    void *l = vec->data->head-nbyte;
    void *r = vec->data->last+nbyte;
    size_t step = vec->len / 2;

    while (step--)
        __swap(l+=nbyte, r-=nbyte, nbyte);
}

void
st_mat_rand(const st_matrix *mat)
{
    for (size_t i = 0; i < mat->nrow; i++)
        st_vec_rand(__st_mat_access_row(mat, i));
}

void
st_view_rand(st_view *view)
{
    st_d64 value, min, max;

    switch (view->dtype) {

        case st_dtype_bool:
            min = 0;
            max = 2;
            break;

        case st_dtype_u8:
            min = 0;
            max = 255;
            break;

        case st_dtype_i32:
            min = -RAND_MAX / 2;
            max = RAND_MAX / 2;
            break;

        case st_dtype_d64:
            min = -RAND_MAX / 2;
            max = RAND_MAX / 2;
            break;

        default:
            __st_raise_dtype_error();
    }

    for (size_t i = 0; i < view->len; i++) {
        value = __scale_value(__rand(min, max), view->dtype);
        __st_view_assign(view, i, value);
    }
}

static void **
__partition_p(void **start, void **end, st_dtype dtype, size_t nbyte)
{
    st_d64 pivot = __st_access_p(*end, dtype);
    void **candidate = start -1;

   for (void **p = start; p < end; p++) {
        if (__st_access_p(*p, dtype) < pivot) {

            candidate++;
            __swap(*candidate, *p, nbyte);
        }
    }

    candidate ++;
    __swap(*candidate, *end, nbyte);
    return candidate;
}

static void
__quick_sort_view(void **start, void **end, st_dtype dtype, size_t nbyte)
{
    if (start < end) {
        /**
         * [p, p + len*size] -->
         * [p, p + pi*size], [p + (pi+1)*size, p+len*size]
         */
        void **p = __partition_p(start, end, dtype, nbyte);
        __quick_sort_view(start, p - 1, dtype, nbyte);
        __quick_sort_view(p + 1, end, dtype, nbyte);
    }
}

void
st_view_sort(st_view *view)
{
    __quick_sort_view(
        view->head,
        view->last,
        view->dtype,
        view->nbyte
    );
}

void
st_view_reverse(st_view *view)
{
    void **l = view->head-1;
    void **r = view->last+1;
    size_t step = view->len / 2;

    while (step--)
        __swap(*++l, *--r, view->nbyte);
}
