#include <math.h>
#include "distance.h"

static void
check_vec_length(st_vector *a, st_vector *b)
{
    if (a->len != b->len)
        __st_raise_length_error();

    __st_check();
}

static void
check_mat_shape(st_matrix *mat, size_t nrow, size_t ncol)
{
    if (mat->nrow != nrow)
        __st_raise_length_error();

    if (mat->ncol != ncol)
        __st_raise_length_error();

    __st_check();
}

double
st_dist_euclid(st_vector *a, st_vector *b)
{
    check_vec_length(a, b);
    double diff, sum_square = 0;

    for (size_t i = 0; i < a->len; i++) {

        diff = __st_vec_access(a, i) - __st_vec_access(b, i);
        sum_square += diff*diff;
    }

    return sqrt(sum_square);
}

/* cosine similarity of vector v1 and v2. */
double
st_dist_cosine(st_vector *a, st_vector *b)
{
    check_vec_length(a, b);
    return st_vec_dot(a,b)/(st_vec_norm(a)*st_vec_norm(b));
}

/* manhattan distance of vector v1 and v2. */
double
st_dist_manhattan(st_vector *a, st_vector *b)
{
    check_vec_length(a, b);
    double dist = 0;
    for (size_t i = 0; i < a->len; i++)
        dist += fabs(__st_vec_access(a, i)-__st_vec_access(b, i));

    return dist;
}

double
st_dist_chebyshev(st_vector *a, st_vector *b)
{
    check_vec_length(a, b);
    double dist = 0;

    for (size_t i = 0; i < a->len; i++)
        dist = (fabs(__st_vec_access(a, i) - __st_vec_access(b, i)) > dist
                ? fabs(__st_vec_access(a, i) - __st_vec_access(b, i))
                : dist);

    return dist;
}

double
st_dist_cos_ww(st_view *w1, st_view *w2)
{
    return st_view_dot(w1,w2)/(st_view_norm(w1)*st_view_norm(w2));
}

/* implement distance function of matrix by every row. */
void
st_dist_mat_row(st_matrix *re, st_matrix *mat, dist_fp fp)
{
    check_mat_shape(re, mat->nrow, mat->nrow);
    double v;

    for (size_t i = 0; i < mat->nrow; i++) {
        for (size_t j = 0; j < mat->nrow; j++) {

            if (i > j) {
                v = __st_mat_access(re, j, i);
                __st_mat_assign(re, i, j, v);
            }
            else {
                v = fp(
                    __st_mat_access_row(mat, i),
                    __st_mat_access_row(mat, j));

                __st_mat_assign(re, i, j, v);
            }
        }
    }
    __st_check();
}
