#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "dtypes.h"
#include "tools.h"

static Vector *__create_vector(enum dtype dtype, unsigned int len)
{
    Vector *vec = malloc(sizeof(Vector));
    char *p = malloc(len * __sizeof(dtype));
    Vector _vec = {
        dtype,
        p,
        p+(len-1) * __sizeof(dtype),
        __sizeof(dtype),
        len,
    };
    memcpy(vec, &_vec, sizeof(Vector));
    return vec;
}

Vector *create_bool_vector(unsigned int len)
{
    return __create_vector(dtype_bool, len);
}

Vector *create_pixel_vector(unsigned int len)
{
    return __create_vector(dtype_pixel, len);
}

Vector *create_int_vector(unsigned int len)
{
    return __create_vector(dtype_int, len);
}

Vector *create_double_vector(unsigned int len)
{
    return __create_vector(dtype_double, len);
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

        case dtype_bool: {
            printf("BoolVector([\n");
            char c;
            for (char *p = vec->head; p < vec->bott; p += vec->byte, i++) {
                c = (access(vec->dtype, p) == false ? '-' : '+');
                printf("(%c), ", c);

                if ((i + 1) % 10 == 0)
                    printf("\n");
            }

            printf("(%c)])\n", (access(vec->dtype, vec->bott) == false ? '-' : '+'));
            break;
        }

        case dtype_pixel: {
            printf("PixelVector([\n");
            for (char *p = vec->head; p < vec->bott; p += vec->byte, i++) {
                printf("(%3d), ", (int)access(vec->dtype, p));

                if ((i + 1) % 10 == 0)
                    printf("\n");
            }
            printf("(%3d)])\n", (int)access(vec->dtype, vec->bott));
            break;
        }

        case dtype_int: {
            printf("IntVector([\n");
            for (char *p = vec->head; p < vec->bott; p += vec->byte, i++) {
                printf("%10d, ", (int)access(vec->dtype, p));

                if ((i + 1) % 5 == 0)
                    printf("\n");
            };
            printf("%10d])\n", (int)access(vec->dtype, vec->bott));
            break;
        }

        case dtype_double: {
            printf("DoubleVector([\n");
            for (char *p = vec->head; p < vec->bott; p += vec->byte, i++) {
                printf("%10.2f, ", access(vec->dtype, p));

                if ((i + 1) % 5 == 0)
                    printf("\n");
            }
            printf("%10.2f])\n", access(vec->dtype, vec->bott));
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

        case dtype_bool: {
            for (char *p = vec->head; p <= vec->bott; p += vec->byte)
                *p = (bool)__rand_int(0, 1);

            break;
        }

        case dtype_pixel: {
            for (char *p = vec->head; p <= vec->bott; p += vec->byte)
                *p = (pixel) __rand_int(0, 255);

            break;
        }

        case dtype_int: {
            for (char *p = vec->head; p <= vec->bott; p += vec->byte)
                dassign(p, __rand_int(-RAND_MAX/2, RAND_MAX/2), vec->dtype);

            break;
        }

        case dtype_double: {
            for (char *p = vec->head; p <= vec->bott; p += vec->byte)
                dassign(p, __rand_double(-100/2, 100/2), vec->dtype);

            break;
        }
        
        default:
            __is_error = true;
    }
    __check();
}

double vector_min(Vector *vec)
{
    char *p = vec->head;
    double min = access(vec->dtype, p);
    for (size_t i = 0; i < vec->len; i++, p += vec->byte)
        min = (min <= access(vec->dtype, p) ? min : access(vec->dtype, p));

    __check();
    return min;
}

double vector_max(Vector *vec)
{
    char *p = vec->head;
    double max = access(vec->dtype, p);
    for (size_t i = 0; i < vec->len; i++, p += vec->byte)
        max = (max >= access(vec->dtype, p) ? max : access(vec->dtype, p));

    __check();
    return max;
}

/* scale the vector to make sure that its max value and min value match param max and min. */
void vector_scale(Vector *vec, double min, double max)
{
    double vec_min = vector_min(vec);
    double scale = vector_max(vec) - vec_min;
    double target_scale = max - min;

    for (char *p = vec->head; p <= vec->bott; p += vec->byte)
        dassign(
            p,
            min + (access(vec->dtype, p) - vec_min) * target_scale / scale,
            vec->dtype
        );

    __check();
}

void vector_reverse(Vector *vec)
{
    char *mid = vec->head + (vec->len/2)*(vec->byte);
    char *r = vec->bott;
    for (char *l = vec->head; l <= mid; l += vec->byte, r -= vec->byte)
        __swap(l, r, vec->byte);
}

/**
 * choosing the last value as pivot
 * @head: address of the first number of the vector
 * @len: length of the vector
 * @candidate: the candidate position of pivot
 */
char *__partition(enum dtype dtype, char *start, char *end)
{
    size_t size = __sizeof(dtype);
    double pivot = access(dtype, end);
    char *candidate = start - size;

    for (char *p = start; p < end; p+=size) {
        if (access(dtype, p) < pivot) {

            candidate += size;
            __swap(candidate, p, size);
        }
    }

    candidate += size;
    __swap(candidate, end, size);
    return candidate;
}

static void __quick_sort(enum dtype dtype, char *start, char *end)
{
    if (start < end) {
        /**
         * [p, p + len*size] -->
         * [p, p + pi*size], [p + (pi+1)*size, p+len*size]
         */
        char* p = __partition(dtype, start, end);
        __quick_sort(dtype, start, p-__sizeof(dtype));
        __quick_sort(dtype, p+__sizeof(dtype), end);
    }
}

void vector_sort(Vector *vec, enum order order)
{
    __quick_sort(vec->dtype, vec->head, vec->bott);
    if (order == descend) {
        vector_reverse(vec);
    }
    __check();
}
