#include <math.h>
#include <immintrin.h>
#include "st_distance.h"

static double
__dist_euclid_double(size_t n, double *a, double *b)
{
    size_t bsize     = st_m_size_d64;
    size_t batches   = n / bsize;
    size_t remainder = n % bsize;

    st_md *pa = (st_md *) a;
    st_md *pb = (st_md *) b;

    st_md pk_sum_diff = st_m_zero_d();
    st_d64 arr_sum_diff[st_m_size_d64];
    st_d64 diff, sum_diff = 0;

    while (batches--) {

        st_md pk_a = st_load_d64((st_d64 *)pa++);
        st_md pk_b = st_load_d64((st_d64 *)pb++);
        st_md pk_diff = st_m_sub_d64(pk_a, pk_b);
        pk_diff = st_m_mul_d64(pk_diff, pk_diff);
        pk_sum_diff = st_m_add_d64(pk_sum_diff, pk_diff);
    }

    st_store_d64(arr_sum_diff, pk_sum_diff);

    for (size_t i = 0; i < st_m_size_d64; i++)
        sum_diff += arr_sum_diff[i];

    a = (st_d64 *)pa;
    b = (st_d64 *)pb;

    while (remainder--) {
        diff = (*a++) - (*b++);
        sum_diff += diff * diff;
    }

    return sqrt(sum_diff);
}


st_decimal
st_dist_euclid(st_vector *a, st_vector *b)
{
    if (st_check_vec_len(a, b->len))
        __st_raise_length_error();

    if (st_check_vec_dtype(a, b->dtype))
        __st_raise_dtype_error();

    size_t n = a->len;

    switch (a->dtype) {
        case st_dtype_d64:
            return __dist_euclid_double(n, a->data->head, b->data->head);
        
        default:
            return 0;
    }
}

/* cosine similarity of vector v1 and v2. */
st_decimal
st_dist_cosine(st_vector *a, st_vector *b)
{
    if (st_check_vec_len(a, b->len))
        __st_raise_length_error();

    return st_vec_dot(a,b)/(st_vec_norm(a)*st_vec_norm(b));
}

/* manhattan distance of vector v1 and v2. */
st_decimal
st_dist_manhattan(st_vector *a, st_vector *b)
{
    if (st_check_vec_len(a, b->len))
        __st_raise_dtype_error();

    st_d64 diff, dist = 0;
    size_t i;
    void *pa, *pb;

    for __st_iter_vector2(i, pa, pb, a, b) {
        diff = __st_access_p(pa, a->dtype) - __st_access_p(pb, b->dtype);
        dist += st_abs(diff);
    }

    return dist;
}

st_decimal
st_dist_chebyshev(st_vector *a, st_vector *b)
{
    if (st_check_vec_len(a, b->len))
        __st_raise_length_error();

    st_d64 diff, dist = 0;
    size_t i;
    void *pa, *pb;

    for __st_iter_vector2(i, pa, pb, a, b) {
        diff = __st_access_p(pa, a->dtype) - __st_access_p(pb, b->dtype);
        dist = (st_abs(diff) > dist ? st_abs(diff) : dist);
    }

    return dist;
}

st_decimal
st_dist_cos_ww(st_view *w1, st_view *w2)
{
    return st_view_dot(w1,w2)/(st_view_norm(w1)*st_view_norm(w2));
}

/* implement distance function of matrix by every row. */
void
st_dist_mat_row(st_matrix *re, st_matrix *mat, dist_fp fp)
{
    if (st_check_mat_nrow(re, mat->nrow))
        __st_raise_length_error();

    if (st_check_mat_ncol(re, mat->nrow))
        __st_raise_length_error();

    st_d64 v;

    for (size_t i = 0; i < mat->nrow; i++) {
        for (size_t j = 0; j < mat->nrow; j++) {

            if (i > j) {
                v = st_mat_access(re, j, i);
                __st_mat_assign(re, i, j, v);
            }
            else {
                v = fp(
                    st_mat_access_row(mat, i),
                    st_mat_access_row(mat, j));

                __st_mat_assign(re, i, j, v);
            }
        }
    }
}
