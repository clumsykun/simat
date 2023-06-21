#include <math.h>
#include <immintrin.h>
#include "st_c_elemental.h"
#include "st_a_blas.h"
#include "st_a_simd.h"

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
 *  Compute absolute value.
 */

static void
__abs_d64(size_t n, st_d64 *elem)
{
    size_t psize     = __st_m_psize_d64;
    size_t packs     = n / psize;
    size_t remainder = n % psize;

    __st_md *pe = (__st_md *) elem;

    while (packs--) {

        __st_md pk_e = __st_load_d64(pe);
        pk_e = __st_m_and_d(
            pk_e,
            __st_m_cast_i2d(__st_m_setall_i64(0x7fffffffffffffffLL))
        );
        __st_store_d64(pe++, pk_e);
    }

    elem = (st_d64 *)pe;

    while (remainder--)
        *elem++ = fabs(*elem);
}

static void
__abs_i32(size_t n, st_i32 *elem)
{
    size_t psize     = __st_m_psize_d64;
    size_t packs     = n / psize;
    size_t remainder = n % psize;

    __st_mi *pe = (__st_mi *) elem;

    while (packs--) {

        __st_mi pk_e = __st_load_i(pe);
        pk_e = __st_m_abs_i32(pk_e);
        __st_store_i(pe++, pk_e);
    }

    elem = (st_i32 *)pe;

    while (remainder--)
        *elem++ = abs(*elem);
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
 *  Compute min/max value.
 */

static st_d64
__min_d64(size_t n, st_d64 *head)
{
    size_t psize     = __st_m_psize_d64;
    size_t packs     = n / psize;
    size_t remainder = n % psize;

    st_d64 value;
    st_d64 min     = *head;
    __st_md pk_min = __st_load_d64(head);
    __st_md *pe    = (__st_md *) head;

    while (packs--)
        pk_min = __st_m_min_d64(__st_load_d64(pe++), pk_min);

    if (n > remainder)
        for (size_t i = 0; i < psize; i++)
            min = (min < pk_min[i] ? min : pk_min[i]);

    head = (st_d64 *)pe;

    while (remainder--) {
        value = *head++;
        min = (min < value ? min : value);
    }
    return min;
}

static st_i32
__min_i32(size_t n, st_i32 *head)
{
    size_t psize     = __st_m_psize_i32;
    size_t packs     = n / psize;
    size_t remainder = n % psize;

    st_i32 value;
    st_i32 arr_min[psize];
    st_i32 min = *head;
    __st_mi pk_e;
    __st_mi pk_min = __st_load_i(head);
    __st_mi *pe = (__st_mi *)head;

    while (packs--) {

        pk_e = __st_load_i(pe++);
        pk_min = __st_m_min_i32(pk_e, pk_min);
    }

    if (n > remainder) {

        __st_store_i(arr_min, pk_min);

        for (size_t i = 0; i < psize; i++)
            min = (min < arr_min[i] ? min : arr_min[i]);
    }

    head = (st_i32 *)pe;

    while (remainder--) {
        value = *head++;
        min = (min < value ? min : value);
    }
    return min;
}

static st_u8
__min_u8_bool(size_t n, st_u8 *head)
{
    size_t psize     = __st_m_psize_u8;
    size_t packs     = n / psize;
    size_t remainder = n % psize;

    st_u8 value;
    st_u8 arr_min[psize];
    st_u8 min = *head;
    __st_mi pk_e;
    __st_mi pk_min = __st_load_i(head);
    __st_mi *pe = (__st_mi *)head;

    while (packs--) {

        pk_e = __st_load_i(pe++);
        pk_min = __st_m_min_u8(pk_e, pk_min);
    }

    if (n > remainder) {

        __st_store_i(arr_min, pk_min);

        for (size_t i = 0; i < psize; i++)
            min = (min < arr_min[i] ? min : arr_min[i]);
    }

    head = (st_u8 *)pe;

    while (remainder--) {
        value = *head++;
        min = (min < value ? min : value);
    }
    return min;
}

static st_decimal
__data_min(const __st_data *data)
{
    size_t n = data->size;
    void *head = data->head;

    switch (data->dtype) {
        case st_dtype_d64:
            return (st_decimal)__min_d64(n, head);

        case st_dtype_i32:
            return (st_decimal)__min_i32(n, head);

        case st_dtype_u8:
            return (st_decimal)__min_u8_bool(n, head);

        case st_dtype_bool:
            return (st_decimal)__min_u8_bool(n, head);

        default:
            __st_raise_dtype_error();
    }
}

inline st_decimal
st_vec_min(st_vector *vec)
{
    return __data_min(vec->data);
}

inline st_decimal
st_mat_min(st_matrix *mat)
{
    return __data_min(mat->data);
}

static st_d64
__max_d64(size_t n, st_d64 *head)
{
    size_t psize     = __st_m_psize_d64;
    size_t packs     = n / psize;
    size_t remainder = n % psize;

    st_d64 value;
    st_d64 max     = *head;
    __st_md pk_max = __st_load_d64(head);
    __st_md *pe    = (__st_md *) head;

    while (packs--)
        pk_max = __st_m_max_d64(__st_load_d64(pe++), pk_max);

    if (n > remainder)
        for (size_t i = 0; i < psize; i++)
            max = (max > pk_max[i] ? max : pk_max[i]);

    head = (st_d64 *)pe;

    while (remainder--) {
        value = *head++;
        max = (max > value ? max : value);
    }
    return max;
}

static st_i32
__max_i32(size_t n, st_i32 *head)
{
    size_t psize     = __st_m_psize_i32;
    size_t packs     = n / psize;
    size_t remainder = n % psize;

    st_i32 value;
    st_i32 arr_max[psize];
    st_i32 max = *head;
    __st_mi pk_e;
    __st_mi pk_max = __st_load_i(head);
    __st_mi *pe = (__st_mi *)head;

    while (packs--) {

        pk_e = __st_load_i(pe++);
        pk_max = __st_m_max_i32(pk_e, pk_max);
    }

    if (n > remainder) {

        __st_store_i(arr_max, pk_max);

        for (size_t i = 0; i < psize; i++)
            max = (max > arr_max[i] ? max : arr_max[i]);
    }

    head = (st_i32 *)pe;

    while (remainder--) {
        value = *head++;
        max = (max > value ? max : value);
    }
    return max;
}

static st_u8
__max_u8_bool(size_t n, st_u8 *head)
{
    size_t psize     = __st_m_psize_u8;
    size_t packs     = n / psize;
    size_t remainder = n % psize;

    st_u8 value;
    st_u8 arr_max[psize];
    st_u8 max = *head;
    __st_mi pk_e;
    __st_mi pk_max = __st_load_i(head);
    __st_mi *pe = (__st_mi *)head;

    while (packs--) {

        pk_e = __st_load_i(pe++);
        pk_max = __st_m_max_u8(pk_e, pk_max);
    }

    if (n > remainder) {

        __st_store_i(arr_max, pk_max);

        for (size_t i = 0; i < psize; i++)
            max = (max > arr_max[i] ? max : arr_max[i]);
    }

    head = (st_u8 *)pe;

    while (remainder--) {
        value = *head++;
        max = (max > value ? max : value);
    }
    return max;
}

static st_decimal
__data_max(const __st_data *data)
{
    size_t n = data->size;
    void *head = data->head;

    switch (data->dtype) {
        case st_dtype_d64:
            return (st_decimal)__max_d64(n, head);

        case st_dtype_i32:
            return (st_decimal)__max_i32(n, head);

        case st_dtype_u8:
            return (st_decimal)__max_u8_bool(n, head);

        case st_dtype_bool:
            return (st_decimal)__max_u8_bool(n, head);

        default:
            __st_raise_dtype_error();
    }
}

inline st_decimal
st_vec_max(st_vector *vec)
{
    return __data_max(vec->data);
}

inline st_decimal
st_mat_max(st_matrix *mat)
{
    return __data_max(mat->data);
}

/** ================================================================================================
 *  Compute sum value.
 */

static st_decimal
__sum_d64(size_t n, st_d64 *head)
{
    size_t psize     = __st_m_psize_d64;
    size_t packs     = n / psize;
    size_t remainder = n % psize;

    st_d64 arr_sum[psize];
    st_d64 sum     = 0;
    __st_md pk_sum = __st_m_zero_d();
    __st_md *p     = (__st_md *) head;

    while (packs--)
        pk_sum = __st_m_add_d64(__st_load_d64(p++), pk_sum);

    __st_store_d64(arr_sum, pk_sum);

    if (n > remainder)
        for (size_t i = 0; i < psize; i++)
            sum += arr_sum[i];

    head = (st_d64 *)p;

    while (remainder--)
        sum += *head++;

    return sum;
}

static st_i32
__sum_i32(size_t n, st_i32 *head)
{
    size_t psize     = __st_m_psize_i32;
    size_t packs     = n / psize;
    size_t remainder = n % psize;

    st_i32 arr_sum[psize];
    st_i32 sum     = 0;
    __st_mi pk_sum = __st_m_zero_i();
    __st_mi *p     = (__st_mi *) head;

    while (packs--)
        pk_sum = __st_m_add_i32(__st_load_i(p++), pk_sum);

    __st_store_i(arr_sum, pk_sum);

    if (n > remainder)
        for (size_t i = 0; i < psize; i++)
            sum += pk_sum[i];

    head = (st_i32 *)p;

    while (remainder--)
        sum += *head++;

    return sum;
}

static st_i64
__sum_u8_bool(size_t n, st_u8 *head)
{
    size_t psize     = __st_m_psize_u8;
    size_t packs     = n / psize;
    size_t remainder = n % psize;

    st_i64 arr_sum[__st_m_psize_i64];
    st_i64 sum = 0;
    __st_mi pk_sum = __st_m_zero_i();
    __st_mi zero   = __st_m_zero_i();
    __st_mi *p     = (__st_mi *) head;
    __st_mi pk_sad;

    while (packs--) {
        pk_sad = __st_m_sad_u8(__st_load_i(p++), zero);
        pk_sum = __st_m_add_i64(pk_sad, pk_sum);
    }

    __st_store_i(arr_sum, pk_sum);

    if (n > remainder)
        for (size_t i = 0; i < __st_m_psize_i64; i++)
            sum += pk_sum[i];

    head = (st_u8 *)p;

    while (remainder--)
        sum += *head++;

    return sum;
}

static st_decimal
__data_sum(const __st_data *data, const size_t incx)
{
    size_t n = data->size;
    void *head = data->head;

    switch (data->dtype) {
        case st_dtype_d64:
            return (st_decimal)__sum_d64(n, head);

        case st_dtype_i32:
            return (st_decimal)__sum_i32(n, head);

        case st_dtype_u8:
            return (st_decimal)__sum_u8_bool(n, head);

        case st_dtype_bool:
            return (st_decimal)__sum_u8_bool(n, head);

        default:
            __st_raise_dtype_error();
    }
}

st_decimal
st_vec_sum(st_vector *vec)
{
    return __data_sum(vec->data, 1);
}

st_decimal
st_mat_sum(st_matrix *mat)
{
    return __data_sum(mat->data, 1);
}

/** ================================================================================================
 *  Compute sum of square.
 */

static st_d64
__sum_square_d64(size_t n, st_d64 *head)
{
    size_t psize     = __st_m_psize_d64;
    size_t packs     = n / psize;
    size_t remainder = n % psize;

    st_d64 elem, arr_sum[psize];
    st_d64 sum     = 0;
    __st_md pk_elem;
    __st_md pk_sum = __st_m_zero_d();
    __st_md *p     = (__st_md *)head;

    while (packs--) {
        pk_elem = __st_load_d64(p++);
        pk_elem = __st_m_mul_d64(pk_elem, pk_elem);
        pk_sum = __st_m_add_d64(pk_elem, pk_sum);
    }

    if (n > remainder) {
        __st_store_d64(arr_sum, pk_sum);

        for (size_t i = 0; i < psize; i++)
            sum += arr_sum[i];
    }

    head = (st_d64 *)p;

    while (remainder--) {
        elem = *head++;
        sum += elem*elem;
    }

    return sum;
}

static st_i32
__sum_square_i32(size_t n, st_i32 *head)
{
    size_t psize     = __st_m_psize_i32;
    size_t packs     = n / psize;
    size_t remainder = n % psize;

    st_i32 elem, arr_sum[psize];
    st_i32 sum     = 0;
    __st_mi pk_elem;
    __st_mi pk_sum = __st_m_zero_i();
    __st_mi *p     = (__st_mi *) head;

    while (packs--) {
        pk_elem = __st_load_i(p++);
        pk_elem = __st_m_mul_i32(pk_elem, pk_elem);
        pk_sum  = __st_m_add_i32(pk_elem, pk_sum);
    }

    if (n > remainder) {
        __st_store_i(arr_sum, pk_sum);

        for (size_t i = 0; i < psize; i++)
            sum += pk_sum[i];
    }

    head = (st_i32 *)p;

    while (remainder--) {
        elem = *head++;
        sum += elem * elem;
    }

    return sum;
}

static st_i32
__sum_square_u8_bool(size_t n, st_i32 *head)
{
    size_t psize     = __st_m_psize_u8;
    size_t packs     = n / psize;
    size_t remainder = n % psize;

    st_i32 value, arr_sum[__st_m_psize_i32];
    st_i32 sum = 0;
    __st_mi pk_sum = __st_m_zero_i();
    __st_mi zero   = __st_m_zero_i();
    __st_mi *p     = (__st_mi *) head;
    __st_mi pk_sad;

    while (packs--) {
        pk_sad = __st_m_sad_u8(__st_load_i(p++), zero);
        pk_sad = __st_m_mul_i32(pk_sad, pk_sad);
        pk_sum = __st_m_add_i32(pk_sad, pk_sum);
    }

    __st_store_i(arr_sum, pk_sum);

    if (n > remainder)
        for (size_t i = 0; i < __st_m_psize_i64; i++)
            sum += pk_sum[i];

    head = (st_u8 *)p;

    while (remainder--) {
        value = *head++;
        sum += value * value;
    }

    return sum;
}

static st_decimal
__data_norm(const __st_data *data)
{
    size_t n = data->size;
    void *head = data->head;

    switch (data->dtype) {
        case st_dtype_d64:
            return sqrt((st_decimal)__sum_square_d64(n, head));

        case st_dtype_i32:
            return sqrt((st_decimal)__sum_square_i32(n, head));

        case st_dtype_u8:
            return sqrt((st_decimal)__sum_square_u8_bool(n, head));

        case st_dtype_bool:
            return sqrt((st_decimal)__sum_square_u8_bool(n, head));

        default:
            __st_raise_dtype_error();
    }
}

st_decimal
st_vec_norm(st_vector *vec)
{
    return __data_norm(vec->data);
}

st_decimal
st_mat_norm(st_matrix *mat)
{
    return __data_norm(mat->data);
}

/* =================================================================================================
 * pair function
 */

/* for each element, rst = a * b */
static void
simd_mul_d64(size_t n, st_d64 *dst, st_d64 *a, st_d64 *b)
{
    size_t psize     = __st_m_psize_d64;
    size_t packs   = n / psize;
    size_t remainder = n % psize;

    __st_md *pa = (__st_md *) a;
    __st_md *pb = (__st_md *) b;
    __st_md *pd = (__st_md *) dst;

    /* 2 * (8*8) = 128 */
    while (packs--) {

        __st_md __a = __st_load_d64((st_d64 *)pa++);
        __st_md __b = __st_load_d64((st_d64 *)pb++);
        __b = __st_m_mul_d64(__a, __b);
        __st_store_d64((st_d64 *)pd++, __b);
    }

    a   = (st_d64 *)pa;
    b   = (st_d64 *)pb;
    dst = (st_d64 *)pd;

    while (remainder--)
        *dst++ = (*a++) * (*b++);
}

static void
simd_mul_i32(size_t n, st_i32 *dst, st_i32 *a, st_i32 *b)
{
    size_t psize     = __st_m_psize_i32;
    size_t packs   = n / psize;
    size_t remainder = n % psize;

    __st_mi *pa = (__st_mi *) a;
    __st_mi *pb = (__st_mi *) b;
    __st_mi *pd = (__st_mi *) dst;

    while (packs--) {

        __st_mi pk_a = __st_load_i(pa++);
        __st_mi pk_b = __st_load_i(pb++);
        __st_mi pk_r = __st_m_mul_i32(pk_a, pk_b);
        __st_store_i(pd++, pk_r);
    }

    a   = (st_i32 *)pa;
    b   = (st_i32 *)pb;
    dst = (st_i32 *)pd;

    while (remainder--)
        *dst++ = (*a++) * (*b++);
}

static void
simd_mul_u8(size_t n, st_u8 *dst, st_u8 *a, st_u8 *b)
{
    size_t psize     = __st_m_psize_u8;
    size_t packs   = n / psize;
    size_t remainder = n % psize;

    __st_mi *pa = (__st_mi *) a;
    __st_mi *pb = (__st_mi *) b;
    __st_mi *pd = (__st_mi *) dst;

    /* 16 * (1*8) = 128 */

    /**
     * Code of -16711936:       10000000111111110000000100000000
     * Inverse of -16711936:    11111111000000001111111011111111
     * Complement of -16711936: 11111111000000001111111100000000
     * Code of0xFF00FF00:       11111111000000001111111100000000
     *
     */
    while (packs--) {

        __st_mi pk_a = __st_load_i(pa++);
        __st_mi pk_b = __st_load_i(pb++);

        const __st_mi mask = __st_m_setall_i32(0xFF00FF00);
        __st_mi pk_even = __st_m_mullo_i16(pk_a, pk_b);
        __st_mi pk_odd = __st_m_mullo_i16(__st_m_sr_i16(pk_a, 8), __st_m_sr_i16(pk_b, 8));
        pk_odd = __st_m_sl_i16(pk_odd, 8);
        __st_mi pk_dst = __st_m_xor_i(
            pk_even,
            __st_m_and_i(
                __st_m_xor_i(pk_even, pk_odd),
                mask
            )
        );
        __st_store_i(pd++, pk_dst);
    }

    a   = (st_u8 *)pa;
    b   = (st_u8 *)pb;
    dst = (st_u8 *)pd;

    while (remainder--)
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
    if (st_check_data_dtype(dst, a->dtype))
        __st_raise_dtype_error();

    if (st_check_data_dtype(dst, b->dtype))
        __st_raise_dtype_error();

    if (st_check_data_size(dst, a->size))
        __st_raise_length_error();

    if (st_check_data_size(dst, b->size))
        __st_raise_length_error();

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
    if (st_check_vec_len(a, b->len))
        __st_raise_length_error();

    if (st_check_vec_dtype(a, b->dtype))
        __st_raise_dtype_error();


    size_t len = a->len;
    st_dtype dtype = a->dtype;
    st_vector *dst = st_new_vector(len, dtype);

    __data_mul(dst->data, a->data, b->data);
    return dst;
}

st_matrix *
st_mat_mul(st_matrix *a, st_matrix *b)
{
    if (st_check_mat_nrow(a, b->nrow))
        __st_raise_length_error();

    if (st_check_mat_ncol(a, b->ncol))
        __st_raise_length_error();

    if (st_check_mat_dtype(a, b->dtype))
        __st_raise_dtype_error();

    size_t nrow = a->nrow;
    size_t ncol = a->ncol;
    st_dtype dtype = a->dtype;
    st_matrix *dst = st_new_matrix(nrow, ncol, dtype);

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
    size_t psize     = __st_m_psize_i32;
    size_t packs   = n / psize;
    size_t remainder = n % psize;

    __st_mi *pa = (__st_mi *) a;
    __st_mi *pb = (__st_mi *) b;
    __st_mi *pd = (__st_mi *) dst;

    while (packs--) {

        __st_mi __a = __st_load_i(pa++);
        __st_mi __b = __st_load_i(pb++);
        __b = __st_m_add_i32(__a, __b);
        __st_store_i(pd++, __b);
    }

    a   = (st_i32 *)pa;
    b   = (st_i32 *)pb;
    dst = (st_i32 *)pd;

    while (remainder--)
        *dst++ = (*a++) + (*b++);
}

static void
__simd_add_u8(size_t n, st_u8 *dst, st_u8 *a, st_u8 *b)
{
    size_t psize     = __st_m_psize_u8;
    size_t packs   = n / psize;
    size_t remainder = n % psize;

    __st_mi *pa = (__st_mi *) a;
    __st_mi *pb = (__st_mi *) b;
    __st_mi *pd = (__st_mi *) dst;

    /* 16 * (1*8) = 128 */
    while (packs--) {

        __st_mi __a = __st_load_i(pa++);
        __st_mi __b = __st_load_i(pb++);
        __b = __st_m_add_i8(__a, __b);
        __st_store_i(pd++, __b);
    }

    a   = (st_u8 *)pa;
    b   = (st_u8 *)pb;
    dst = (st_u8 *)pd;

    while (remainder--)
        *dst++ = (*a++) + (*b++);
}

static void
__simd_add_bool(size_t n, st_bool *dst, st_bool *a, st_bool *b)
{
    size_t psize     = __st_m_psize_u8;
    size_t packs   = n / psize;
    size_t remainder = n % psize;

    __st_mi *pa = (__st_mi *) a;
    __st_mi *pb = (__st_mi *) b;
    __st_mi *pd = (__st_mi *) dst;

    while (packs--) {

        __st_mi __a = __st_load_i(pa++);
        __st_mi __b = __st_load_i(pb++);
        __b = __st_m_or_i(__a, __b);
        __st_store_i(pd++, __b);
    }

    a   = (st_bool *)pa;
    b   = (st_bool *)pb;
    dst = (st_bool *)pd;

    while (remainder--)
        *dst++ = (*a++) || (*b++);
}

static void
__data_add(const __st_data *dst, const __st_data *a, const __st_data *b)
{
    if (st_check_data_dtype(dst, a->dtype))
        __st_raise_dtype_error();

    if (st_check_data_dtype(dst, b->dtype))
        __st_raise_dtype_error();

    if (st_check_data_size(dst, a->size))
        __st_raise_length_error();

    if (st_check_data_size(dst, b->size))
        __st_raise_length_error();

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
    if (st_check_vec_len(a, b->len))
        __st_raise_length_error();

    if (st_check_vec_dtype(a, b->dtype))
        __st_raise_dtype_error();

    size_t len = a->len;
    st_dtype dtype = a->dtype;
    st_vector *dst = st_new_vector(len, dtype);

    __data_add(dst->data, a->data, b->data);
    return dst;
}

st_matrix *
st_mat_add(st_matrix *a, st_matrix *b)
{
    if (st_check_mat_nrow(a, b->nrow))
        __st_raise_length_error();

    if (st_check_mat_ncol(a, b->ncol))
        __st_raise_length_error();

    if (st_check_mat_dtype(a, b->dtype))
        __st_raise_dtype_error();

    size_t nrow = a->nrow;
    size_t ncol = a->ncol;
    st_dtype dtype = a->dtype;
    st_matrix *dst = st_new_matrix(nrow, ncol, dtype);

    __data_add(dst->data, a->data, b->data);
    return dst;
}

/* =================================================================================================
 * call pair function
 */

// st_decimal
// st_vec_pair(st_vector *vl, st_vector *vr, fp_pair fp, void *argv[])
// {
//     st_dtype dtype = st_check_vec_dtype(vl, vr->dtype);

//     size_t i;
//     void *e1, *e2;
//     for __st_iter_vector2(i, e1, e2, vl, vr)
//             fp(e1, e2, dtype, argv);
// }
