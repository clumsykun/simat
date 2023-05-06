#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tools.h"
#include "dtypes.h"
#include "vector.h"
#include "matrix.h"

Matrix *create_matrix(unsigned int nrow, unsigned int ncol)
{
    Matrix *mat = malloc(sizeof(Matrix));
    Matrix _mat = {
        malloc(nrow * ncol * sizeof(double)),
        nrow,
        ncol,
    };
    memcpy(
        mat,
        &_mat,
        sizeof(Matrix)
    );
    return mat;
}

void free_matrix(Matrix *mat)
{
    __std_free(mat->head);
    __std_free(mat);
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
            printf("%.2f,  ", head[j][i]);
        }
        printf("\n");
    }
}