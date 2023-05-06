#ifndef SIMAT_DTYPES_H
#define SIMAT_DTYPES_H
#include "flags.h"


#define st_bool bool
#define st_pixel unsigned char
#define st_int int
#define st_double double

/**
 * @st_pixel: unsigned char
 */
typedef enum __st_dtype__ {
    __st_bool,
    __st_pixel,
    __st_int,
    __st_double,
} __st_dtype;

/**
 * @head: ptr of first element of the data
 * @last: ptr of last element of the data
 * @byte: how many bytes single element occupied
 * @size: how many element is there
 */
typedef struct __st_data__
{
    void *const head;
    void *const last;
    const size_t byte;
    const size_t size;
    const __st_dtype dtype;
} __st_data;

typedef struct __st_vector
{
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
    const __st_data data;
    const size_t nrow;
    const size_t ncol;
} st_matrix;

/* flexible structure contains ptr of element of target vector/matrix */
typedef struct __st_view
{
    void *head;
    void *last;
    size_t size;
    __st_dtype dtype;
    __st_data *source;
} st_view;

#define __st_assign_bool(p, v) *(st_bool *)(p) = v
#define __st_assign_pixel(p, v) *(st_pixel *)(p) = v
#define __st_assign_int(p, v) *(st_int *)(p) = v
#define __st_assign_double(p, v) *(st_double *)(p) = v

/* access the value of element of vector/matrix, as type of double */
#define __st_access(dtype, p)                   \
    (dtype == __st_double                     \
        ? *(double *)(p)                        \
        : (dtype == __st_int                  \
            ? (double)*(int *)(p)               \
            : (dtype == __st_pixel            \
                ? (double)*(unsigned char *)(p) \
                : (dtype == __st_double       \
                    ? (double)*(bool *)(p)      \
                    : __st_raise_access_error()))))

#define st_vec_access(vec, idx) \
    (idx < 0 \
        ? __st_raise_access_error() \
        : (idx >= vec->len \
            ? __st_raise_access_error() \
            : __st_access(vec->data->dtype, vec->data->head+idx*vec->data->byte)))

#define st_byteof(dtype)                     \
    (dtype == __st_double                    \
        ? sizeof(double)                     \
        : (dtype == __st_int                 \
            ? sizeof(int)                    \
            : (dtype == __st_pixel           \
                ? sizeof(int)                \
                : (dtype == __st_bool        \
                    ? sizeof(bool)           \
                    : __st_raise_dtype_error()))))

st_vector *st_new_bool_vector(size_t len);
st_vector *st_new_pixel_vector(size_t len);
st_vector *st_new_int_vector(size_t len);
st_vector *st_new_double_vector(size_t len);
void st_vec_free(st_vector *vec);
void st_vec_display(st_vector *vec);
void st_vec_assign(st_vector *vec, double value);

st_matrix *st_new_bool_matrix(size_t nrow, size_t ncol);
st_matrix *st_new_pixel_matrix(size_t nrow, size_t ncol);
st_matrix *st_new_int_matrix(size_t nrow, size_t ncol);
st_matrix *st_new_double_matrix(size_t nrow, size_t ncol);
void st_mat_free(st_matrix *mat);
void st_mat_display(st_matrix *mat);

st_view *st_new_view();
void st_view_free(st_view *view);
void st_view_display(st_view *view);

#define __st_data_iter(p, data) (p = data->head; p <= data->last; p += data->byte)

#endif /* SIMAT_DTYPES_H */
