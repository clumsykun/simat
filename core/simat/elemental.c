#include "elemental.h"


/* =================================================================================================
 * elemental function
 */

static double
__abs(double x, void *argv[])
{
    return st_abs(x);
}

/* =================================================================================================
 * call elemental function
 */

static void
__call_fp_elem(__st_data *data, fp_elem fp, void *argv[])
{
    void *p;
    double value;
    for __st_iter_data(p, data) {
        value = fp(__st_access_p(p, data->dtype), argv);
        __st_assign_p(p, value, data->dtype);
    }
}

double
st_vec_elemental(st_vector *vec, fp_elem fp, void *argv[])
{
    __call_fp_elem(vec->data, fp, argv);
}

double
st_mat_elemental(st_vector *mat, fp_elem fp, void *argv[])
{
    __call_fp_elem(mat->data, fp, argv);
}

double
st_view_elemental(st_view *view, fp_elem fp, void *argv[])
{
    void **p;
    size_t i;
    double value;
    for __st_iter_view(i, p, view) {
        value = fp(__st_access_p(*p, view->dtype), argv);
        __st_assign_p(*p, value, view->dtype);
    }
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
