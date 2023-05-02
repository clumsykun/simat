#ifndef CORE_DTYPES_H
#define CORE_DTYPES_H

enum order {
    ascend,
    descend,
};

// enum dtype {
//     dtype_vector,
//     dtype_view,
//     dtype_matrix,
//     dtype_column,
// };

/**
 * @head: ptr of the first number of the vector
 * @len: length of this vector
 */
typedef struct _Vector
{
    double *const head;
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
