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
void st_vec_rand(st_vector *vec)
{
    double value, min, max;
    srand(time(NULL));

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
