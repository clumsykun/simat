#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "st_tools.h"

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
__swap_double(double *left, double *right)
{
    double tmp = *left;
    *left = *right;
    *right = tmp;
}

/**
 * generate random double number (2 decimals) between
 * integer `min` and `max`, both end are inclusive
 */
static double
__rand(int min, int max)
{
    double integer = rand() % (max - min);
    double decimal = (100 *( (double)rand() / RAND_MAX) ) / 100;
    return integer + decimal;
}

static double
__scale_value(double value, st_dtype dtype)
{
    switch (dtype) {

        case st_dtype_bool:
            value = ((int)value == 0 ? 0 : 1);
            break;
        
        case st_dtype_u8:
            value = (value < 0 ? 0 : (value > 255 ? 255 : (int)value));
            break;

        case st_dtype_i32:
            value = (int)value;
            break;

        case st_dtype_d64:
            value = (double)value;
            break;

        default:
            __st_raise_dtype_error();
            break;
    }
    return value;
}

double
st_precise(double x, size_t ndigits)
{
    ndigits = (ndigits >= 15 ? 15 : ndigits);  /* max precision of double */
    return trunc(x*pow(10, ndigits))/pow(10, ndigits);
}

/**
 * set random value to vector, random range is intersection of
 * [-RAND_MAX/2, RAND_MAX/2] and support range of data type
 */
void
st_vec_rand(const st_vector *vec)
{
    double value, min, max;

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
    double pivot = __st_access_p(end, dtype);
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
    double value, min, max;

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
    double pivot = __st_access_p(*end, dtype);
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
        __st_byteof(view->dtype)
    );
}

void
st_view_reverse(st_view *view)
{
    void **l = view->head-1;
    void **r = view->last+1;
    size_t step = view->len / 2;

    while (step--)
        __swap(*++l, *--r, __st_byteof(view->dtype));
}
