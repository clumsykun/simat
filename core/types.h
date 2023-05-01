#ifndef CORE_TYPES_H
#define CORE_TYPES_H

/**
 * @head: ptr of the first number of the vector
 * @len: length of this vector
 */
typedef struct _Vector
{
    double *head;
    unsigned int len;
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
    double *head;
    unsigned int nrow;
    unsigned int ncol;
} Matrix;

typedef struct _Col
{
    unsigned int idx;
    Matrix *matrix;
    Vector *vec;
} Col;

#endif /* CORE_TYPES_H */
