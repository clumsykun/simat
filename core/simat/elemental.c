#include "elemental.h"
#include "cblas.h"

/* =================================================================================================
 * elemental function
 */

static void
__abs(void *elem, __st_dtype dtype, void *argv[])
{
    double value = __st_access_p(elem, dtype);
    value = st_abs(st_abs(value));
    __st_assign_p(elem, value, dtype);
}

/* assign smaller value of `p` and `argv[0]` to `argv[0]` */
static void
__min(void *elem, __st_dtype dtype, void *argv[])
{
    double *min = (double *)argv[0];
    double value = __st_access_p(elem, dtype);
    *min = (*(min) < value ? *(min) : value);
}

/* assign bigger value of `p` and `argv[0]` to `argv[0]` */
static void
__max(void *elem, __st_dtype dtype, void *argv[])
{
    double *max = (double *)argv[0];
    double value = __st_access_p(elem, dtype);
    *max = (*(max) > value ? *(max) : value);
}

/* assign sum value of `p` and `argv[0]` to `argv[0]` */
static void
__sum(void *elem, __st_dtype dtype, void *argv[])
{
    double *sum = (double *)argv[0];
    double value = __st_access_p(elem, dtype);
    *sum = (*sum) + value;
}

/* =================================================================================================
 * call elemental function
 */

double
__call_fp_elem(const __st_data *data, fp_elem fp, void *argv[])
{
    void *elem;
    for __st_iter_data(elem, data)
        fp(elem, data->dtype, argv);
}

double
st_vec_elemental(st_vector *vec, fp_elem fp, void *argv[])
{
    return __call_fp_elem(vec->data, fp, argv);
}

double
st_mat_elemental(st_matrix *mat, fp_elem fp, void *argv[])
{
    return __call_fp_elem(mat->data, fp, argv);
}

double
st_view_elemental(st_view *view, fp_elem fp, void *argv[])
{
    void **elem;
    size_t i;
    double value;
    for __st_iter_view(i, elem, view)
        fp(*elem, view->dtype, argv);
}

/* =================================================================================================
 * vector elemental function
 */

void
st_vec_abs(st_vector *vec)
{
    st_vec_elemental(vec, __abs, NULL);
}

double
st_vec_min(st_vector *vec)
{
    if st_is_double(vec)
        return st_vec_access(vec, cblas_idmin(vec->len, vec->data->head, 1));

    double min = st_vec_access(vec, 0);
    void *argv[] = {&min};

    st_vec_elemental(vec, __min, argv);
    return min;
}

double
st_vec_max(st_vector *vec)
{
    if st_is_double (vec)
        return st_vec_access(vec, cblas_idmax(vec->len, vec->data->head, 1));

    double max = st_vec_access(vec, 0);
    void *argv[] = {&max};

    st_vec_elemental(vec, __max, argv);
    return max;
}

double
st_vec_sum(st_vector *vec)
{
    if st_is_double (vec)
        return cblas_dsum(vec->len, vec->data->head, 1);

    double sum = 0;
    void *argv[] = {&sum};

    st_vec_elemental(vec, __sum, argv);
    return sum;
}

double
st_vec_norm(st_vector *vec)
{
    return cblas_dnrm2(vec->len, vec->data->head, 1);
}

/* =================================================================================================
 * matrix elemental function
 */

void
st_mat_abs(st_matrix *mat)
{
    st_mat_elemental(mat, __abs, NULL);
}

double
st_mat_min(st_matrix *mat)
{
    if st_is_double(mat) {
        size_t idx = cblas_idmin(mat->nrow*mat->ncol, mat->data->head, 1);
        void *p = __st_data_find_p(mat->data, idx);
        return __st_access_p(p, mat->dtype);
    }

    double min = __st_mat_access(mat, 0, 0);
    void *argv[] = {&min};

    st_mat_elemental(mat, __min, argv);
    return min;
}

double
st_mat_max(st_matrix *mat)
{
    if st_is_double(mat) {
        size_t idx = cblas_idmax(mat->nrow * mat->ncol, mat->data->head, 1);
        void *p = __st_data_find_p(mat->data, idx);
        return __st_access_p(p, mat->dtype);
    }

    double max = __st_mat_access(mat, 0, 0);
    void *argv[] = {&max};

    st_mat_elemental(mat, __max, argv);
    return max;
}

double
st_mat_sum(st_matrix *mat)
{
    if st_is_double(mat)
        return cblas_dsum(mat->nrow * mat->ncol, mat->data->head, 1);

    double sum = 0;
    void *argv[] = {&sum};

    st_mat_elemental(mat, __sum, argv);
    return sum;
}

/* =================================================================================================
 * pair function
 */

/* assign multiply value of `l` and `r` to `r` */
static void
__pair_mul(void *el, void *er, __st_dtype dtype, void *argv[])
{
    double v = __st_access_p(el, dtype);
    v = v * __st_access_p(er, dtype);
    __st_assign_p(er, v, dtype);
}

/* add value of `l` to value of `r` */
static void

__pair_add(void *el, void *er, __st_dtype dtype, void *argv[])
{
    double v = __st_access_p(el, dtype);
    v = v + __st_access_p(er, dtype);
    __st_assign_p(er, v, dtype);
}

/* =================================================================================================
 * call pair function
 */

double
st_vec_pair(st_vector *vl, st_vector *vr, fp_pair fp, void *argv[])
{
    __st_dtype dtype = st_check_vec_dtype(vl, vr->dtype);

    size_t i;
    void *e1, *e2;
    for __st_iter_vector2(i, e1, e2, vl, vr)
            fp(e1, e2, dtype, argv);
}

/* implement vector elemental multiply of a and b, save result to vector re */
st_vector *
st_vec_mul(st_vector *a, st_vector *b)
{
    st_check_vec_dtype(a, b->dtype);
    st_check_vec_len(a, b->len);

    st_vector *r = st_vec_copy(a);
    void *eb, *er;
    st_vec_pair(b, r, __pair_mul, NULL);
    return r;
}

/* implement vector subtraction a-b, save result to vector re */
st_vector *
st_vec_add(st_vector *a, st_vector *b)
{
    st_check_vec_dtype(a, b->dtype);
    st_check_vec_len(a, b->len);

    st_vector *r = st_vec_copy(a);
    void *eb, *er;
    st_vec_pair(b, r, __pair_add, NULL);
    return r;
}
