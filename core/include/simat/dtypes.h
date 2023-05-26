#ifndef SIMAT_DTYPES_H
#define SIMAT_DTYPES_H
#include "inspector.h"


#define st_bool bool
#define st_pixel unsigned char
#define st_int int
#define st_double double

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
    bool temp;
    __st_dtype dtype;
    void **head;
    void **last;
    size_t len;
} st_view;

#define st_is_bool(x) (x->dtype == __st_bool)
#define st_is_pixel(x) (x->dtype == __st_pixel)
#define st_is_int(x) (x->dtype == __st_int)
#define st_is_double(x) (x->dtype == __st_double)

/* return the ptr of the `vec` of index `idx` */
#define __st_vec_find_p(vec, idx) (vec->data->head + (size_t)(idx) * vec->data->nbyte)

/* return the ptr of the `mat` of index (`irow`, `icol`) */
#define __st_mat_find_p(mat, irow, icol) \
    (mat->data->head + ((size_t)(irow)*(mat->ncol)+(size_t)(icol))*mat->data->nbyte)

/* access the value of `p`, as type of `st_dtype` */
#define __st_access_p(p, st_dtype)              \
    (st_dtype == __st_double                    \
        ? *(double *)(p)                        \
        : (st_dtype == __st_int                 \
            ? (double)*(int *)(p)               \
            : (st_dtype == __st_pixel           \
                ? (double)*(unsigned char *)(p) \
                : (st_dtype == __st_bool        \
                    ? (double)*(bool *)(p)      \
                    : __st_raise_access_error()))))

/* assign `value` to `p`, as type of `st_dtype` */
#define __st_assign_p(p, value, st_dtype)                  \
    (st_dtype == __st_double                               \
        ? (*(st_double *)(p) = (st_double)(value))         \
        : (st_dtype == __st_int                            \
            ? (*(st_int *)(p) = (st_int)(value))           \
            : (st_dtype == __st_pixel                      \
                ? (*(st_pixel *)(p) = (st_pixel)(value))   \
                : (st_dtype == __st_bool                   \
                    ? (*(st_bool *)(p) = (st_bool)(value)) \
                    : __st_raise_dtype_error()))))

#define st_vec_access(vec, idx)                        \
    ((idx < 0 || vec->len <= idx)                      \
        ? __st_raise_out_range_error()                 \
            : __st_access_p(__st_vec_find_p(vec, idx), \
                            vec->data->dtype))

#define st_view_access(view, idx)                         \
    ((idx < 0 || view->len <= idx)                        \
        ? __st_raise_out_range_error()                    \
            : __st_access_p(*((void **)view->head+idx),   \
                            view->dtype))

/* TODO: check irow/icol are in range */
#define st_mat_access(mat, irow, icol) \
    __st_access_p(__st_mat_find_p(mat, irow, icol), mat->data->dtype)

#define st_mat_access_row(mat, irow) ((st_vector *)mat->first+(irow))

#define st_vec_assign(vec, idx, value)                  \
    ((idx < 0 || vec->len <= idx)                       \
        ? __st_raise_out_range_error()                  \
        : (__st_assign_p(__st_vec_find_p(vec, idx),     \
                             value,                     \
                             vec->data->dtype)))

#define st_mat_assign(mat, irow, icol, value) \
    ((irow < 0 || mat->nrow <= irow) \
        ? __st_raise_out_range_error() \
        : ((icol < 0 || mat->ncol <= icol) \
            ? __st_raise_out_range_error() \
            : __st_assign_p(__st_mat_find_p(mat, irow, icol),\
                            value,\
                            mat->data->dtype)))

/* TODO: check the range */
#define st_view_assign(view, idx, value) __st_assign_p(view->head[idx], value, view->dtype)

size_t __st_byteof(__st_dtype dtype);

st_vector *st_new_bool_vector(size_t len);
st_vector *st_new_pixel_vector(size_t len);
st_vector *st_new_int_vector(size_t len);
st_vector *st_new_vector(size_t len);
void st_vec_display(const st_vector *vec);
void st_vec_assign_all(st_vector *vec, double value);

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

#define __st_iter_data(p, data) (p = data->head; p <= data->last; p += data->nbyte)
#define st_iter_vector(p, vec) __st_iter_data(p, vec->data)
#define st_iter_matrix(p, mat) __st_iter_data(p, mat->data)

#endif /* SIMAT_DTYPES_H */
