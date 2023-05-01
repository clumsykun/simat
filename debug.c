#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "core/types.h"
#include "core/vector.h"
#include "core/matrix.h"

int test_vector()
{
    unsigned int len = 500;
    Vector *vec = create_vector(len);

    for (size_t i = 0; i < 500; i ++) {
        idx(vec, i) = 500-i;
    }

    assert(vector_max(vec) == 500);
    assert(vector_min(vec) == 1);

    vector_set_rand(vec);
    assert(vector_max(vec) != 500);
    assert(vector_min(vec) != 1);

    vector_scale(vec, 0, 1);
    assert(vector_max(vec) == 1);
    assert(vector_min(vec) == 0);

    vector_set_rand(vec);
    vector_sort(vec);
    vector_display(vec);
    free_vector(vec);
    return 0;
}


int test_matrix()
{
    unsigned int nrow = 10;
    unsigned int ncol = 4;
    Matrix *mat = create_matrix(nrow, ncol);
    View *view;
    Col *col = create_col();

    for (size_t i = 0; i < ncol; i++) {
        matrix_loc_col(col, mat, i);
        for (size_t j = 0; j < nrow; j ++) {
            idx(col->vec, j) = (double) i * 100 + j+1;
        }

        // vector_scale(vec, 0, 100);
        vector_display(col->vec);
    }

    matrix_display(mat);

    printf("------------------------------\n");

    view = create_view(ncol);
    matrix_view_row(view, mat, 3);
    view_display(view);
    matrix_view_col(view, mat, 3);
    view_display(view);

    printf("------------------------------\n");

    free_matrix(mat);
    free_view(view);
    free_col(col);
    return 0;
}

int test_stats()
{
    return 0;
}


int main()
{
    // test_vector();
    test_matrix();
    return 0;
}
