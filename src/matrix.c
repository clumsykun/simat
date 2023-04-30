#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#include "types.h"
#include "vector.h"
#include "matrix.h"

Matrix *create_matrix(unsigned int len, unsigned int num)
{
    Matrix *mat = malloc(sizeof(Matrix));
    mat->len = len;
    mat->num = num;
    mat->head = malloc(len * num * sizeof(double));
    return mat;
}

void free_matrix(Matrix *mat)
{
    _std_free(mat->head);
    _std_free(mat);
}

void matrix_display(Matrix *mat)
{
    double(*head)[mat->len] = (double(*)[mat->len])mat->head;

    for (size_t i = 0; i < mat->len; i++)
    {
        for (size_t j = 0; j < mat->num; j++)
        {
            printf("%.2f    ", head[j][i]);
        }
        printf("\n");
    }
}
