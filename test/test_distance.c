#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "simat.h"

int main()
{
    size_t nrow = 10;
    size_t ncol = 5;
    st_matrix *mat = st_new_matrix(nrow, ncol);
    st_matrix *bool_mat = st_new_bool_matrix(nrow, ncol);
    st_matrix *pixel_mat = st_new_pixel_matrix(nrow, ncol);
    st_matrix *int_mat = st_new_int_matrix(nrow, ncol);

    // srand(time(NULL));

    st_mat_rand(bool_mat);
    st_mat_display(bool_mat);
    st_mat_rand(pixel_mat);
    st_mat_display(pixel_mat);
    st_mat_rand(int_mat);
    st_mat_display(int_mat);
    st_mat_rand(mat);
    st_mat_display(mat);

    st_vector *v1 = st_mat_access_col(mat, 1);
    st_vector *v2 = st_mat_access_col(mat, 2);

    st_vec_display(v1);
    st_vec_display(v2);

    printf("cos similarity of col 1 and col 2: %.4f\n", st_dist_cosine(v1, v2));

    st_free_matrix(bool_mat);
    st_free_matrix(pixel_mat);
    st_free_matrix(int_mat);
    st_free_matrix(mat);

    return 0;
}
