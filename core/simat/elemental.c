#include <math.h>
#include <immintrin.h>
#include "elemental.h"
#include "cblas.h"

/* =================================================================================================
 * call elemental function
 */

// /* call elemental function of double */
// static void
// __call_elem_d(size_t len, st_elemental *elemental, double *head, void *argv[])
// {
//     fp_elem_d fp = elemental->d;

//     if (fp == NULL)
//         return;

//     while (len--) {
//         fp(head++, argv);
//     }
// }

// /* call elemental function of integer */
// static void
// __call_elem_i(size_t len, st_elemental *elemental, int *head, void *argv[])
// {
//     fp_elem_i fp = elemental->i;

//     if (fp == NULL)
//         return;

//     while (len--) {
//         fp(head++, argv);
//     }
// }

// /* call elemental function of pixel */
// static void
// __call_elem_p(size_t len, st_elemental *elemental, unsigned char *head, void *argv[])
// {
//     fp_elem_p fp = elemental->p;

//     if (fp == NULL)
//         return;

//     while (len--) {
//         fp(head++, argv);
//     }
// }

// /* call elemental function of bool */
// static void
// __call_elem_b(size_t len, st_elemental *elemental, bool *head, void *argv[])
// {
//     fp_elem_b fp = elemental->b;

//     if (fp == NULL)
//         return;

//     while (len--) {
//         fp(head++, argv);
//     }
// }

// static void
// __data_elemental(__st_data *data, st_elemental *elemental, void *argv[])
// {
//     switch (data->dtype) {
//         case st_double:
//             __call_elem_d(data->size, elemental, data->head, argv);
//             break;

//         case st_int:
//             __call_elem_i(data->size, elemental, data->head, argv);
//             break;

//         case st_pixel:
//             __call_elem_p(data->size, elemental, data->head, argv);
//             break;

//         case st_bool:
//             __call_elem_b(data->size, elemental, data->head, argv);
//             break;

//         default:
//             __st_raise_dtype_error();
//     }
// }

/** ================================================================================================
 * vectorized `abs` function
 * need SIMD !
 */

static void
__abs_d(size_t n, double *elem)
{
    while (n--)
        *elem++ = st_abs(*elem);
}

static void
__abs_i(size_t n, int *elem)
{
    while (n--)
        *elem++ = st_abs(*elem);
}

static void
__data_abs(const __st_data *data)
{
    switch (data->dtype) {
        case st_double:
            __abs_d(data->size, data->head);
            return;

        case st_int:
            __abs_i(data->size, data->head);
            return;

        case st_pixel:
            return;

        case st_bool:
            return;

        default:
            __st_raise_dtype_error();
    }
}

void
st_vec_abs(st_vector *vec)
{
    __data_abs(vec->data);
}

void
st_mat_abs(st_matrix *mat)
{
    __data_abs(mat->data);
}

/** ================================================================================================
 * vectorized `min` function
 * need SIMD!
 */

static double
simd_min_i(size_t n, int *elem, const size_t incx)
{
    double min = *elem;
    while (n--) {
        min = (*elem < min ? *elem : min);
        elem++;
    }
    return min;
}

static double
simd_min_p(size_t n, unsigned char *elem, const size_t incx)
{
    double min = *elem;
    while (n--) {
        min = (*elem < min ? *elem : min);
        min = __st_trim_pixel(min);
        elem++;
    }
    return min;
}

static double
simd_min_b(size_t n, bool *elem, const size_t incx)
{
    double min = *elem;
    while (n--)
        min = (*elem) && min;

    return min;
}

static double
__data_min(const __st_data *data, const size_t incx)
{
    switch (data->dtype) {
        case st_double:
            return __st_data_access(
                data,
                cblas_idmin(data->size, data->head, incx));

        case st_int:
            return simd_min_i(data->size, data->head, incx);

        case st_pixel:
            return simd_min_p(data->size, data->head, incx);

        case st_bool:
            return simd_min_b(data->size, data->head, incx);

        default:
            __st_raise_dtype_error();
    }
}

double
st_vec_min(st_vector *vec)
{
    return __data_min(vec->data, 1);
}

double
st_mat_min(st_matrix *mat)
{
    return __data_min(mat->data, 1);
}

/** ================================================================================================
 * vectorized `max` function
 * need SIMD!
 */

static double
simd_max_i(size_t n, int *elem, const size_t incx)
{
    double max = *elem;
    while (n--) {
        max = (*elem > max ? *elem : max);
        elem++;
    }
    return max;
}

static double
simd_max_p(size_t n, unsigned char *elem, const size_t incx)
{
    double max = *elem;
    while (n--) {
        max = (*elem > max ? *elem : max);
        max = __st_trim_pixel(max);
        elem++;
    }
    return max;
}

static double
simd_max_b(size_t n, bool *elem, const size_t incx)
{
    double max = *elem;
    while (n--)
        max = (*elem) || max;

    return max;
}

static double
__data_max(const __st_data *data, const size_t incx)
{
    switch (data->dtype) {
        case st_double:
            return __st_data_access(
                data,
                cblas_idmax(data->size, data->head, incx));

        case st_int:
            return simd_max_i(data->size, data->head, incx);

        case st_pixel:
            return simd_max_p(data->size, data->head, incx);

        case st_bool:
            return simd_max_b(data->size, data->head, incx);

        default:
            __st_raise_dtype_error();
    }
}

double
st_vec_max(st_vector *vec)
{
    return __data_max(vec->data, 1);
}

double
st_mat_max(st_matrix *mat)
{
    return __data_max(mat->data, 1);
}

/** ================================================================================================
 * vectorized `sum` function
 * need SIMD!
 */

static double
simd_sum_i(size_t n, int *elem, const size_t incx)
{
    double sum = 0;
    while (n--)
        sum += *elem++;

    return sum;
}

static double
simd_sum_p(size_t n, unsigned char *elem, const size_t incx)
{
    double sum = 0;
    while (n--)
        sum += *elem++;

    return sum;
}

static double
simd_sum_b(size_t n, bool *elem, const size_t incx)
{
    double sum = 0;
    while (n--)
        sum += *elem++;

    return sum;
}

static double
__data_sum(const __st_data *data, const size_t incx)
{
    switch (data->dtype) {
        case st_double:
            return cblas_dsum(data->size, data->head, incx);

        case st_int:
            return simd_sum_i(data->size, data->head, incx);

        case st_pixel:
            return simd_sum_p(data->size, data->head, incx);

        case st_bool:
            return simd_sum_b(data->size, data->head, incx);

        default:
            __st_raise_dtype_error();
    }
}

double
st_vec_sum(st_vector *vec)
{
    return __data_sum(vec->data, 1);
}

double
st_mat_sum(st_matrix *mat)
{
    return __data_sum(mat->data, 1);
}

/** ================================================================================================
 * vectorized `square_sum` function
 * need SIMD!
 */

static double
simd_sum_square_i(size_t n, int *elem)
{
    double sum = 0;
    while (n--) {
        sum += (*elem)*(*elem);
        elem++;
    }

    return sum;
}

static double
simd_sum_square_p(size_t n, int *elem)
{
    double sum = 0;
    while (n--) {
        sum += (*elem)*(*elem);
        elem++;
    }

    return sum;
}

static double
simd_sum_square_b(size_t n, int *elem)
{
    double sum = 0;
    while (n--) {
        sum += (*elem)*(*elem);
        elem++;
    }

    return sum;
}

static double
__data_norm(const __st_data *data, const size_t incx)
{
    switch (data->dtype) {
        case st_double:
            return cblas_dnrm2(data->size, data->head, 1);

        case st_int:
            return sqrt(simd_sum_square_i(data->size, data->head));

        case st_pixel:
            return sqrt(simd_sum_square_p(data->size, data->head));

        case st_bool:
            return sqrt(simd_sum_square_b(data->size, data->head));

        default:
            __st_raise_dtype_error();
    }
}

double
st_vec_norm(st_vector *vec)
{
    return __data_norm(vec->data, 1);
}


/* =================================================================================================
 * pair function
 */

/* for each element, rst = a * b */
static void
simd_mul_d(size_t n, double *dst, double *a, double *b)
{
    while (n--) {
        *dst++ = (*a++) * (*b++);
    }    
}

static void
simd_mul_i(size_t n, int *dst, int *a, int *b)
{
    while (n--) {
        *dst++ = (*a++) * (*b++);
    }
}

static void
simd_mul_p(size_t n, unsigned char *dst, unsigned char *a, unsigned char *b)
{
    while (n--) {
        *dst++ = (*a++) * (*b++);
    }
}

static void
simd_mul_b(size_t n, bool *dst, bool *a, bool *b)
{
    while (n--) {
        *dst++ = (*a++) && (*b++);
    }
}

static void
__data_mul(const __st_data *dst, const __st_data *a, const __st_data *b)
{
    st_check_data_dtype(dst, a->dtype);
    st_check_data_dtype(dst, b->dtype);
    st_check_data_size(dst, a->size);
    st_check_data_size(dst, b->size);

    switch (dst->dtype) {
        case st_double:
            simd_mul_d(dst->size, dst->head, a->head, b->head);
            return;

        case st_int:
            simd_mul_i(dst->size, dst->head, a->head, b->head);
            return;

        case st_pixel:
            simd_mul_p(dst->size, dst->head, a->head, b->head);
            return;

        case st_bool:
            simd_mul_b(dst->size, dst->head, a->head, b->head);
            return;

        default:
            __st_raise_dtype_error();
    }
}

st_vector *
st_vec_mul(st_vector *a, st_vector *b)
{
    size_t len = st_check_vec_len(a, b->len);
    __st_dtype dtype = st_check_vec_dtype(a, b->dtype);
    st_vector *dst = __st_new_vector(dtype, len);

    __data_mul(dst->data, a->data, b->data);
    return dst;
}

st_matrix *
st_mat_mul(st_matrix *a, st_matrix *b)
{
    size_t nrow = st_check_mat_nrow(a, b->nrow);
    size_t ncol = st_check_mat_ncol(a, b->ncol);
    __st_dtype dtype = st_check_mat_dtype(a, b->dtype);
    st_matrix *dst = __st_new_matrix(dtype, nrow, ncol);

    __data_mul(dst->data, a->data, b->data);
    return dst;
}

/* =================================================================================================
 * vectorized simd function add
 */

static void
__simd_add_d(size_t n, double *dst, double *a, double *b)
{
    cblas_dcopy(n, a, 1, dst, 1);
    cblas_daxpy(n, 1, b, 1, dst, 1);
}

static void
__simd_add_i(size_t n, int *dst, int *a, int *b)
{
    __m128i *pa = (__m128i *) a;
    __m128i *pb = (__m128i *) b;
    __m128i *pd = (__m128i *) dst;

    /* 4 * (4*8) = 128 */
    while (n >= 4) {

        __m128i __a = _mm_loadu_si128(pa++);
        __m128i __b = _mm_loadu_si128(pb++);
        __b = _mm_add_epi8(__a, __b);
        _mm_storeu_si128(pd++, __b);

        n -= 4;
    }

    a   = (int *)pa;
    b   = (int *)pb;
    dst = (int *)pd;

    while (n--)
        *dst++ = (*a++) + (*b++);
}

static void
__simd_add_p(size_t n, unsigned char *dst, unsigned char *a, unsigned char *b)
{
    __m128i *pa = (__m128i *) a;
    __m128i *pb = (__m128i *) b;
    __m128i *pd = (__m128i *) dst;

    /* 16 * (1*8) = 128 */
    while (n >= 16) {

        __m128i __a = _mm_loadu_si128(pa++);
        __m128i __b = _mm_loadu_si128(pb++);
        __b = _mm_add_epi8(__a, __b);
        _mm_storeu_si128(pd++, __b);

        n -= 16;
    }

    a   = (unsigned char *)pa;
    b   = (unsigned char *)pb;
    dst = (unsigned char *)pd;

    while (n--)
        *dst++ = (*a++) + (*b++);
}

static void
__simd_add_b(size_t n, bool *dst, bool *a, bool *b)
{
    __m128i *pa = (__m128i *) a;
    __m128i *pb = (__m128i *) b;
    __m128i *pd = (__m128i *) dst;

    /* 16 * (1*8) = 128 */
    while (n >= 16) {

        __m128i __a = _mm_loadu_si128(pa++);
        __m128i __b = _mm_loadu_si128(pb++);
        __b = _mm_or_si128(__a, __b);
        _mm_storeu_si128(pd++, __b);

        n -= 16;
    }

    a   = (bool *)pa;
    b   = (bool *)pb;
    dst = (bool *)pd;

    while (n--)
        *dst++ = (*a++) || (*b++);
}

static void
__data_add(const __st_data *dst, const __st_data *a, const __st_data *b)
{
    st_check_data_dtype(dst, a->dtype);
    st_check_data_dtype(dst, b->dtype);
    st_check_data_size(dst, a->size);
    st_check_data_size(dst, b->size);

    switch (dst->dtype) {
        case st_double:
            __simd_add_d(dst->size, dst->head, a->head, b->head);
            return;

        case st_int:
            __simd_add_i(dst->size, dst->head, a->head, b->head);
            return;

        case st_pixel:
            __simd_add_p(dst->size, dst->head, a->head, b->head);
            return;

        case st_bool:
            __simd_add_b(dst->size, dst->head, a->head, b->head);
            return;

        default:
            __st_raise_dtype_error();
    }
}

st_vector *
st_vec_add(st_vector *a, st_vector *b)
{
    size_t len = st_check_vec_len(a, b->len);
    __st_dtype dtype = st_check_vec_dtype(a, b->dtype);
    st_vector *dst = __st_new_vector(dtype, len);

    __data_add(dst->data, a->data, b->data);
    return dst;
}

st_matrix *
st_mat_add(st_matrix *a, st_matrix *b)
{
    size_t nrow = st_check_mat_nrow(a, b->nrow);
    size_t ncol = st_check_mat_ncol(a, b->ncol);
    __st_dtype dtype = st_check_mat_dtype(a, b->dtype);
    st_matrix *dst = __st_new_matrix(dtype, nrow, ncol);

    __data_add(dst->data, a->data, b->data);
    return dst;
}

/* =================================================================================================
 * call pair function
 */

// double
// st_vec_pair(st_vector *vl, st_vector *vr, fp_pair fp, void *argv[])
// {
//     __st_dtype dtype = st_check_vec_dtype(vl, vr->dtype);

//     size_t i;
//     void *e1, *e2;
//     for __st_iter_vector2(i, e1, e2, vl, vr)
//             fp(e1, e2, dtype, argv);
// }
