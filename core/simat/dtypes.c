#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dtypes.h"

static st_vector *__st_new_vector(__st_dtype st_dtype, size_t len)
{
    st_vector *vec;
    __st_data *data;
    void *head;
    size_t byte;

    switch (st_dtype) {

        case __st_bool:
            byte = sizeof(st_bool);
            break;

        case __st_pixel:
            byte = sizeof(st_pixel);
            break;

        case __st_int:
            byte = sizeof(st_int);
            break;

        case __st_double:
            byte = sizeof(st_double);
            break;

        default:
            return NULL;
    }

    vec = malloc(sizeof(st_vector));
    data = malloc(sizeof(__st_data));
    head = malloc(len * byte);

    __st_data _data = {
        head,                    /* head */
        head + (len - 1) * byte, /* last */
        byte,                    /* byte */
        len,                     /* len */
        st_dtype,                /* dtype */
    };

    st_vector _vec = {
        data, /* data */
        len,  /* len */
    };

    memcpy(data, &_data, sizeof(__st_data));
    memcpy(vec, &_vec, sizeof(st_vector));
    return vec;
}

st_vector *st_new_bool_vector(size_t len)
{
    return __st_new_vector(__st_bool, len);
}

st_vector *st_new_pixel_vector(size_t len)
{
    return __st_new_vector(__st_pixel, len);
}

st_vector *st_new_int_vector(size_t len)
{
    return __st_new_vector(__st_int, len);
}

st_vector *st_new_double_vector(size_t len)
{
    return __st_new_vector(__st_double, len);
}

/* the standard way to free memory */
static void __std_free(void *ptr)
{
    free(ptr);
    ptr = NULL;
}

void st_free_vector(st_vector *vec)
{
    __std_free(vec->data->head);
    __std_free(vec->data);
    __std_free(vec);
}

void st_vec_display(st_vector *vec)
{
    void *p;
    char c;
    switch (vec->data->dtype) {

        case __st_bool: {
            printf("BoolVector([\n");

            for (size_t i = 0; i <= vec->len - 2; i++) {
                c = (st_vec_access(vec, i) == false ? '-' : '+');
                printf("(%c), ", c);

                if ((i + 1) % 10 == 0)
                    printf("\n");
            }

            printf("(%c)])\n", (st_vec_access(vec, vec->len-1) == false ? '-' : '+'));
            break;
        }

        case __st_pixel: {
            printf("PixelVector([\n");

            for (size_t i = 0; i <= vec->len - 2; i++) {
                printf("(%3d), ", (int)st_vec_access(vec, i));

                if ((i + 1) % 10 == 0)
                    printf("\n");
            }

            printf("(%3d)])\n", (int)st_vec_access(vec, vec->len-1));
            break;
        }

        case __st_int: {
            printf("IntVector([\n");

            for (size_t i = 0; i <= vec->len - 2; i++) {
                printf("%5d, ", (int)st_vec_access(vec, i));

                if ((i + 1) % 10 == 0)
                    printf("\n");
            }

            printf("%5d])\n", (int)st_vec_access(vec, vec->len-1));
            break;
        }

        case __st_double: {
            printf("Vector([\n");

            for (size_t i = 0; i <= vec->len - 2; i++) {
                printf("%4.2f, ", (double)st_vec_access(vec, i));

                if ((i + 1) % 10 == 0)
                    printf("\n");
            }

            printf("%4.2f])\n", (int)st_vec_access(vec, vec->len-1));
            break;
        }

        default:
            __st_raise_dtype_error();
            break;
    }
    __st_check();
}

static double __scale_assign_value(double value, __st_dtype dtype)
{
    switch (dtype) {

        case __st_bool:
            value = (value == 0 ? 0 : 1);
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

void st_vec_assign_all(st_vector *vec, double value)
{
    void *p;
    value = __scale_assign_value(value, vec->data->dtype);

    for __st_iter_data(p, vec->data)
        __st_assign_p(p, value, vec->data->dtype);

    __st_check();
}

