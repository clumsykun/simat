#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dtypes.h"

static size_t __byte_of(__st_dtype dtype)
{
    size_t nbyte;
    switch (dtype) {

        case __st_bool:
            nbyte = sizeof(st_bool);
            break;

        case __st_pixel:
            nbyte = sizeof(st_pixel);
            break;

        case __st_int:
            nbyte = sizeof(st_int);
            break;

        case __st_double:
            nbyte = sizeof(st_double);
            break;

        default:
            nbyte = 0;
            __st_raise_dtype_error();
    }

    return nbyte;
}

static st_vector *__st_new_vector(__st_dtype dtype, size_t len)
{
    st_vector *vec;
    __st_data *data;
    void *head;
    size_t nbyte = __byte_of(dtype);

    vec = malloc(sizeof(st_vector));
    data = malloc(sizeof(__st_data));
    head = malloc(len * nbyte);

    __st_data _data = {
        head,                     /* head */
        head + (len - 1) * nbyte, /* last */
        dtype,                    /* dtype */
        nbyte,                    /* nbyte */
        len,                      /* size */
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

            printf("%4.2f])\n", (double)st_vec_access(vec, vec->len-1));
            break;
        }

        default:
            __st_raise_dtype_error();
            break;
    }
    __st_check();
}

void st_vec_assign_all(st_vector *vec, double value)
{
    void *p;

    for __st_iter_data(p, vec->data)
        __st_assign_p(p, value, vec->data->dtype);

    __st_check();
}

static st_matrix *__st_new_matrix(__st_dtype dtype, size_t nrow, size_t ncol)
{
    st_matrix *mat;
    __st_data *data;
    void *head;
    size_t nbyte = __byte_of(dtype);

    mat = malloc(sizeof(st_matrix));
    data = malloc(sizeof(__st_data));
    head = malloc(nrow * ncol * nbyte);

    __st_data _data = {
        head,                             /* head */
        head + (nrow * ncol - 1) * nbyte, /* last */
        dtype,                            /* dtype */
        nbyte,                            /* nbyte */
        nrow * ncol,                      /* size */
    };

    st_matrix _mat = {
        data,
        nrow,
        ncol,
    };
    memcpy(data, &_data, sizeof(__st_data));
    memcpy(mat, &_mat, sizeof(st_matrix));
    return mat;
}

st_matrix *st_new_matrix(size_t nrow, size_t ncol)
{
    return __st_new_matrix(__st_double, nrow, ncol);
}

#define __st_mat_find_p(mat, irow, icol) \
    (mat->data->head + ((size_t)(irow)+(size_t)(icol)*(mat->nrow))*mat->data->nbyte)

#define st_access_mat(mat, irow, icol) \
    __st_access_p(__st_mat_find_p(mat, irow, icol), mat->data->dtype)

void st_mat_display(st_matrix *mat)
{
    // double(*head)[mat->nrow] = (double(*)[mat->nrow])mat->head;
    printf("Matrix([\n");

    for (size_t i = 0; i < mat->nrow; i++) {
            for (size_t j = 0; j < mat->ncol; j++) {

                if (i * j == (mat->nrow-1) * (mat->ncol-1))
                    printf("%.2f])", st_access_mat(mat, i, j));
                else
                    printf("%.2f,  ", st_access_mat(mat, i, j));
            }
            printf("\n");
    }
}
