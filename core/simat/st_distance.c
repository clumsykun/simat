#include <math.h>
#include "st_distance.h"

st_d64
st_dist_euclid(st_vector *a, st_vector *b)
{
    st_check_vec_len(a, b->len);
    st_d64 diff, sum_square = 0;
    size_t i;
    void *pa, *pb;
    for __st_iter_vector2(i, pa, pb, a, b) {
            diff = __st_access_p(pa, a->dtype) - __st_access_p(pb, b->dtype);
            sum_square += diff * diff;
    }

    return sqrt(sum_square);
}

/* cosine similarity of vector v1 and v2. */
st_d64
st_dist_cosine(st_vector *a, st_vector *b)
{
    st_check_vec_len(a, b->len);
    return st_vec_dot(a,b)/(st_vec_norm(a)*st_vec_norm(b));
}

/* manhattan distance of vector v1 and v2. */
st_d64
st_dist_manhattan(st_vector *a, st_vector *b)
{
    st_check_vec_len(a, b->len);
    st_d64 diff, dist = 0;
    size_t i;
    void *pa, *pb;

    for __st_iter_vector2(i, pa, pb, a, b) {
        diff = __st_access_p(pa, a->dtype) - __st_access_p(pb, b->dtype);
        dist += st_abs(diff);
    }

    return dist;
}

st_d64
st_dist_chebyshev(st_vector *a, st_vector *b)
{
    st_check_vec_len(a, b->len);
    st_d64 diff, dist = 0;
    size_t i;
    void *pa, *pb;

    for __st_iter_vector2(i, pa, pb, a, b) {
        diff = __st_access_p(pa, a->dtype) - __st_access_p(pb, b->dtype);
        dist = (st_abs(diff) > dist ? st_abs(diff) : dist);
    }

    return dist;
}

st_d64
st_dist_cos_ww(st_view *w1, st_view *w2)
{
    return st_view_dot(w1,w2)/(st_view_norm(w1)*st_view_norm(w2));
}

/* implement distance function of matrix by every row. */
void
st_dist_mat_row(st_matrix *re, st_matrix *mat, dist_fp fp)
{
    // st_check_mat_shape(re, mat->nrow, mat->nrow);
    st_check_mat_nrow(re, mat->nrow);
    st_check_mat_ncol(re, mat->nrow);

    st_d64 v;

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
}
