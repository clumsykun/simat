#include <math.h>
#include <immintrin.h>
#include "st_elemental.h"
#include "cblas.h"

/* =================================================================================================
 * call elemental function
 */

// /* call elemental function of st_d64 */
// static void
// __call_elem_d64(size_t len, st_elemental *elemental, st_d64 *head, void *argv[])
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
// __call_elem_i32(size_t len, st_elemental *elemental, st_i32 *head, void *argv[])
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
// __call_elem_u8(size_t len, st_elemental *elemental, st_u8 *head, void *argv[])
// {
//     fp_elem_p fp = elemental->p;

//     if (fp == NULL)
//         return;

//     while (len--) {
//         fp(head++, argv);
//     }
// }

// /* call elemental function of st_bool */
// static void
// __call_elem_bool(size_t len, st_elemental *elemental, st_bool *head, void *argv[])
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
//         case st_dtype_d64:
//             __call_elem_d64(data->size, elemental, data->head, argv);
//             break;

//         case st_dtype_i32:
//             __call_elem_i32(data->size, elemental, data->head, argv);
//             break;

//         case st_dtype_u8:
//             __call_elem_u8(data->size, elemental, data->head, argv);
//             break;

//         case st_dtype_bool:
//             __call_elem_bool(data->size, elemental, data->head, argv);
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
__abs_d64(size_t n, st_d64 *elem)
{
    while (n--)
        *elem++ = st_abs(*elem);
}

static void
__abs_i32(size_t n, st_i32 *elem)
{
    while (n--)
        *elem++ = st_abs(*elem);
}

static void
__data_abs(const __st_data *data)
{
    switch (data->dtype) {
        case st_dtype_d64:
            __abs_d64(data->size, data->head);
            return;

        case st_dtype_i32:
            __abs_i32(data->size, data->head);
            return;

        case st_dtype_u8:
            return;

        case st_dtype_bool:
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

static st_d64
simd_min_i32(size_t n, st_i32 *elem, const size_t incx)
{
    st_d64 min = *elem;
    while (n--) {
        min = (*elem < min ? *elem : min);
        elem++;
    }
    return min;
}

static st_d64
simd_min_u8(size_t n, st_u8 *elem, const size_t incx)
{
    st_d64 min = *elem;
    while (n--) {
        min = (*elem < min ? *elem : min);
        min = __st_trim_pixel(min);
        elem++;
    }
    return min;
}

static st_d64
simd_min_bool(size_t n, st_bool *elem, const size_t incx)
{
    st_d64 min = *elem;
    while (n--)
        min = (*elem) && min;

    return min;
}

static st_d64
__data_min(const __st_data *data, const size_t incx)
{
    switch (data->dtype) {
        case st_dtype_d64:
            return __st_data_access(
                data,
                cblas_idmin(data->size, data->head, incx));

        case st_dtype_i32:
            return simd_min_i32(data->size, data->head, incx);

        case st_dtype_u8:
            return simd_min_u8(data->size, data->head, incx);

        case st_dtype_bool:
            return simd_min_bool(data->size, data->head, incx);

        default:
            __st_raise_dtype_error();
    }
}

st_d64
st_vec_min(st_vector *vec)
{
    return __data_min(vec->data, 1);
}

st_d64
st_mat_min(st_matrix *mat)
{
    return __data_min(mat->data, 1);
}

/** ================================================================================================
 * vectorized `max` function
 * need SIMD!
 */

static st_d64
simd_max_i32(size_t n, st_i32 *elem, const size_t incx)
{
    st_d64 max = *elem;
    while (n--) {
        max = (*elem > max ? *elem : max);
        elem++;
    }
    return max;
}

static st_d64
simd_max_u8(size_t n, st_u8 *elem, const size_t incx)
{
    st_d64 max = *elem;
    while (n--) {
        max = (*elem > max ? *elem : max);
        max = __st_trim_pixel(max);
        elem++;
    }
    return max;
}

static st_d64
simd_max_bool(size_t n, st_bool *elem, const size_t incx)
{
    st_d64 max = *elem;
    while (n--)
        max = (*elem) || max;

    return max;
}

static st_d64
__data_max(const __st_data *data, const size_t incx)
{
    switch (data->dtype) {
        case st_dtype_d64:
            return __st_data_access(
                data,
                cblas_idmax(data->size, data->head, incx));

        case st_dtype_i32:
            return simd_max_i32(data->size, data->head, incx);

        case st_dtype_u8:
            return simd_max_u8(data->size, data->head, incx);

        case st_dtype_bool:
            return simd_max_bool(data->size, data->head, incx);

        default:
            __st_raise_dtype_error();
    }
}

st_d64
st_vec_max(st_vector *vec)
{
    return __data_max(vec->data, 1);
}

st_d64
st_mat_max(st_matrix *mat)
{
    return __data_max(mat->data, 1);
}

/** ================================================================================================
 * vectorized `sum` function
 * need SIMD!
 */

static st_d64
simd_sum_i32(size_t n, st_i32 *elem, const size_t incx)
{
    st_d64 sum = 0;
    while (n--)
        sum += *elem++;

    return sum;
}

static st_d64
simd_sum_u8(size_t n, st_u8 *elem, const size_t incx)
{
    st_d64 sum = 0;
    while (n--)
        sum += *elem++;

    return sum;
}

static st_d64
simd_sum_bool(size_t n, st_bool *elem, const size_t incx)
{
    st_d64 sum = 0;
    while (n--)
        sum += *elem++;

    return sum;
}

static st_d64
__data_sum(const __st_data *data, const size_t incx)
{
    switch (data->dtype) {
        case st_dtype_d64:
            return cblas_dsum(data->size, data->head, incx);

        case st_dtype_i32:
            return simd_sum_i32(data->size, data->head, incx);

        case st_dtype_u8:
            return simd_sum_u8(data->size, data->head, incx);

        case st_dtype_bool:
            return simd_sum_bool(data->size, data->head, incx);

        default:
            __st_raise_dtype_error();
    }
}

st_d64
st_vec_sum(st_vector *vec)
{
    return __data_sum(vec->data, 1);
}

st_d64
st_mat_sum(st_matrix *mat)
{
    return __data_sum(mat->data, 1);
}

/** ================================================================================================
 * vectorized `square_sum` function
 * need SIMD!
 */

static st_d64
simd_sum_square_i32(size_t n, st_i32 *elem)
{
    st_d64 sum = 0;
    while (n--) {
        sum += (*elem)*(*elem);
        elem++;
    }

    return sum;
}

static st_d64
simd_sum_square_u8(size_t n, st_i32 *elem)
{
    st_d64 sum = 0;
    while (n--) {
        sum += (*elem)*(*elem);
        elem++;
    }

    return sum;
}

static st_d64
simd_sum_square_bool(size_t n, st_i32 *elem)
{
    st_d64 sum = 0;
    while (n--) {
        sum += (*elem)*(*elem);
        elem++;
    }

    return sum;
}

static st_d64
__data_norm(const __st_data *data, const size_t incx)
{
    switch (data->dtype) {
        case st_dtype_d64:
            return cblas_dnrm2(data->size, data->head, 1);

        case st_dtype_i32:
            return sqrt(simd_sum_square_i32(data->size, data->head));

        case st_dtype_u8:
            return sqrt(simd_sum_square_u8(data->size, data->head));

        case st_dtype_bool:
            return sqrt(simd_sum_square_bool(data->size, data->head));

        default:
            __st_raise_dtype_error();
    }
}

st_d64
st_vec_norm(st_vector *vec)
{
    return __data_norm(vec->data, 1);
}


/* =================================================================================================
 * pair function
 */

/* for each element, rst = a * b */
static void
simd_mul_d64(size_t n, st_d64 *dst, st_d64 *a, st_d64 *b)
{
    __m128d *pa = (__m128d *) a;
    __m128d *pb = (__m128d *) b;
    __m128d *pd = (__m128d *) dst;

    /* 2 * (8*8) = 128 */
    while (n >= 2) {

        __m128d __a = _mm_loadu_pd((st_d64 *)pa++);
        __m128d __b = _mm_loadu_pd((st_d64 *)pb++);
        __b = _mm_mul_pd(__a, __b);
        _mm_storeu_pd((st_d64 *)pd++, __b);

        n -= 2;
    }

    a   = (st_d64 *)pa;
    b   = (st_d64 *)pb;
    dst = (st_d64 *)pd;

    while (n--)
        *dst++ = (*a++) * (*b++);
}

static void
simd_mul_i32(size_t n, st_i32 *dst, st_i32 *a, st_i32 *b)
{
    __m128i *pa = (__m128i *) a;
    __m128i *pb = (__m128i *) b;
    __m128i *pd = (__m128i *) dst;

    /* 4 * (4*8) = 128 */
    while (n >= 4) {

        __m128i __a = _mm_loadu_si128(pa++);
        __m128i __b = _mm_loadu_si128(pb++);
        __m128i __even = _mm_mul_epu32(__a, __b);
        __m128i __odd = _mm_mul_epu32(_mm_srli_epi64(__a, 32), _mm_srli_epi64(__b, 32));
        __m128i __low = _mm_unpacklo_epi32(__even, __odd);
        __m128i __high = _mm_unpackhi_epi32(__even, __odd);
        __m128i __dst = _mm_unpacklo_epi64(__low, __high);

        _mm_storeu_si128(pd++, __dst);
        n -= 4;
    }

    a   = (st_i32 *)pa;
    b   = (st_i32 *)pb;
    dst = (st_i32 *)pd;

    while (n--)
        *dst++ = (*a++) * (*b++);
}

static void
simd_mul_u8(size_t n, st_u8 *dst, st_u8 *a, st_u8 *b)
{
    __m128i *pa = (__m128i *) a;
    __m128i *pb = (__m128i *) b;
    __m128i *pd = (__m128i *) dst;

    /* 16 * (1*8) = 128 */
    while (n >= 16) {

        __m128i __a = _mm_loadu_si128(pa++);
        __m128i __b = _mm_loadu_si128(pb++);

        const __m128i mask = _mm_set1_epi32(0xFF00FF00);
        __m128i __even = _mm_mullo_epi16(__a, __b);
        __m128i __odd = _mm_mullo_epi16(_mm_srai_epi16(__a, 8), _mm_srai_epi16(__b, 8));
        __odd = _mm_slli_epi16(__odd, 8);
        __m128i __dst = _mm_xor_si128(__even, _mm_and_si128(_mm_xor_si128(__even, __odd), mask));
        _mm_storeu_si128(pd++, __dst);
        n -= 16;
    }

    a   = (st_u8 *)pa;
    b   = (st_u8 *)pb;
    dst = (st_u8 *)pd;

    while (n--)
        *dst++ = (*a++) * (*b++);
}

static void
simd_mul_bool(size_t n, st_bool *dst, st_bool *a, st_bool *b)
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
        case st_dtype_d64:
            simd_mul_d64(dst->size, dst->head, a->head, b->head);
            return;

        case st_dtype_i32:
            simd_mul_i32(dst->size, dst->head, a->head, b->head);
            return;

        case st_dtype_u8:
            simd_mul_u8(dst->size, dst->head, a->head, b->head);
            return;

        case st_dtype_bool:
            simd_mul_bool(dst->size, dst->head, a->head, b->head);
            return;

        default:
            __st_raise_dtype_error();
    }
}

st_vector *
st_vec_mul(st_vector *a, st_vector *b)
{
    size_t len = st_check_vec_len(a, b->len);
    st_dtype dtype = st_check_vec_dtype(a, b->dtype);
    st_vector *dst = __st_new_vector(dtype, len);

    __data_mul(dst->data, a->data, b->data);
    return dst;
}

st_matrix *
st_mat_mul(st_matrix *a, st_matrix *b)
{
    size_t nrow = st_check_mat_nrow(a, b->nrow);
    size_t ncol = st_check_mat_ncol(a, b->ncol);
    st_dtype dtype = st_check_mat_dtype(a, b->dtype);
    st_matrix *dst = __st_new_matrix(dtype, nrow, ncol);

    __data_mul(dst->data, a->data, b->data);
    return dst;
}

/* =================================================================================================
 * vectorized simd function add
 */

static void
__simd_add_d64(size_t n, st_d64 *dst, st_d64 *a, st_d64 *b)
{
    cblas_dcopy(n, a, 1, dst, 1);
    cblas_daxpy(n, 1, b, 1, dst, 1);
}

static void
__simd_add_i32(size_t n, st_i32 *dst, st_i32 *a, st_i32 *b)
{
    __m128i *pa = (__m128i *) a;
    __m128i *pb = (__m128i *) b;
    __m128i *pd = (__m128i *) dst;

    /* 4 * (4*8) = 128 */
    while (n >= 4) {

        __m128i __a = _mm_loadu_si128(pa++);
        __m128i __b = _mm_loadu_si128(pb++);
        __b = _mm_add_epi32(__a, __b);
        _mm_storeu_si128(pd++, __b);

        n -= 4;
    }

    a   = (st_i32 *)pa;
    b   = (st_i32 *)pb;
    dst = (st_i32 *)pd;

    while (n--)
        *dst++ = (*a++) + (*b++);
}

static void
__simd_add_u8(size_t n, st_u8 *dst, st_u8 *a, st_u8 *b)
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

    a   = (st_u8 *)pa;
    b   = (st_u8 *)pb;
    dst = (st_u8 *)pd;

    while (n--)
        *dst++ = (*a++) + (*b++);
}

static void
__simd_add_bool(size_t n, st_bool *dst, st_bool *a, st_bool *b)
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

    a   = (st_bool *)pa;
    b   = (st_bool *)pb;
    dst = (st_bool *)pd;

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
        case st_dtype_d64:
            __simd_add_d64(dst->size, dst->head, a->head, b->head);
            return;

        case st_dtype_i32:
            __simd_add_i32(dst->size, dst->head, a->head, b->head);
            return;

        case st_dtype_u8:
            __simd_add_u8(dst->size, dst->head, a->head, b->head);
            return;

        case st_dtype_bool:
            __simd_add_bool(dst->size, dst->head, a->head, b->head);
            return;

        default:
            __st_raise_dtype_error();
    }
}

st_vector *
st_vec_add(st_vector *a, st_vector *b)
{
    size_t len = st_check_vec_len(a, b->len);
    st_dtype dtype = st_check_vec_dtype(a, b->dtype);
    st_vector *dst = __st_new_vector(dtype, len);

    __data_add(dst->data, a->data, b->data);
    return dst;
}

st_matrix *
st_mat_add(st_matrix *a, st_matrix *b)
{
    size_t nrow = st_check_mat_nrow(a, b->nrow);
    size_t ncol = st_check_mat_ncol(a, b->ncol);
    st_dtype dtype = st_check_mat_dtype(a, b->dtype);
    st_matrix *dst = __st_new_matrix(dtype, nrow, ncol);

    __data_add(dst->data, a->data, b->data);
    return dst;
}

/* =================================================================================================
 * call pair function
 */

// st_d64
// st_vec_pair(st_vector *vl, st_vector *vr, fp_pair fp, void *argv[])
// {
//     st_dtype dtype = st_check_vec_dtype(vl, vr->dtype);

//     size_t i;
//     void *e1, *e2;
//     for __st_iter_vector2(i, e1, e2, vl, vr)
//             fp(e1, e2, dtype, argv);
// }
