#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "dtypes.h"
#include "tools.h"

static Vector *__create_vector(enum st_dtype dtype, unsigned int len)
{
    Vector *vec = malloc(sizeof(Vector));
    char *p = malloc(len * st_byteof(dtype));
    Vector _vec = {
        dtype,
        p,
        p+(len-1) * st_byteof(dtype),
        st_byteof(dtype),
        len,
    };
    memcpy(vec, &_vec, sizeof(Vector));
    return vec;
}

Vector *create_bool_vector(unsigned int len)
{
    return __create_vector(st_bool, len);
}

Vector *create_pixel_vector(unsigned int len)
{
    return __create_vector(st_pixel, len);
}

Vector *create_int_vector(unsigned int len)
{
    return __create_vector(st_int, len);
}

Vector *create_double_vector(unsigned int len)
{
    return __create_vector(st_double, len);
}

void free_vector(Vector *vec)
{
    __std_free(vec->head);
    __std_free(vec);
}

void vector_display(Vector *vec)
{
    size_t i = 0;
    switch (vec->dtype) {

        case st_bool: {
            printf("BoolVector([\n");
            char c;

            for st_iter(vec) {
                c = (st_access(vec->dtype, p) == false ? '-' : '+');
                printf("(%c), ", c);

                if ((i++ + 1) % 10 == 0)
                    printf("\n");
            }

            printf("(%c)])\n", (st_access(vec->dtype, vec->last) == false ? '-' : '+'));
            break;
        }

        case st_pixel: {
            printf("PixelVector([\n");

            for st_iter(vec) {
                printf("(%3d), ", (int)st_access(vec->dtype, p));

                if ((i++ + 1) % 10 == 0)
                    printf("\n");
            }
            printf("(%3d)])\n", (int)st_access(vec->dtype, vec->last));
            break;
        }

        case st_int: {
            printf("IntVector([\n");

            for st_iter(vec) {
                printf("%10d, ", (int)st_access(vec->dtype, p));

                if ((i++ + 1) % 5 == 0)
                    printf("\n");
            };
            printf("%10d])\n", (int)st_access(vec->dtype, vec->last));
            break;
        }

        case st_double: {
            printf("DoubleVector([\n");

            for st_iter(vec) {
                printf("%10.2f, ", st_access(vec->dtype, p));

                if ((i++ + 1) % 5 == 0)
                    printf("\n");
            }
            printf("%10.2f])\n", st_access(vec->dtype, vec->last));
            break;
        }

        default:
            __is_error = true;
    }
    __check();
}

/* set random double value to vector. */
void vector_set_rand(Vector *vec)
{
    srand(time(NULL));
    switch (vec->dtype) {

        case st_bool: {
            for st_iter(vec)
                *p = (bool)__rand_int(0, 1);

            break;
        }

        case st_pixel: {
            for st_iter(vec)
                *p = (unsigned char) __rand_int(0, 255);

            break;
        }

        case st_int: {
            for st_iter(vec)
                dassign(p, __rand_int(-RAND_MAX/2, RAND_MAX/2), vec->dtype);

            break;
        }

        case st_double: {
            for st_iter(vec)
                dassign(p, __rand_double(-RAND_MAX/2, RAND_MAX/2), vec->dtype);

            break;
        }
        
        default:
            __is_error = true;
    }
    __check();
}

double vector_min(Vector *vec)
{
    double min = st_access(vec->dtype, vec->head);
    for st_iter(vec)
        min = (min <= st_access(vec->dtype, p) ? min : st_access(vec->dtype, p));

    __check();
    return min;
}

double vector_max(Vector *vec)
{
    double max = st_access(vec->dtype, vec->head);
    for st_iter(vec)
        max = (max >= st_access(vec->dtype, p) ? max : st_access(vec->dtype, p));

    __check();
    return max;
}

/* scale the vector to make sure that its max value and min value match param max and min. */
void vector_scale(Vector *vec, double min, double max)
{
    double vec_min = vector_min(vec);
    double scale = vector_max(vec) - vec_min;
    double target_scale = max - min;

    for st_iter(vec)
        dassign(
            p,
            min + (st_access(vec->dtype, p) - vec_min) * target_scale / scale,
            vec->dtype
        );

    __check();
}

void vector_reverse(Vector *vec)
{
    char *mid = vec->head + (vec->len/2)*(vec->byte);
    char *r = vec->last;
    for (char *l = vec->head; l <= mid; l += vec->byte, r -= vec->byte)
        __swap(l, r, vec->byte);
}

/**
 * choosing the last value as pivot
 * @head: address of the first number of the vector
 * @len: length of the vector
 * @candidate: the candidate position of pivot
 */
static char *__partition(enum st_dtype dtype, char *start, char *end)
{
    size_t size = st_byteof(dtype);
    double pivot = st_access(dtype, end);
    char *candidate = start - size;

    for (char *p = start; p < end; p+=size) {
        if (st_access(dtype, p) < pivot) {

            candidate += size;
            __swap(candidate, p, size);
        }
    }

    candidate += size;
    __swap(candidate, end, size);
    return candidate;
}

static void __quick_sort(enum st_dtype dtype, char *start, char *end)
{
    if (start < end) {
        /**
         * [p, p + len*size] -->
         * [p, p + pi*size], [p + (pi+1)*size, p+len*size]
         */
        char* p = __partition(dtype, start, end);
        __quick_sort(dtype, start, p-st_byteof(dtype));
        __quick_sort(dtype, p+st_byteof(dtype), end);
    }
}

void vector_sort(Vector *vec, enum order order)
{
    __quick_sort(vec->dtype, vec->head, vec->last);
    if (order == descend) {
        vector_reverse(vec);
    }
    __check();
}
