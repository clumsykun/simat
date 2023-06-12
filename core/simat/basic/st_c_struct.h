#ifndef CORE_struct_H
#define CORE_struct_H

#include "st_b_watcher.h"

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
    const st_dtype dtype;
    const size_t nbyte;
    const size_t size;
} __st_data;

typedef struct __st_vector
{
    st_bool temp;
    const st_dtype dtype;
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
    st_bool temp;
    const st_dtype dtype;
    const __st_data *data;
    const size_t nrow;
    const size_t ncol;
    const st_vector *const first; /* first col of this matrix as dtype of vector*/
} st_matrix;

/* flexible structure contains ptr of element of target vector/matrix */
typedef struct __st_view
{
    st_bool temp;
    st_dtype dtype;
    void **head;
    void **last;
    size_t nbyte;
    size_t len;
} st_view;

#define st_is_bool(x) ((x)->dtype == st_dtype_bool)
#define st_is_pixel(x) ((x)->dtype == st_dtype_u8)
#define st_is_int(x) ((x)->dtype == st_dtype_i32)
#define st_is_double(x) ((x)->dtype == st_dtype_d64)

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
    ((dtype) == st_dtype_d64                        \
        ? *(st_d64 *)(p)                        \
        : ((dtype) == st_dtype_i32                     \
            ? (st_d64)*(st_i32 *)(p)               \
            : ((dtype) == st_dtype_u8               \
                ? (st_d64)*(st_u8 *)(p)         \
                : ((dtype) == st_dtype_bool            \
                    ? (st_d64)*(st_bool *)(p)      \
                    : __st_raise_dtype_error()))))

#define __st_trim_pixel(x) ((x) > 255 ? 255 : ((x) < 0 ? 0 : (x)))

/* assign st_d64 `value` to `p`, as type of `dtype` */
#define __st_assign_p(p, value, dtype)                               \
    ((dtype) == st_dtype_d64                                          \
         ? (*(st_d64 *)(p) = (st_d64)(value))                  \
         : ((dtype) == st_dtype_i32                                      \
                ? (*(st_i32 *)(p) = (st_i32)(value))                 \
                : ((dtype) == st_dtype_u8                             \
                       ? (*(st_u8 *)(p) = (st_u8)__st_trim_pixel(value)) \
                       : ((dtype) == st_dtype_bool                       \
                              ? (*(st_bool *)(p) = (st_bool)(value)) \
                              : __st_raise_dtype_error()))))

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

st_vector *st_new_vector(size_t len, st_dtype dtype);

st_matrix *st_new_matrix(size_t nrow, size_t ncol, st_dtype dtype);

st_view *st_new_view();
void st_matrix_view_col(st_view *view, st_matrix *mat, size_t icol);
void st_matrix_view_row(st_view *view, st_matrix *mat, size_t irow);
void st_vector_view(st_view *view, st_vector *vec);

/* =================================================================================================
 * Assign/Access/Display
 */

st_decimal     __st_data_access(const __st_data *data, size_t idx);
st_decimal     st_vec_access(const st_vector *vec, size_t idx);
st_decimal     st_mat_access(const st_matrix *mat, size_t irow, size_t icol);
st_vector *st_mat_access_row(const st_matrix *mat, size_t irow);
st_decimal     st_view_access(const st_view *view, size_t idx);

void st_vec_assign(const st_vector *vec, size_t idx, st_d64 value);
void st_vec_assign_all(st_vector *vec, st_d64 value);
void st_mat_assign_all(st_matrix *mat, st_d64 value);

void st_vec_display(const st_vector *vec);
void st_mat_display(st_matrix *mat);
void st_view_display(const st_view *view);

/* =================================================================================================
 * check.
 */

st_bool st_check_data_dtype(const __st_data *data, st_dtype dtype);
st_bool st_check_data_size(const __st_data *data, size_t size);

size_t st_check_vec_len(const st_vector *vec, size_t len);
st_dtype st_check_vec_dtype(const st_vector *vec, st_dtype dtype);
size_t st_check_mat_nrow(const st_matrix *mat, size_t nrow);
size_t st_check_mat_ncol(const st_matrix *mat, size_t ncol);
st_dtype st_check_mat_dtype(const st_matrix *mat, st_dtype dtype);

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

#endif /* CORE_struct_H */
