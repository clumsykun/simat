#include <string.h>
#include "st_d_matrix.h"

static st_matrix *
__mat_dot_double(st_matrix *a, st_matrix *b)
{
    if (a->ncol != b->nrow)
        __st_raise_length_error();

    st_matrix *r = st_new_matrix(a->nrow, b->ncol, st_dtype_d64);
    st_d64 (*pa)[a->nrow][a->ncol] = a->data->head;
    st_d64 (*pb)[b->nrow][b->ncol] = b->data->head;
    st_d64 (*pr)[r->nrow][r->ncol] = r->data->head;
    st_d64 tmp;

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

// st_decimal
// st_mat_min(st_matrix *mat)
// {
//     st_d64 min = st_mat_access(mat, 0, 0);
//     void *p;
//     for __st_iter_data(p, mat->data)
//         min = (min <= __st_access_p(p, mat->data->dtype)
//                    ? min
//                    : __st_access_p(p, mat->data->dtype));

//     return min;
// }

// st_decimal
// st_mat_max(st_matrix *mat)
// {
//     st_d64 max = st_mat_access(mat, 0, 0);
//     void *p;
//     for __st_iter_data(p, mat->data)
//         max = (max >= __st_access_p(p, mat->data->dtype)
//                    ? max
//                    : __st_access_p(p, mat->data->dtype));

//     return max;
// }

void
st_mat_scale(st_matrix *mat, st_d64 min, st_d64 max)
{
    if st_is_bool(mat) /* do nothing */
        return;

    st_d64 mat_min = st_mat_min(mat);
    st_d64 scale = st_mat_max(mat) - mat_min;
    st_d64 target_scale = max - min;
    st_d64 scaled;
    void *p;

    for __st_iter_data(p, mat->data) {
        scaled = min + (__st_access_p(p, mat->data->dtype) - mat_min) * target_scale / scale;
        __st_assign_p(p, scaled, mat->data->dtype);
    }
}

st_matrix *
st_mat_copy(st_matrix *mat)
{
    st_matrix *copy = st_new_matrix(
        mat->nrow,
        mat->ncol,
        mat->dtype);

    memcpy(
        copy->data->head,
        mat->data->head,
        mat->data->nbyte*mat->data->size);

    copy->temp = mat->temp;
    return copy;
}

/* copy the input matrix in transpose form */
st_matrix *
st_mat_copy_t(st_matrix *mat)
{
    void *p;
    size_t irow, icol;
    st_matrix *t = st_new_matrix(
        mat->ncol,
        mat->nrow,
        mat->dtype);

    for __st_iter_matrix(irow, icol, p, mat)
        memcpy(
            __st_mat_find_p(t, icol, irow),
            p,
            mat->data->nbyte);

    return t;
}

st_matrix *
st_mat_dot(st_matrix *a, st_matrix *b)
{
    if (a->dtype != b->dtype)
        return NULL;

    /* specified method in order to optimize speed */
    switch (a->dtype) {

        case st_dtype_bool:
            return NULL;
    
        case st_dtype_u8:
            return NULL;

        case st_dtype_i32:
            return NULL;
    
        case st_dtype_d64:
            return __mat_dot_double(a, b);

        default:
            __st_raise_dtype_error();
    }
}
