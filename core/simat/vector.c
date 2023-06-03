#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "vector.h"
#include "cblas.h"

typedef double (*fp_single)(double);
typedef double (*fp_pair)(double, double);

double
st_vec_access(st_vector *vec, size_t idx)
{
    return 0;
}

static void
__min(void *p, __st_dtype dtype, void *argv[])
{
    double *min = (double *)argv[0];
    double value = __st_access_p(p, dtype);
    *min = (*(min) < value ? *(min) : value);
}

double
st_vec_min(st_vector *vec)
{
    switch (vec->dtype) {

        case __st_double: {
            size_t idx = cblas_idmin(vec->len, vec->data->head, 1);
            return __st_vec_access(vec, idx);
        }

        default: {
            double min = __st_vec_access(vec, 0);
            void *p = &min;
            st_vec_elemental(vec, __min, &p);
            return min;
        }
    }
}

double
st_vec_max(st_vector *vec)
{
    double max = __st_access_p(vec->data->head, vec->dtype);
    void *p;

    for __st_iter_data(p, vec->data)
        max = (max >= __st_access_p(p, vec->dtype)
               ? max
               : __st_access_p(p, vec->dtype));

    __st_check();
    return max;
}

double
st_vec_norm(st_vector *vec)
{
    return cblas_dnrm2(vec->len, vec->data->head, 1);
}

/* scale the vector to make sure that its max value and min value match `max` and `min`. */
void
st_vec_scale(st_vector *vec, double min, double max)
{
    if st_is_bool(vec) /* do noting */
        return;

    double vec_min = st_vec_min(vec);
    double scale = st_vec_max(vec) - vec_min;
    double target_scale = max - min;
    double scaled;
    void *p;

    for __st_iter_data(p, vec->data) {
        scaled = min + (__st_access_p(p, vec->dtype) - vec_min) * target_scale / scale;
        __st_assign_p(p, scaled, vec->dtype);
    }

    __st_check();
}

void
st_vec_sub_scalar(st_vector *vec, double value)
{
    void *p;
    for __st_iter_data(p, vec->data)
        __st_assign_p(p, __st_access_p(p, vec->dtype)-value, vec->dtype);
}

void
st_vec_mul_scalar(st_vector *vec, double value)
{
    void *p;
    for __st_iter_data(p, vec->data)
        __st_assign_p(p, __st_access_p(p, vec->dtype)*value, vec->dtype);
}

static st_vector *
__call_pair_fp(st_vector *a, st_vector *b, fp_pair fp)
{
    st_check_vec_len(a, b->len);

    double va, vb;
    void *pa, *pb, *pr;
    size_t i;
    __st_dtype dtype = (a->dtype > b->dtype ? a->dtype : b->dtype);
    st_vector *re;

    switch (dtype) {
        case __st_bool:
            re = st_new_bool_vector(a->len);
            break;

        case __st_pixel:
            re = st_new_pixel_vector(a->len);
            break;

        case __st_int:
            re = st_new_int_vector(a->len);
            break;

        case __st_double:
            re = st_new_vector(a->len);
            break;

        default:
            __st_raise_dtype_error();
    }

    __st_check();

    for __st_iter_vector3(i, pa, pb, pr, a, b, re) {
        va = __st_access_p(pa, a->dtype);
        vb = __st_access_p(pb, b->dtype);
        __st_assign_p(pr, fp(va, vb), re->dtype);
    }

    __st_check();
    return re;
}

static double
__add(double a, double b)
{
    return a+b;
}

/* implement vector subtraction a-b, save result to vector re */
st_vector *
st_vec_add(st_vector *a, st_vector *b)
{
    return __call_pair_fp(a, b, __add);
}

static double
__sub(double a, double b)
{
    return a-b;
}

/* implement vector subtraction a-b, save result to vector re */
st_vector *
st_vec_sub(st_vector *a, st_vector *b)
{
    return __call_pair_fp(a, b, __sub);
}

static double
__mul(double a, double b)
{
    return a*b;
}

/* implement vector elemental multiply of a and b, save result to vector re */
st_vector *
st_vec_mul(st_vector *a, st_vector *b)
{
    return __call_pair_fp(a, b, __mul);
}

static double
__div(double a, double b)
{
    return a/b;
}

/* implement vector elemental division of a and b, save result to vector re */
st_vector *
st_vec_div(st_vector *a, st_vector *b)
{
    return __call_pair_fp(a, b, __div);
}

/* implement vector dot production a·b, return result */
double
st_vec_dot(st_vector *a, st_vector *b)
{
    st_check_vec_len(a, b->len);

    double re = 0;
    void *pa, *pb;
    size_t i;
    for __st_iter_vector2(i, pa, pb, a, b)
        re += __st_access_p(pa, a->dtype) * __st_access_p(pb, b->dtype);

    __st_check();
    return re;
}

bool
st_vec_equal(st_vector *a, st_vector *b)
{
    if (&a == &b)
        return true;

    if (a->len != b->len)
        return false;

    bool is_equal = true;

    for (size_t i = 0; i < a->len; i++)
        if (__st_vec_access(a, i) != __st_vec_access(b, i))
            is_equal = false;
    
    return is_equal;
}
