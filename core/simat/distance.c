#include "distance.h"

static void check_mat_shape(st_matrix *mat, size_t nrow, size_t ncol)
{
    if (mat->nrow != nrow)
        __st_raise_length_error();

    if (mat->ncol != ncol)
        __st_raise_length_error();

    __st_check();
}

/* cosine similarity of vector v1 and v2. */
double st_dist_cos_vv(st_vector *v1, st_vector *v2)
{
    return st_vec_dot(v1,v2)/(st_vec_norm(v1)*st_vec_norm(v2));
}

double st_dist_cos_ww(st_view *w1, st_view *w2)
{
    return st_view_dot(w1,w2)/(st_view_norm(w1)*st_view_norm(w2));
}

/* cosine similarity of matrix by every row. */
void st_dist_cos_mat_row(st_matrix *re, st_matrix *mat)
{
    check_mat_shape(re, mat->nrow, mat->nrow);
    st_view *rows[mat->nrow];

    for (size_t i = 0; i < mat->nrow; i++) {
        rows[i] = st_new_view();
        st_matrix_view_row(rows[i], mat, i);
        st_view_display(rows[i]);
    }

    for (size_t i = 0; i < mat->nrow; i++) {
        for (size_t j = 0; j < mat->nrow; j++) {

            if (i > j)
                st_mat_assign(re, i, j, st_mat_access(re, j, i));
            else
                st_mat_assign(re, i, j, st_dist_cos_ww(rows[i], rows[j]));
        }
    }
}
