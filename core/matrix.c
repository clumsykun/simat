#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#include "types.h"
#include "vector.h"
#include "matrix.h"

Matrix *create_matrix(unsigned int nrow, unsigned int ncol)
{
    Matrix *mat = malloc(sizeof(Matrix));
    mat->nrow = nrow;
    mat->ncol = ncol;
    mat->head = malloc(nrow * ncol * sizeof(double));
    return mat;
}

void free_matrix(Matrix *mat)
{
    mat->ncol = 0;
    mat->nrow = 0;
    _std_free(mat->head);
    _std_free(mat);
}

/**
 * @idx: the index of array which you want locate
 */
void loc_col(Vector *vec, Matrix *mat, unsigned int idx)
{
    vec->len = mat->nrow;
    vec->head = &(mat->head[idx * mat->nrow]);
}

void matrix_display(Matrix *mat)
{
    double(*head)[mat->nrow] = (double(*)[mat->nrow])mat->head;
    printf("    ");

    for (size_t j = 0; j < mat->ncol; j++) {
        printf("[%1d]        ", j);
    }

    printf("\n");

    for (size_t i = 0; i < mat->nrow; i++) {
        printf("[%1d]  ", i);

        for (size_t j = 0; j < mat->ncol; j++) {
            printf("%.2f    ", head[j][i]);
        }
        printf("\n");
    }
}
