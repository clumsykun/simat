#ifndef CORE_DTYPES_H
#define CORE_DTYPES_H
#include "flags.h"

enum st_order {
    st_ascend,
    st_descend,
};

enum st_dtype {
    st_bool,
    st_pixel,
    st_int,
    st_double,
};

/**
 * @head: ptr of the first number of the vector
 * @len: length of this vector
 */
typedef struct __st_data__
{
    void *const head;
    void *const last;        /* last element */
    const size_t byte; /* size of single element */
    const size_t size;
    const enum st_dtype dtype;
} __st_data;

typedef struct __st_vector
{
    char *label;
    const __st_data data;
} st_vector;

/* flexible structure contains ptr of element of target vector/matrix */
typedef struct __st_view
{
    char *label;
    __st_data data;
    __st_data source;
} st_view;

/**
 * matrix is basically an ordered collection of same sized vectors
 * @head: ptr of the first number of the first vector of this matrix
 * @nrow: number of rows
 * @ncol: number of cols
 */
typedef struct __st_matrix
{
    char *label;
    const __st_data data;
    const size_t nrow;
    const size_t ncol;
} st_matrix;

/* access the value of element of vector/matrix, as type of double */
#define st_access(dtype, p)                \
    (dtype == st_bool                      \
        ? (double)*((bool *)p)                \
        : (dtype == st_pixel               \
            ? (double)*((unsigned char *)p)           \
            : (dtype == st_int             \
                ? (double)*((int *)p)         \
                : (dtype == st_double      \
                    ? *((double *)p)          \
                    : __double_raise_error()))))

#define st_byteof(dtype)                   \
    (dtype == st_bool                      \
        ? sizeof(bool)                        \
        : (dtype == st_pixel               \
            ? sizeof(unsigned char)                   \
            : (dtype == st_int             \
                ? sizeof(int)                 \
                : (dtype == st_double      \
                    ? sizeof(double)          \
                    : __size_raise_error()))))

/**
 * @x: vector or view.
 * @m: matrix.
 */
#define idx(x, i) x->head[i]
#define loc(m, i, j) m->head[m->nrow * i + j]

/* @x can be vector/view/column */
#define get(x, i)                                                          \
    ((x->dtype == dtype_vector)                                            \
         ? (x->head == NULL ? NULL : (x->head[i]))                         \
         : ((x->dtype == dtype_view)                                       \
                ? (x->head == NULL ? NULL : (*(x->head[i])))               \
                : ((x->dtype == dtype_column)                              \
                       ? (x->vec->head == NULL ? NULL : (x->vec->head[i])) \
                       : NULL)))


#define st_iter(target) (char *p = target->head; p <= target->last; p += target->byte)

#endif /* CORE_DTYPES_H */
