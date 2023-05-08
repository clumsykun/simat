#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "basic.h"
#include "dtypes.h"
#include "vector.h"

int main()
{
    size_t nrow = 10;
    size_t ncol = 5;
    st_matrix *mat = st_new_matrix(nrow, ncol);
    st_matrix *bool_mat = st_new_bool_matrix(nrow, ncol);
    st_matrix *pixel_mat = st_new_pixel_matrix(nrow, ncol);
    st_matrix *int_mat = st_new_int_matrix(nrow, ncol);

    srand(time(NULL));

    st_mat_rand(bool_mat);
    st_mat_display(bool_mat);
    st_mat_rand(pixel_mat);
    st_mat_display(pixel_mat);
    st_mat_rand(int_mat);
    st_mat_display(int_mat);
    st_mat_rand(mat);
    st_mat_display(mat);

    // for (size_t i = 0; i < mat->ncol; i++) {
    //     st_vec_display(st_mat_access_col(mat, i));
    // }

    st_free_matrix(bool_mat);
    st_free_matrix(pixel_mat);
    st_free_matrix(int_mat);
    st_free_matrix(mat);

    return 0;
}
