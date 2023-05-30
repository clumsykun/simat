#include "dtypes.h"
#include <string.h>
#include "matrix.h"

double st_mat_min(st_matrix *mat)
{
    double min = st_mat_access(mat, 0, 0);
    void *p;
    for st_iter_matrix(p, mat)
        min = (min <= __st_access_p(p, mat->data->dtype)
                   ? min
                   : __st_access_p(p, mat->data->dtype));

    return min;
}

double st_mat_max(st_matrix *mat)
{
    double max = st_mat_access(mat, 0, 0);
    void *p;
    for st_iter_matrix(p, mat)
        max = (max >= __st_access_p(p, mat->data->dtype)
                   ? max
                   : __st_access_p(p, mat->data->dtype));

    return max;
}

void st_mat_scale(st_matrix *mat, double min, double max)
{
    if st_is_bool(mat) /* do nothing */
        return;

    double mat_min = st_mat_min(mat);
    double scale = st_mat_max(mat) - mat_min;
    double target_scale = max - min;
    double scaled;
    void *p;

    for st_iter_matrix(p, mat) {
        scaled = min + (__st_access_p(p, mat->data->dtype) - mat_min) * target_scale / scale;
        __st_assign_p(p, scaled, mat->data->dtype);
    }

    __st_check();
}

st_matrix *st_mat_t(st_matrix *mat)
{
    // TODO: specify dtype.
    st_matrix *t = st_new_matrix(mat->ncol, mat->nrow);

    for (size_t i = 0; i < mat->nrow; i++) {
        for (size_t j = 0; j < mat->ncol; j++) {
            st_mat_assign(
                t,
                j,
                i,
                st_mat_access(mat, i, j)
            );
        }
    }
    return t;
}

st_matrix * st_mat_copy(st_matrix *mat)
{
    st_matrix *copy;

    switch (mat->dtype) {

        case __st_bool:
            copy = st_new_bool_matrix(mat->nrow, mat->ncol);
            break;
        
        case __st_pixel:
            copy = st_new_pixel_matrix(mat->nrow, mat->ncol);
            break;

        case __st_int:
            copy = st_new_int_matrix(mat->nrow, mat->ncol);
            break;

        case __st_double:
            copy = st_new_matrix(mat->nrow, mat->ncol);
            break;

        default:
            __st_raise_dtype_error();
    }

    __st_check();

    memcpy(copy->data->head,
           mat->data->head,
           mat->data->nbyte*mat->data->size);

    return copy;
}
