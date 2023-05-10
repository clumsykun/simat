#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "basic.h"

static void __swap(char *a, char *b, size_t len)
{
    char tmp;
    while (len--) {
        tmp = *a;
        *a++ = *b;
        *b++ = tmp;
    }
}

static void __swap_double(double *left, double *right)
{
    double tmp = *left;
    *left = *right;
    *right = tmp;
}

static void __swap_double_p(double **left, double **right)
{
    double tmp = **left;
    **left = **right;
    **right = tmp;
}

/**
 * generate random double number (2 decimals) between
 * integer `min` and `max`, both end are inclusive
 */
static double __rand(int min, int max)
{
    double integer = rand() % (max - min);
    double decimal = (100 *( (double)rand() / RAND_MAX) ) / 100;
    return integer + decimal;
}

static double __scale_value(double value, __st_dtype dtype)
{
    switch (dtype) {

        case __st_bool:
            value = ((int)value == 0 ? 0 : 1);
            break;
        
        case __st_pixel:
            value = (value < 0 ? 0 : (value > 255 ? 255 : (int)value));
            break;

        case __st_int:
            value = (int)value;
            break;

        case __st_double:
            value = (double)value;
            break;

        default:
            __st_raise_dtype_error();
            break;
    }
    return value;
}

/**
 * set random value to vector, random range is intersection of
 * [-RAND_MAX/2, RAND_MAX/2] and support range of data type
 */
void st_vec_rand(const st_vector *vec)
{
    double value, min, max;

    switch (vec->data->dtype) {

        case __st_bool:
            min = 0;
            max = 2;
            break;

        case __st_pixel:
            min = 0;
            max = 255;
            break;

        case __st_int:
            min = -RAND_MAX / 2;
            max = RAND_MAX / 2;
            break;

        case __st_double:
            min = -RAND_MAX / 2;
            max = RAND_MAX / 2;
            break;

        default:
            __st_raise_dtype_error();
    }

    for (size_t i = 0; i < vec->len; i++) {
        value = __scale_value(__rand(min, max), vec->data->dtype);
        st_vec_assign(vec, i, value);
    }
    __st_check();
}

void st_view_rand(st_view *view)
{
    double value, min, max;

    switch (view->dtype) {

        case __st_bool:
            min = 0;
            max = 2;
            break;

        case __st_pixel:
            min = 0;
            max = 255;
            break;

        case __st_int:
            min = -RAND_MAX / 2;
            max = RAND_MAX / 2;
            break;

        case __st_double:
            min = -RAND_MAX / 2;
            max = RAND_MAX / 2;
            break;

        default:
            __st_raise_dtype_error();
    }

    for (size_t i = 0; i < view->len; i++) {
        value = __scale_value(__rand(min, max), view->dtype);
        st_view_assign(view, i, value);
    }
    __st_check();
}

/**
 * choosing the last value as pivot
 * @head: address of the first number of the vector
 * @len: length of the vector
 * @candidate: the candidate position of pivot
 */
static void *__partition(void *start, void *end, __st_dtype dtype, size_t nbyte)
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

static void __quick_sort(void *start, void *end, __st_dtype dtype, size_t nbyte)
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

void st_vec_sort(st_vector *vec)
{
    __quick_sort(
        vec->data->head,
        vec->data->last,
        vec->data->dtype,
        vec->data->nbyte
    );
    __st_check();
}

void st_vec_reverse(st_vector *vec)
{
    void *mid = __st_vec_find_p(vec, vec->len / 2 - 1);
    void *r = vec->data->last;
    void *l;
    size_t nbyte = vec->data->nbyte;

    for (void *l = vec->data->head; l <= mid; l += nbyte, r -= nbyte)
        __swap(l, r, nbyte);
}

void st_mat_rand(const st_matrix *mat)
{
    for (size_t i = 0; i < mat->ncol; i++)
        st_vec_rand(st_mat_access_col(mat, i));

    __st_check();
}
