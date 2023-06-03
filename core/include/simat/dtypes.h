#ifndef CORE_DTYPES_H
#define CORE_DTYPES_H

#include <string.h>
#include "watcher.h"

/**
 * @st_pixel: unsigned char
 */
typedef enum __st_dtype__ {
    __st_bool = 1,
    __st_pixel,
    __st_int,
    __st_double,
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

#define st_bool bool
#define st_pixel unsigned char
#define st_int int
#define st_double double

#define st_is_bool(x) ((x)->dtype == __st_bool)
#define st_is_pixel(x) ((x)->dtype == __st_pixel)
#define st_is_int(x) ((x)->dtype == __st_int)
#define st_is_double(x) ((x)->dtype == __st_double)

#define st_is_vector(vec) !memcmp((vec), st_sha_vector, 64)
#define st_is_matrix(mat) !memcmp((mat), st_sha_matrix, 64)
#define st_is_view(view)  !memcmp((view), st_sha_view, 64)

/* =================================================================================================
 * access/assign of vector/matrix/view
 */

/* return the ptr of the `vec` of index `idx` */
#define __st_vec_find_p(vec, idx) \
    ((vec)->data->head + (size_t)(idx) * (vec)->data->nbyte)

/* return the ptr of the `mat` of index (`irow`, `icol`) */
#define __st_mat_find_p(mat, irow, icol) \
    ((mat)->data->head +                   \
     (mat)->data->nbyte * ((size_t)(irow)*((mat)->ncol)+(size_t)(icol)) \
    )

/* access the value of `p`, as type of `dtype` */
#define __st_access_p(p, dtype)                      \
    ((dtype) == __st_double                        \
        ? *(st_double *)(p)                        \
        : ((dtype) == __st_int                     \
            ? (double)*(st_int *)(p)               \
            : ((dtype) == __st_pixel               \
                ? (double)*(st_pixel *)(p)         \
                : ((dtype) == __st_bool            \
                    ? (double)*(st_bool *)(p)      \
                    : __st_raise_dtype_error()))))

/* assign `value` to `p`, as type of `dtype` */
#define __st_assign_p(p, value, dtype)                     \
    ((dtype) == __st_double                                \
        ? (*(st_double *)(p) = (st_double)(value))         \
        : ((dtype) == __st_int                             \
            ? (*(st_int *)(p) = (st_int)(value))           \
            : ((dtype) == __st_pixel                       \
                ? (*(st_pixel *)(p) = (st_pixel)(value))   \
                : ((dtype) == __st_bool                    \
                    ? (*(st_bool *)(p) = (st_bool)(value)) \
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
void       st_vec_display(const st_vector *vec);
void       st_vec_assign_all(st_vector *vec, double value);
double     st_vec_access(const st_vector *vec, size_t idx);

st_matrix *__st_new_matrix(__st_dtype dtype, size_t nrow, size_t ncol);
st_matrix *st_new_bool_matrix(size_t nrow, size_t ncol);
st_matrix *st_new_pixel_matrix(size_t nrow, size_t ncol);
st_matrix *st_new_int_matrix(size_t nrow, size_t ncol);
st_matrix *st_new_matrix(size_t nrow, size_t ncol);
void st_mat_display(st_matrix *mat);
void st_mat_assign_all(st_matrix *mat, double value);

st_view *st_new_view();
void st_matrix_view_col(st_view *view, st_matrix *mat, size_t icol);
void st_matrix_view_row(st_view *view, st_matrix *mat, size_t irow);
void st_vector_view(st_view *view, st_vector *vec);
void st_view_display(const st_view *view);

/* =================================================================================================
 * check.
 */

void st_check_vec_len(st_vector *vec, size_t len);
void st_check_mat_shape(st_matrix *mat, size_t nrow, size_t ncol);

/* =================================================================================================
 * iterator.
 */

#define __st_iter_data(p, data) \
    ( \
        p = data->head;  \
        p <= data->last; \
        p += data->nbyte \
    )

#define __st_iter_vector(i, p, vec) \
    ( \
        p = vec->data->head, i = 0;        \
        p <= vec->data->last;              \
        p += vec->data->nbyte, (size_t)i++ \
    )

#define __st_iter_view(i, p, view) \
    ( \
        p = view->head, i = 0;        \
        p <= view->last;              \
        p++, (size_t)i++ \
    )

#define __st_iter_vector2(i, p1, p2, vec1, vec2) \
    ( \
        p1 = vec1->data->head, p2 = vec2->data->head, i = 0;          \
        p1 <= vec1->data->last;                                       \
        p1 += vec1->data->nbyte, p2 += vec2->data->nbyte, (size_t)i++ \
    )

#define __st_iter_vector3(i, p1, p2, p3, vec1, vec2, vec3) \
    ( \
        p1 = vec1->data->head,       \
            p2 = vec2->data->head,   \
            p3 = vec3->data->head,   \
            i = 0;                   \
        p1 <= vec1->data->last;      \
        p1 += vec1->data->nbyte,     \
            p2 += vec2->data->nbyte, \
            p3 += vec3->data->nbyte, \
            (size_t)i++              \
    )

#define __st_iter_matrix(irow, icol, p, mat) \
    ( \
        p = mat->data->head, irow = 0, icol = 0;                                      \
        p <= mat->data->last;                                                         \
        p += mat->data->nbyte,                                                        \
            irow = ((size_t)icol + 1 == mat->ncol ? (size_t)irow + 1 : (size_t)irow), \
            icol = ((size_t)icol + 1 == mat->ncol ? 0 : (size_t)icol + 1)             \
    )

#endif /* CORE_DTYPES_H */
