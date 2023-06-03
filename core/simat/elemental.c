#include "elemental.h"
#include "cblas.h"

/* =================================================================================================
 * elemental function
 */

static void
__abs(void *p, __st_dtype dtype, void *argv[])
{
    double value = __st_access_p(p, dtype);
    value = st_abs(st_abs(value));
    __st_assign_p(p, value, dtype);
}

/* assign smaller value of `p` and `argv[0]` to `argv[0]` */
static void
__min(void *p, __st_dtype dtype, void *argv[])
{
    double *min = (double *)argv[0];
    double value = __st_access_p(p, dtype);
    *min = (*(min) < value ? *(min) : value);
}

/* assign sum value of `p` and `argv[0]` to `argv[0]` */
static void
__sum(void *p, __st_dtype dtype, void *argv[])
{
    double *sum = (double *)argv[0];
    double value = __st_access_p(p, dtype);
    *sum = (*sum) + value;
}

/* =================================================================================================
 * call elemental function
 */

double
__call_fp_elem(__st_data *data, fp_elem fp, void *argv[])
{
    void *p;
    for __st_iter_data(p, data)
        fp(p, data->dtype, argv);
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
    void **p;
    size_t i;
    double value;
    for __st_iter_view(i, p, view)
        fp(*p, view->dtype, argv);
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
    void *p = &min;
    st_vec_elemental(vec, __min, &p);
    return min;

}

double
st_vec_sum(st_vector *vec)
{
    if st_is_double (vec)
        return cblas_dsum(vec->len, vec->data->head, 1);

    double sum = 0;
    void *p = &sum;

    st_vec_elemental(vec, __sum, &p);
    return sum;
}

/* =================================================================================================
 * matrix elemental function
 */

void st_mat_abs(st_vector *mat)
{
    st_mat_elemental(mat, __abs, NULL);
}
