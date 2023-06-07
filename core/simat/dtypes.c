#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dtypes.h"

#define __st_temp_str(is_temp) \
    ((is_temp) == true ? "TEMP" : "    ")

#define __st_dtype_str(dtype)           \
    ((dtype) == st_double             \
        ? "Double"                      \
        : ((dtype) == st_int          \
            ? "Int"                     \
            : ((dtype) == st_pixel    \
                ? "Pixel"               \
                : ((dtype) == st_bool \
                    ? "Bool"            \
                    : "invalid"))))

/* the standard way to free memory */
static void
__free(void *p)
{
    free((void *)p);
    p = NULL;
}

static void
__free_data(const __st_data *data)
{
    __st_data *p = (__st_data *) data;
    memset(p->head, 0, p->size*p->nbyte);
    __free(p->head);
    memset(p, 0, sizeof(__st_data));
    __free(p);
}

static void
__free_vector(void *vector)
{
    st_vector *vec = vector;
    __free_data(vec->data);
    memset(vec, 0, sizeof(st_vector));
    __free(vec);
}

static void
__free_matrix(void *matrix)
{
    st_matrix *mat = matrix;
    void *p;

    __free_data(mat->data);

    for (size_t i = 0; i < mat->nrow; i++) {
        memset(__st_mat_access_row(mat, i)->data, 0, sizeof(__st_data));
        __free(__st_mat_access_row(mat, i)->data);
    }

    p = (void *)mat->first;
    memset(p, 0, mat->nrow*sizeof(st_vector));
    __free(p);

    memset(mat, 0, sizeof(st_matrix));
    __free(mat);
}

static void
__free_view(void *view)
{
    memset(view, 0, sizeof(st_view));
    __free(view);
}

static void
__status_vector(void *vector)
{
    const st_vector *vec = vector;
    printf(
        "%10s Vector (%p), %s, size (%d)\n",
        __st_dtype_str(vec->dtype),
        vec,
        __st_temp_str(vec->temp),
        vec->len
    );
}

static void
__status_matrix(void *matrix)
{
    const st_matrix *mat = matrix;
    printf(
        "%10s Matrix (%p), %s, size (%d, %d)\n",
        __st_dtype_str(mat->dtype),
        mat,
        __st_temp_str(mat->temp),
        mat->nrow,
        mat->ncol
    );
}

static void
__status_view(void *view)
{
    const st_view *v = view;
    printf(
        "%10s View   (%p), %s, size (%d)\n",
        __st_dtype_str(v->dtype),
        v,
        __st_temp_str(v->temp),
        v->len
    );
}

size_t
__st_byteof(__st_dtype dtype)
{
    size_t nbyte;
    switch (dtype) {

        case st_bool:
            nbyte = sizeof(__st_bool);
            break;

        case st_pixel:
            nbyte = sizeof(__st_pixel);
            break;

        case st_int:
            nbyte = sizeof(__st_int);
            break;

        case st_double:
            nbyte = sizeof(__st_double);
            break;

        default:
            nbyte = 0;
            __st_raise_dtype_error();
    }

    return nbyte;
}


/* =================================================================================================
 * functions here defined to support vector computation. 
 * @__st_new_vector: construct function of vector.
 * @st_new_bool_vector: construct new bool vector.
 * @st_new_pixel_vector: construct new __st_pixel vector.
 * @st_new_int_vector: construct new int vector.
 * @st_new_vector: construct new double vector.
 */

st_vector *
__st_new_vector(__st_dtype dtype, size_t len)
{
    st_vector *vec;
    __st_data *data;
    void *head;
    size_t nbyte = __st_byteof(dtype);

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
        st_sha_vector,
        true,
        dtype,
        data, /* data */
        len,  /* len */
    };

    memcpy(data, &_data, sizeof(__st_data));
    memcpy(vec, &_vec, sizeof(st_vector));
    __st_ds_add(vec, __free_vector, __status_vector, &vec->temp);
    return vec;
}

st_vector *
st_new_bool_vector(size_t len)
{
    return __st_new_vector(st_bool, len);
}

st_vector *
st_new_pixel_vector(size_t len)
{
    return __st_new_vector(st_pixel, len);
}

st_vector *
st_new_int_vector(size_t len)
{
    return __st_new_vector(st_int, len);
}

st_vector *
st_new_vector(size_t len)
{
    return __st_new_vector(st_double, len);
}

void
st_vec_display(const st_vector *vec)
{
    __st_check_valid(vec);
    char c;
    switch (vec->dtype) {

        case st_bool: {
            printf("BoolVector([");

            for (size_t i = 0; i <= vec->len - 2; i++) {
                c = (st_vec_access(vec, i) == false ? '-' : '+');
                printf("(%c), ", c);
            }

            printf("(%c)])\n", (st_vec_access(vec, vec->len-1) == false ? '-' : '+'));
            break;
        }

        case st_pixel: {
            printf("PixelVector([");

            for (size_t i = 0; i <= vec->len - 2; i++)
                printf("(%d), ", (int)st_vec_access(vec, i));

            printf("(%d)])\n", (int)st_vec_access(vec, vec->len-1));
            break;
        }

        case st_int: {
            printf("IntVector([");

            for (size_t i = 0; i <= vec->len - 2; i++)
                printf("%d, ", (int)st_vec_access(vec, i));

            printf("%d])\n", (int)st_vec_access(vec, vec->len-1));
            break;
        }

        case st_double: {
            printf("Vector([");

            for (size_t i = 0; i <= vec->len - 2; i++)
                printf("%f, ", (double)st_vec_access(vec, i));

            printf("%f])\n", (double)st_vec_access(vec, vec->len-1));
            break;
        }

        default:
            __st_raise_dtype_error();
            break;
    }
    printf("\n");
}

void
st_vec_assign_all(st_vector *vec, double value)
{
    __st_check_valid(vec);
    void *p;

    for __st_iter_data(p, vec->data)
        __st_assign_p(p, value, vec->dtype);
}

double
__st_data_access(const __st_data *data, size_t idx)
{
    if (idx < 0 || data->size <= idx)
        __st_raise_out_range_error();

    void *p = __st_data_find_p(data, idx);

    switch (data->dtype) {
        case st_bool:
            return (double)*(bool *)(p);

        case st_int:
            return (double)*(int *)(p);

        case st_pixel:
            return (double)*(unsigned char *)(p);

        case st_double:
            return *(double *)(p);

        default:
            __st_raise_dtype_error();
    }
}

static void
__st_data_assign(const __st_data *data, size_t idx, double value)
{
    if (idx < 0 || data->size <= idx)
        __st_raise_out_range_error();

    switch (data->dtype) {

        case st_bool: {
            bool *e = __st_data_find_p(data, idx);
            *e = (bool) value;
            return;
        }

        case st_pixel: {
            unsigned char *e = __st_data_find_p(data, idx);
            *e = (unsigned char) value;
            return;
        }

        case st_int: {
            int *e = __st_data_find_p(data, idx);
            *e = (int) value;
            return;
        }

        case st_double: {
            double *e = __st_data_find_p(data, idx);
            *e = (double) value;
            return;
        }

        default:
            __st_raise_dtype_error();
    }
}

double
st_vec_access(const st_vector *vec, size_t idx)
{
    __st_data_access(vec->data, idx);
}

void
st_vec_assign(const st_vector *vec, size_t idx, double value)
{
    __st_data_assign(vec->data, idx, value);
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
st_vec_copy_cast(st_vector *vec, __st_dtype dtype)
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

/* =================================================================================================
 * functions here defined to support matrix computation. 
 */

static void
__new_row(void *row, void *row_data_head, __st_dtype dtype, size_t len)
{
    size_t nbyte = __st_byteof(dtype);
    __st_data *data = malloc(sizeof(__st_data));
    __st_data _data = {
        row_data_head,
        row_data_head + nbyte * (len - 1),
        dtype,
        nbyte,
        len,
    };
    st_vector _vec = {
        st_sha_vector,
        false,  /* this options here doesn't work because
                   this vector is not constructed by __st_new_vector */
        dtype,
        data,
        len
    };

    memcpy(data, &_data, sizeof(__st_data));
    memcpy(row, &_vec, sizeof(st_vector));
    __st_ds_add(row, NULL, NULL, &((st_vector *)row)->temp);
}

st_matrix *
__st_new_matrix(__st_dtype dtype, size_t nrow, size_t ncol)
{
    st_matrix *mat;
    st_vector *_tmp_vec;
    __st_data *data;
    void *head, *first;
    size_t nbyte = __st_byteof(dtype);

    mat = malloc(sizeof(st_matrix));
    data = malloc(sizeof(__st_data));
    head = malloc(nrow * ncol * nbyte);
    first = malloc(nrow * sizeof(st_vector));

    __st_data _data = {
        head,                             /* head */
        head + (nrow * ncol - 1) * nbyte, /* last */
        dtype,                            /* dtype */
        nbyte,                            /* nbyte */
        nrow * ncol,                      /* size */
    };

    for (size_t i = 0; i < nrow; i++) {
        __new_row(
            first+i*sizeof(st_vector),
            head+i*ncol*nbyte,
            dtype,
            ncol
        );
    }

    st_matrix _mat = {
        st_sha_matrix,
        true,
        dtype,
        data,
        nrow,
        ncol,
        first,
    };
    memcpy(data, &_data, sizeof(__st_data));
    memcpy(mat, &_mat, sizeof(st_matrix));
    __st_ds_add(mat, __free_matrix, __status_matrix, &mat->temp);

    return mat;
}

st_matrix *
st_new_bool_matrix(size_t nrow, size_t ncol)
{
    return __st_new_matrix(st_bool, nrow, ncol);
}

st_matrix *
st_new_pixel_matrix(size_t nrow, size_t ncol)
{
    return __st_new_matrix(st_pixel, nrow, ncol);
}

st_matrix *
st_new_int_matrix(size_t nrow, size_t ncol)
{
    return __st_new_matrix(st_int, nrow, ncol);
}

st_matrix *
st_new_matrix(size_t nrow, size_t ncol)
{
    return __st_new_matrix(st_double, nrow, ncol);
}

void
st_mat_display(st_matrix *mat)
{
    __st_check_valid(mat);

    char c;
    switch (mat->dtype) {

        case st_bool: {
            printf("BoolMatrix([");

            for (size_t i = 0; i < mat->nrow; i++) {
                for (size_t j = 0; j < mat->ncol; j++) {
                    c = (__st_mat_access(mat, i, j) == false ? '-': '+');

                    if (i == (mat->nrow-1) && j == (mat->ncol-1))
                        printf("(%c)])", c);
                    else
                        printf("(%c), ", c);
                }

                if (i == (mat->nrow-1))
                    printf("\n");
                else
                    printf("\n            ");
            }
        }
        break;

        case st_pixel: {
            printf("PixelMatrix([");

            for (size_t i = 0; i < mat->nrow; i++) {
                for (size_t j = 0; j < mat->ncol; j++) {

                    if (i == (mat->nrow-1) && j == (mat->ncol-1))
                        printf("(%3d)])", (int)__st_mat_access(mat, i, j));
                    else
                        printf("(%3d), ", (int)__st_mat_access(mat, i, j));
                }

                if (i == (mat->nrow-1))
                    printf("\n");
                else
                    printf("\n             ");
            }
        }
        break;

        case st_int: {
            printf("IntMatrix([");

            for (size_t i = 0; i < mat->nrow; i++) {
                for (size_t j = 0; j < mat->ncol; j++) {

                    if (i == (mat->nrow-1) && j == (mat->ncol-1))
                        printf("%3d])", (int)__st_mat_access(mat, i, j));
                    else
                        printf("%3d, ", (int)__st_mat_access(mat, i, j));
                }

                if (i == (mat->nrow-1))
                    printf("\n");
                else
                    printf("\n           ");
            }
        }
        break;

        case st_double: {
            printf("Matrix([");

            for (size_t i = 0; i < mat->nrow; i++) {
                for (size_t j = 0; j < mat->ncol; j++) {

                    if (i == (mat->nrow-1) && j == (mat->ncol-1))
                        printf("%.2f])", __st_mat_access(mat, i, j));
                    else
                        printf("%.2f,  ", __st_mat_access(mat, i, j));
                }

                if (i == (mat->nrow-1))
                    printf("\n");
                else
                    printf("\n        ");
            }
        }
        break;

        default:
        __st_raise_dtype_error();
    }

    printf("\n");
}

void
st_mat_assign_all(st_matrix *mat, double value)
{
    __st_check_valid(mat);

    void *p;

    for __st_iter_data(p, mat->data)
        __st_assign_p(p, value, mat->data->dtype);
}

/* =================================================================================================
 * functions here defined to support view computation. 
 */

st_view *
st_new_view()
{
    st_view *view = malloc(sizeof(st_view));
    st_view _view = {
        st_sha_view,
        true,
        0,    /* default dtype */
        NULL, /* initialize it to NULL so that realloc() will work properly */
        NULL,
        0,
    };
    memcpy(
        view,
        &_view,
        sizeof(st_view)
    );
    __st_ds_add(view, __free_view, __status_view, &view->temp);
    return view;
}

void
st_matrix_view_row(st_view *view, st_matrix *mat, size_t irow)
{
    void *p;
    size_t i;
    view->dtype = mat->dtype;

    if (view->len != mat->ncol) {
        view->len = mat->ncol;
        view->head = realloc(view->head, view->len * sizeof(void *));
        view->last = view->head + view->len-1;
    }

    for __st_iter_vector(i, p, __st_mat_access_row(mat, irow))
        view->head[i] = p;
}

void
st_matrix_view_col(st_view *view, st_matrix *mat, size_t icol)
{
    view->dtype = mat->dtype;

    if (view->len != mat->nrow) {
        view->len = mat->nrow;
        view->head = realloc(view->head, view->len * sizeof(void *));
        view->last = view->head + view->len-1;
    }

    for (size_t i = 0; i < view->len; i++)
        view->head[i] = __st_mat_find_p(mat, i, icol);
}

void
st_vector_view(st_view *view, st_vector *vec)
{
    void *p;
    size_t i;
    view->dtype = vec->dtype;

    if (view->len != vec->len) {
        view->len = vec->len;
        view->head = realloc(view->head, view->len * sizeof(void *));
        view->last = view->head + view->len-1;
    }

    for __st_iter_vector(i, p, vec)
        view->head[i] = p;
}

void
st_view_display(const st_view *view)
{
    char c;
    switch (view->dtype) {

        case st_bool: {
            printf("BoolView([\n");

            for (size_t i = 0; i <= view->len - 2; i++) {
                c = (__st_view_access(view, i) == false ? '-' : '+');
                printf("(%c), ", c);

                if ((i + 1) % 10 == 0)
                    printf("\n");
            }

            printf("(%c)])\n", (__st_view_access(view, view->len-1) == false ? '-' : '+'));
            break;
        }

        case st_pixel: {
            printf("PixelView([\n");

            for (size_t i = 0; i <= view->len - 2; i++) {
                printf("(%3d), ", (int)__st_view_access(view, i));

                if ((i + 1) % 10 == 0)
                    printf("\n");
            }

            printf("(%3d)])\n", (int)__st_view_access(view, view->len-1));
            break;
        }

        case st_int: {
            printf("IntView([\n");

            for (size_t i = 0; i <= view->len - 2; i++) {
                printf("%5d, ", (int)__st_view_access(view, i));

                if ((i + 1) % 10 == 0)
                    printf("\n");
            }

            printf("%5d])\n", (int)__st_view_access(view, view->len-1));
            break;
        }

        case st_double: {
            printf("View([");

            double d;
            for (size_t i = 0; i <= view->len - 2; i++) {
                d = (double)__st_view_access(view, i);
                printf("%4.2f, ", (double)__st_view_access(view, i));

                if ((i + 1) % 10 == 0)
                    printf("\n      ");
            }

            printf("%4.2f])\n", (double)__st_view_access(view, view->len-1));
            break;
        }

        default:
            __st_raise_dtype_error();
            break;
    }
    printf("\n");
}

/* =================================================================================================
 * check
 */

__st_dtype
st_check_data_dtype(const __st_data *data, __st_dtype dtype)
{
    if (data->dtype != dtype)
        __st_raise_dtype_error();
    
    return dtype;
}

size_t
st_check_data_size(const __st_data *data, size_t size)
{
    if (data->size != size)
        __st_raise_length_error();

    return size;
}

size_t
st_check_vec_len(const st_vector *vec, size_t len)
{
    if (vec->len != len)
        __st_raise_length_error();

    return len;
}

__st_dtype
st_check_vec_dtype(const st_vector *vec, __st_dtype dtype)
{
    if (vec->dtype != dtype)
        __st_raise_dtype_error();
    
    return dtype;
}

size_t
st_check_mat_nrow(const st_matrix *mat, size_t nrow)
{
    if (mat->nrow != nrow)
        __st_raise_length_error();

    return nrow;
}

size_t
st_check_mat_ncol(const st_matrix *mat, size_t ncol)
{
    if (mat->ncol != ncol)
        __st_raise_length_error();

    return ncol;
}

__st_dtype
st_check_mat_dtype(const st_matrix *mat, __st_dtype dtype)
{
    if (mat->dtype != dtype)
        __st_raise_dtype_error();

    return dtype;
}
