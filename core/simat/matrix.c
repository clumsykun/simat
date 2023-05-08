#include "dtypes.h"
#include "vector.h"
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
