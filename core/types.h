#ifndef CORE_TYPES_H
#define CORE_TYPES_H

enum order
{
    ascend,
    descend,
};

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
 * this works for both Vector and View
 * Vector vec: idx(vec, i)
 * View view: *idx(view, i)
 */
#define idx(x, i) x->head[i]

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

#endif /* CORE_TYPES_H */
