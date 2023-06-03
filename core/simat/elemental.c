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
__call_fp_elem(__st_data *data, fp_elem fp, void *argv[])
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
st_mat_elemental(st_vector *mat, fp_elem fp, void *argv[])
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

void st_mat_abs(st_vector *mat)
{
    st_mat_elemental(mat, __abs, NULL);
}
