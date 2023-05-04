#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "core/flags.h"
#include "core/dtypes.h"
#include "core/tools.h"
#include "core/vector.h"
#include "core/matrix.h"
#include "core/stats.h"


int test_vector()
{
    unsigned int len = 50;

    // Vector *vec = create_bool_vector(len);
    // Vector *vec = create_pixel_vector(len);
    // Vector *vec = create_int_vector(len);
    Vector *vec = create_double_vector(len);

    size_t size = 0;
    for (char *p = vec->head; p <= vec->bott; p += vec->esize, size++)
        dassign(p, (double)size+10, vec->dtype);

    printf("set random:\n");
    vector_set_rand(vec);
    vector_display(vec);

    printf("scale:\n");
    vector_scale(vec, 0, 100);
    vector_display(vec);
    if (vec->dtype == dtype_bool) {
        assert(vector_max(vec) == 1);
        assert(vector_min(vec) == 0);
    }
    else {
        assert((int)vector_max(vec) == 100);
        assert((int)vector_min(vec) == 0);
    }

    printf("sort ascend:\n");
    vector_sort(vec, ascend);
    vector_display(vec);

    printf("sort descend:\n");
    vector_sort(vec, descend);
    vector_display(vec);

    free_vector(vec);
    return 0;
}


int test_matrix()
{
    unsigned int nrow = 10;
    unsigned int ncol = 5;
    Matrix *mat = create_matrix(nrow, ncol);
    View *view = create_view();
    Col *col = create_col();

    // for (size_t i = 0; i < ncol; i++) {
    //     matrix_loc_col(col, mat, i);
    //     for (size_t j = 0; j < nrow; j ++) {
    //         idx(col->vec, j) = (double) i * 100 + j + 1;
    //     }

    //     // vector_scale(vec, 0, 100);
    //     vector_display(col->vec);
    // }

    matrix_display(mat);

    printf("------------------------------\n");

    matrix_view_col(view, mat, 2);
    view_display(view);
    matrix_view_col(view, mat, 3);
    view_display(view);
    matrix_view_row(view, mat, 3);
    view_display(view);

    printf("max of row [3] is %.2f\n", view_max(view));
    printf("min of row [3] is %.2f\n", view_min(view));

    printf("set random:\n");
    view_set_rand(view);
    view_display(view);

    printf("scale:\n");
    view_scale(view, 0, 100);
    view_display(view);

    printf("sort ascend:\n");
    view_sort(view, ascend);
    view_display(view);

    printf("sort descend:\n");
    view_sort(view, descend);
    view_display(view);

    matrix_display(mat);

    printf("------------------------------\n");

    free_matrix(mat);
    free_view(view);
    free_col(col);
    return 0;
}

int test_stats()
{
    unsigned int len = 10;
    Vector *vec = create_int_vector(len);
    for (size_t i = 0; i < len; i++) {
        idx(vec, i) = i+1;
    }
    vector_display(vec);

    assert(stats_mean(vec)==5.5);
    assert(stats_var(vec, 0) == 8.25);
    assert(stats_std(vec, 0) == 2.8722813232690143);

    printf("mean is %.2f\n", stats_mean(vec));
    printf("var is %.2f\n", stats_var(vec, 0));
    printf("std is %.2f\n", stats_std(vec, 0));

    return 0;
}

int main()
{
    test_vector();
    // test_matrix();
    // test_stats();
    return 0;
}
