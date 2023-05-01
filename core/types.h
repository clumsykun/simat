#ifndef CORE_TYPES_H
#define CORE_TYPES_H
#define idx(vec, i) vec->head[i]

/**
 * @head: ptr of the first number of the vector
 * @len: length of this vector
 */
typedef struct _Vector
{
    double *head;
    unsigned int len;
} Vector;

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
