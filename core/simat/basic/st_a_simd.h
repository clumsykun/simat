
/* =================================================================================================
 * datatypes
 */


#define st_simd_128      __m128
#define st_simd_i128     __m128i
#define st_simd_d128     __m128d

#define st_load_d128(p)                 _mm_loadu_pd((double *)p)
#define st_load_i128(p)                 _mm_loadu_si128((__m128i *)p)
#define st_store_d128(p, d128)          _mm_storeu_pd((double *)p, d128)
#define st_store_i128(p, i128)          _mm_storeu_si128((__m128i *)p, i128)
#define st_simd_mul_d64(d128_a, d128_b) _mm_mul_pd(d128_a, d128_b)
#define st_simd_or_i128(i128_a, i128_b) _mm_or_si128(i128_a, i128_b)
#define st_simd_add_i32(i128_a, i128_b) _mm_add_epi32(i128_a, i128_b)



#define st_bsize_128_d64 2
#define st_bsize_128_i32 4
#define st_bsize_128_u8  16
#define st_bsize_128_b   16

