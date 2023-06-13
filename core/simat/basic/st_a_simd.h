
#define st_sse4_1

/* =================================================================================================
 * SSE4.1 settings
 */

#ifdef st_sse4_1

#define st_mi     __m128i
#define st_md     __m128d

#define st_load_d64(p)                _mm_load_pd((double *)p)
#define st_load_i32(p)                _mm_load_si128((__m128i *)p)
#define st_store_d64(p, d128)         _mm_store_pd((double *)p, d128)
#define st_store_i32(p, i128)         _mm_store_si128((__m128i *)p, i128)
#define st_m_mul_d64(d128_a, d128_b)  _mm_mul_pd(d128_a, d128_b)
#define st_m_mul_i32(i128_a, i128_b)  _mm_mullo_epi32(i128_a, i128_b)
#define st_m_add_d64(d128_a, d128_b)  _mm_add_pd(d128_a, d128_b)
#define st_m_add_i32(i128_a, i128_b)  _mm_add_epi32(i128_a, i128_b)

#define st_m_sub_i32(i128_a, i128_b)  _mm_sub_epi32(i128_a, i128_b)

#define st_m_sub_d64(d128_a, d128_b)  _mm_sub_pd(d128_a, d128_b)
#define st_m_xor_i128(i128_a, i128_b) _mm_xor_si128(i128_a, i128_b)
#define st_m_or_i128(i128_a, i128_b)  _mm_or_si128(i128_a, i128_b)

#define st_m_zero_d64() _mm_setzero_pd()

#define st_m_size_d64 2
#define st_m_size_i32 4
#define st_m_size_u8  16
#define st_m_size_b   16

#endif /* st_sse4_1 */
