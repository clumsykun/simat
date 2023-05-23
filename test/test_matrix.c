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

    st_mat_scale(bool_mat, 0, 100);
    st_mat_display(bool_mat);
    printf("min: %.2f, max: %.2f\n", st_mat_min(bool_mat), st_mat_max(bool_mat));
    st_mat_scale(pixel_mat, 0, 100);
    st_mat_display(pixel_mat);
    printf("min: %.2f, max: %.2f\n", st_mat_min(pixel_mat), st_mat_max(pixel_mat));
    st_mat_scale(int_mat, 0, 100);
    st_mat_display(int_mat);
    printf("min: %.2f, max: %.2f\n", st_mat_min(int_mat), st_mat_max(int_mat));
    st_mat_scale(mat, 0, 100);
    st_mat_display(mat);
    printf("min: %.2f, max: %.2f\n", st_mat_min(mat), st_mat_max(mat));

    st_view *view = st_new_view();
    st_view *view2 = st_new_view();
    st_matrix_view_col(view, mat, 3);
    st_view_display(view);

    st_matrix_view_row(view, mat, 2);
    st_matrix_view_row(view2, mat, 3);
    st_view_display(view);

    st_view_rand(view);
    st_mat_display(mat);

    st_view_scale(view, 0, 100);
    st_mat_display(mat);

    st_view_sort(view);
    st_mat_display(mat);

    st_view_reverse(view);
    st_mat_display(mat);

    printf("norm of row [2]: %.2f\n", st_view_norm(view));
    printf("dot of row [2] and row [3]: %.2f\n", st_view_dot(view, view));

    st_vector *v1 = st_mat_access_col(mat, 1);
    st_vector *v2 = st_mat_access_col(mat, 2);

    st_vec_sub(v1, v1, v2);
    st_vec_display(v1);
    st_mat_display(mat);

    st_vec_assign_all(v1, 2);
    st_vec_assign_all(v2, 4);

    st_vec_display(v1);
    st_vec_display(v2);
    printf("dot of col 1 and col 2: %.2f\n", st_vec_dot(v1, v2));

    st_matrix *dist_mat = st_new_matrix(mat->nrow, mat->nrow);
    st_mat_assign_all(dist_mat, -1);
    st_mat_display(dist_mat);
    st_dist_cos_mat_row(dist_mat, mat);
    st_mat_display(dist_mat);

    st_free_matrix(bool_mat);
    st_free_matrix(pixel_mat);
    st_free_matrix(int_mat);
    st_free_matrix(mat);

    return 0;
}
