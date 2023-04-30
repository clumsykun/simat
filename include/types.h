#ifndef TYPES_H
#define TYPES_H
#define loc(arr, i) arr->head[i]

/**
 * @head: ptr of the first number of the array
 * @len: length of this array
 */
typedef struct _Array
{
    double *head;
    unsigned int len;
} Array;

/**
 * matrix is basically an ordered collection of same sized arrays
 * @head: ptr of the first array of this matrix
 * @len: length of arrays
 * @num: number of arrays
 */
typedef struct _Matrix
{
    double *head;
    unsigned int len;
    unsigned int num;
} Matrix;

#endif
