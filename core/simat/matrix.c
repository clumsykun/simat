#include <string.h>
#include "dtypes.h"
#include "matrix.h"

static void
check_mat_shape(st_matrix *mat, size_t nrow, size_t ncol)
{
    if (mat->nrow != nrow)
        __st_raise_length_error();

    if (mat->ncol != ncol)
        __st_raise_length_error();

    __st_check();
}

double st_mat_min(st_matrix *mat)
{
    double min = st_mat_access(mat, 0, 0);
    void *p;
    for __st_iter_data(p, mat->data)
        min = (min <= st_access_p(p, mat->data->dtype)
                   ? min
                   : st_access_p(p, mat->data->dtype));

    return min;
}

double st_mat_max(st_matrix *mat)
{
    double max = st_mat_access(mat, 0, 0);
    void *p;
    for __st_iter_data(p, mat->data)
        max = (max >= st_access_p(p, mat->data->dtype)
                   ? max
                   : st_access_p(p, mat->data->dtype));

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

    for __st_iter_data(p, mat->data) {
        scaled = min + (st_access_p(p, mat->data->dtype) - mat_min) * target_scale / scale;
        __st_assign_p(p, scaled, mat->data->dtype);
    }

    __st_check();
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

/* copy the input matrix in transpose form */
st_matrix *st_mat_copy_t(st_matrix *mat)
{
    st_matrix *t;
    switch (mat->dtype) {

        case __st_bool:
            t = st_new_bool_matrix(mat->ncol, mat->nrow);
            break;

        case __st_pixel:
            t = st_new_pixel_matrix(mat->ncol, mat->nrow);
            break;

        case __st_int:
            t = st_new_int_matrix(mat->ncol, mat->nrow);
            break;

        case __st_double:
            t = st_new_matrix(mat->ncol, mat->nrow);
            break;

        default:
            __st_raise_dtype_error();
    }

    __st_check();

    void *p;
    size_t irow, icol;
    for __st_iter_matrix(irow, icol, p, mat) {
        memcpy(__st_mat_find_p(t, icol, irow), p, mat->data->nbyte);
    }

    __st_check();
    return t;
}

st_matrix *
__mat_dot_double(st_matrix *a, st_matrix *b)
{
    if (a->ncol != b->nrow) {
        __st_raise_length_error();
        __st_check();
    }

    st_matrix *r = st_new_matrix(a->nrow, b->ncol);
    double (*pa)[a->nrow][a->ncol] = a->data->head;
    double (*pb)[b->nrow][b->ncol] = b->data->head;
    double (*pr)[r->nrow][r->ncol] = r->data->head;
    double tmp;

    for (size_t i = 0; i < a->nrow; i++) {
        for (size_t j = 0; j < b->ncol; j++) {

            tmp = 0;
            for (size_t k = 0; k < a->ncol; k++)
                tmp += (*pa)[i][k] * (*pb)[k][j];

            (*pr)[i][j] = tmp;
        }
    }

    return r;
}

st_matrix *
st_mat_dot(st_matrix *a, st_matrix *b)
{
    if (a->dtype != b->dtype)
        return NULL;

    /* optimized method in case of same dtype */
    switch (a->dtype) {

        case __st_bool:
            return NULL;
    
        case __st_pixel:
            return NULL;

        case __st_int:
            return NULL;
    
        case __st_double:
            return __mat_dot_double(a, b);

        default:
            __st_raise_dtype_error();
    }
    __st_check();
}
