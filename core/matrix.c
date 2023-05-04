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

Col *create_col()
{
    Col *col = malloc(sizeof(Col));
    Col _col = {
        0,
        NULL,
        malloc(sizeof(Vector))
    };
    memcpy(
        col,
        &_col,
        sizeof(Col)
    );
    return col;
}

void free_col(Col *col)
{
    col->idx = 0;
    col->matrix = NULL;
    __std_free(col->vec);
    __std_free(col);
}

/**
 * @idx: the index of array which you want locate
 */
// void matrix_loc_col(Col *col, Matrix *mat, unsigned int idx)
// {
//     col->idx = idx;
//     col->matrix = mat;
//     Vector _vec = {
//         &(mat->head[idx * mat->nrow]),
//         mat->nrow
//     };
//     memcpy(
//         col->vec,
//         &_vec,
//         sizeof(Vector)
//     );
// }

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
