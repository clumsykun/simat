#include "elemental.h"


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

void
st_vec_abs(st_vector *vec)
{
    st_vec_elemental(vec, __abs, NULL);
}

void
st_mat_abs(st_vector *mat)
{
    st_mat_elemental(mat, __abs, NULL);
}
