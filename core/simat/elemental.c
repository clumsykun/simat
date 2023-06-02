#include "elemental.h"


/* =================================================================================================
 * elemental function
 */

static void
__call_fp_elem(__st_data *data, fp_elem fp)
{
    void *p;
    double value;
    for __st_iter_data(p, data) {
        value = fp(__st_access_p(p, data->dtype));
        __st_assign_p(p, value, data->dtype);
    }
}

void
st_vec_elemental(st_vector *vec, fp_elem fp)
{
    __call_fp_elem(vec->data, fp);
}

void
st_mat_elemental(st_vector *mat, fp_elem fp)
{
    __call_fp_elem(mat->data, fp);
}

void
st_view_elemental(st_view *view, fp_elem fp)
{
    void **p;
    size_t i;
    double value;
    for __st_iter_view(i, p, view) {
        value = fp(__st_access_p(*p, view->dtype));
        __st_assign_p(*p, value, view->dtype);
    }
}

// static double
// __abs(double x)
// {
//     return st_abs(x);
// }

// void st_mat_abs(st_matrix *mat)
// {
//     st_mat_elemental(mat, __abs);
// }

// static double
// __abs(double x)
// {
//     return st_abs(x);
// }

// void
// st_vec_abs(st_vector *vec)
// {
//     st_vec_elemental(vec, __abs);
// }

