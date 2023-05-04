#ifndef CORE_DTYPES_H
#define CORE_DTYPES_H
#include "flags.h"

enum order {
    ascend,
    descend,
};

enum dtype {
    dtype_bool,
    dtype_pixel,
    dtype_int,
    dtype_double,
};

#define pixel unsigned char

/**
 * @head: ptr of the first number of the vector
 * @len: length of this vector
 */
typedef struct _Vector
{
    const enum dtype dtype;
    char *const head;
    char *const bott;  /* bottom */
    const unsigned int esize; /* size of single element */
    const unsigned int len;
} Vector;

/* flexible structure contains ptr of element of target vector/matrix */
typedef struct _View
{
    double **head;
    unsigned int len;
} View;


/**
 * matrix is basically an ordered collection of same sized vectors
 * @head: ptr of the first number of the first vector of this matrix
 * @nrow: number of rows
 * @ncol: number of cols
 */
typedef struct _Matrix
{
    double *const head;
    const unsigned int nrow;
    const unsigned int ncol;
} Matrix;

typedef struct _Col
{
    unsigned int idx;
    Matrix *matrix;
    Vector *const vec;
} Col;

/* access the value of element of vector/matrix, as type of double */
#define access(dtype, p)                      \
    (dtype == dtype_bool                      \
        ? (double)*((bool *)p)                \
        : (dtype == dtype_pixel               \
            ? (double)*((pixel *)p)   \
            : (dtype == dtype_int             \
                ? (double)*((int *)p)         \
                : (dtype == dtype_double      \
                    ? *((double *)p)          \
                    : __double_raise_error()))))

/* do not mix this func with sizeof */
#define __sizeof(dtype)                        \
    (dtype == dtype_bool                      \
        ? sizeof(bool)                        \
        : (dtype == dtype_pixel               \
            ? sizeof(pixel)           \
            : (dtype == dtype_int             \
                ? sizeof(int)                 \
                : (dtype == dtype_double      \
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

#endif /* CORE_DTYPES_H */
