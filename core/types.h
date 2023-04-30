#ifndef TYPES_H
#define TYPES_H
#define idx(vec, i) vec->head[i]

/**
 * @head: ptr of the first number of the vector
 * @len: length of this vector
 */
typedef struct _Vector
{
    double *head;
    unsigned int len;
    char* label;
} Vector;

typedef struct _pVector
{
    double **head;
    unsigned int len;
    char *label;
} pVector;

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

#endif /* CORE_TYPES_H */
