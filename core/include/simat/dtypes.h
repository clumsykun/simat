#ifndef CORE_DTYPES_H
#define CORE_DTYPES_H

#include <string.h>
#include "watcher.h"

/**
 * @__st_pixel: unsigned char
 */
typedef enum __st_dtype__ {
    st_bool = 1,
    st_pixel,
    st_int,
    st_double,
} __st_dtype;

/**
 * @head: ptr of first element of the data
 * @last: ptr of last element of the data
 * @nbyte: how many bytes single element occupied
 * @size: how many element is there
 */
typedef struct __st_data__
{
    void *const head;
    void *const last;
    const __st_dtype dtype;
    const size_t nbyte;
    const size_t size;
} __st_data;

typedef struct __st_vector
{
    char sha[64];
    bool temp;
    const __st_dtype dtype;
    __st_data *const data;
    const size_t len;  /* vec->len = vec->data->size */
} st_vector;

/**
 * matrix is basically an ordered collection of element
 * @head: ptr of the first number of the first vector of this matrix
 * @nrow: number of rows
 * @ncol: number of cols
 */
typedef struct __st_matrix
{
    char sha[64];
    bool temp;
    const __st_dtype dtype;
    const __st_data *data;
    const size_t nrow;
    const size_t ncol;
    const st_vector *const first; /* first col of this matrix as dtype of vector*/
} st_matrix;

/* flexible structure contains ptr of element of target vector/matrix */
typedef struct __st_view
{
    char sha[64];
    bool temp;
    __st_dtype dtype;
    void **head;
    void **last;
    size_t len;
} st_view;

#define __st_bool bool
#define __st_pixel unsigned char
#define __st_int int
#define __st_double double

#define st_is_bool(x) ((x)->dtype == st_bool)
#define st_is_pixel(x) ((x)->dtype == st_pixel)
#define st_is_int(x) ((x)->dtype == st_int)
#define st_is_double(x) ((x)->dtype == st_double)

#define st_is_vector(vec) !memcmp((vec), st_sha_vector, 64)
#define st_is_matrix(mat) !memcmp((mat), st_sha_matrix, 64)
#define st_is_view(view)  !memcmp((view), st_sha_view, 64)

/* =================================================================================================
 * access/assign of vector/matrix/view
 */

/* return the ptr of the `data` of index `idx` */
#define __st_data_find_p(data, idx) \
    ((data)->head + (size_t)(idx) * (data)->nbyte)

/* return the ptr of the `vec` of index `idx` */
#define __st_vec_find_p(vec, idx) \
    __st_data_find_p((vec)->data, idx)

/* return the ptr of the `mat` of index (`irow`, `icol`) */
#define __st_mat_find_p(mat, irow, icol) \
    ((mat)->data->head +                 \
        (mat)->data->nbyte * ((size_t)(irow)*((mat)->ncol)+(size_t)(icol)))

/* access the value of `p`, as type of `dtype` */
#define __st_access_p(p, dtype)                      \
    ((dtype) == st_double                        \
        ? *(__st_double *)(p)                        \
        : ((dtype) == st_int                     \
            ? (double)*(__st_int *)(p)               \
            : ((dtype) == st_pixel               \
                ? (double)*(__st_pixel *)(p)         \
                : ((dtype) == st_bool            \
                    ? (double)*(__st_bool *)(p)      \
                    : __st_raise_dtype_error()))))

#define __st_trim_pixel(x) ((x) > 255 ? 255 : ((x) < 0 ? 0 : (x)))

/* assign double `value` to `p`, as type of `dtype` */
#define __st_assign_p(p, value, dtype)                               \
    ((dtype) == st_double                                          \
         ? (*(__st_double *)(p) = (__st_double)(value))                  \
         : ((dtype) == st_int                                      \
                ? (*(__st_int *)(p) = (__st_int)(value))                 \
                : ((dtype) == st_pixel                             \
                       ? (*(__st_pixel *)(p) = (__st_pixel)__st_trim_pixel(value)) \
                       : ((dtype) == st_bool                       \
                              ? (*(__st_bool *)(p) = (__st_bool)(value)) \
                              : __st_raise_dtype_error()))))

/* TODO: check if valid */
#define __st_view_access(view, idx)                         \
    (((idx) < 0 || (view)->len <= (idx))                  \
        ? __st_raise_out_range_error()                    \
            : __st_access_p(*((void **)(view)->head+(idx)), \
                            (view)->dtype))

/* TODO: check irow/icol are in range and if valid */
#define __st_mat_access(mat, irow, icol) \
    __st_access_p(__st_mat_find_p((mat), (irow), (icol)), (mat)->data->dtype)

#define __st_mat_access_row(mat, irow) \
    ((st_vector *)(mat)->first+(irow))

#define __st_vec_assign(vec, idx, value)                    \
    (((idx) < 0 || (vec)->len <= (idx))                   \
        ? __st_raise_out_range_error()                    \
        : (__st_assign_p(__st_vec_find_p((vec), (idx)),   \
                             (value),                     \
                             (vec)->dtype)))

#define __st_mat_assign(mat, irow, icol, value)    \
    (((irow) < 0 || (mat)->nrow <= (irow))       \
        ? __st_raise_out_range_error()           \
        : (((icol) < 0 || (mat)->ncol <= (icol)) \
            ? __st_raise_out_range_error()       \
            : __st_assign_p(__st_mat_find_p((mat), (irow), (icol)),\
                            (value),                               \
                            (mat)->dtype)))

/* TODO: check the range */
#define __st_view_assign(view, idx, value) \
    __st_assign_p(view->head[idx], value, view->dtype)

/* =================================================================================================
 * function define.
 */

size_t __st_byteof(__st_dtype dtype);

st_vector *__st_new_vector(__st_dtype dtype, size_t len);
st_vector *st_new_bool_vector(size_t len);
st_vector *st_new_pixel_vector(size_t len);
st_vector *st_new_int_vector(size_t len);
st_vector *st_new_vector(size_t len);

st_matrix *__st_new_matrix(__st_dtype dtype, size_t nrow, size_t ncol);
st_matrix *st_new_bool_matrix(size_t nrow, size_t ncol);
st_matrix *st_new_pixel_matrix(size_t nrow, size_t ncol);
st_matrix *st_new_int_matrix(size_t nrow, size_t ncol);
st_matrix *st_new_matrix(size_t nrow, size_t ncol);

st_view *st_new_view();
void st_matrix_view_col(st_view *view, st_matrix *mat, size_t icol);
void st_matrix_view_row(st_view *view, st_matrix *mat, size_t irow);
void st_vector_view(st_view *view, st_vector *vec);

/* =================================================================================================
 * assign/access/display/copy
 */

double __st_data_access(const __st_data *data, size_t idx);
double st_vec_access(const st_vector *vec, size_t idx);

void st_vec_display(const st_vector *vec);
void st_vec_assign_all(st_vector *vec, double value);
st_vector *st_vec_copy(st_vector *vec);
void st_mat_display(st_matrix *mat);
void st_mat_assign_all(st_matrix *mat, double value);
void st_view_display(const st_view *view);

/* =================================================================================================
 * check.
 */

__st_dtype st_check_data_dtype(const __st_data *data, __st_dtype dtype);
size_t st_check_data_size(const __st_data *data, size_t size);

size_t st_check_vec_len(const st_vector *vec, size_t len);
__st_dtype st_check_vec_dtype(const st_vector *vec, __st_dtype dtype);
size_t st_check_mat_nrow(const st_matrix *mat, size_t nrow);
size_t st_check_mat_ncol(const st_matrix *mat, size_t ncol);
__st_dtype st_check_mat_dtype(const st_matrix *mat, __st_dtype dtype);

/* =================================================================================================
 * iterator.
 */

#define __st_iter_data(elem, data) \
    ( \
        elem = data->head;  \
        elem <= data->last; \
        elem += data->nbyte \
    )

#define __st_iter_vector(i, elem, vec) \
    ( \
        elem = vec->data->head, i = 0;        \
        elem <= vec->data->last;              \
        elem += vec->data->nbyte, (size_t)i++ \
    )

#define __st_iter_view(i, elem, view) \
    ( \
        elem = view->head, i = 0;        \
        elem <= view->last;              \
        elem++, (size_t)i++ \
    )

#define __st_iter_vector2(i, e1, e2, v1, v2) \
    ( \
        e1 = (v1)->data->head, e2 = (v2)->data->head, (i) = 0;          \
        (i) < (v1)->len;                                                \
        e1 += (v1)->data->nbyte, e2 += (v2)->data->nbyte, (size_t)(i)++ \
    )

#define __st_iter_vector3(i, e1, e2, e3, vec1, vec2, vec3) \
    ( \
        e1 = vec1->data->head,       \
            e2 = vec2->data->head,   \
            e3 = vec3->data->head,   \
            i = 0;                   \
        e1 <= vec1->data->last;      \
        e1 += vec1->data->nbyte,     \
            e2 += vec2->data->nbyte, \
            e3 += vec3->data->nbyte, \
            (size_t)i++              \
    )

#define __st_iter_matrix(irow, icol, elem, mat) \
    ( \
        elem = mat->data->head, irow = 0, icol = 0;                                   \
        elem <= mat->data->last;                                                      \
        elem += mat->data->nbyte,                                                     \
            irow = ((size_t)icol + 1 == mat->ncol ? (size_t)irow + 1 : (size_t)irow), \
            icol = ((size_t)icol + 1 == mat->ncol ? 0 : (size_t)icol + 1)             \
    )

#endif /* CORE_DTYPES_H */
