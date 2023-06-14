
// #define st_sse4_1
#define st_avx2

/* =================================================================================================
 * SSE4.1 settings
 */

#ifdef st_sse4_1

#define st_mi     __m128i
#define st_md     __m128d

#define st_load_i32(p)                _mm_loadu_si128((__m128i *)p)
#define st_load_d64(p)                _mm_loadu_pd((double *)p)
#define st_store_i32(p, i128)         _mm_storeu_si128((__m128i *)p, i128)
#define st_store_d64(p, d128)         _mm_storeu_pd((double *)p, d128)

#define st_m_add_i8(i128_a, i128_b)   _mm_add_epi8(i128_a, i128_b)
#define st_m_add_i32(i128_a, i128_b)  _mm_add_epi32(i128_a, i128_b)
#define st_m_add_d64(d128_a, d128_b)  _mm_add_pd(d128_a, d128_b)

#define st_m_sub_i32(i128_a, i128_b)   _mm_sub_epi32(i128_a, i128_b)
#define st_m_sub_d64(d128_a, d128_b)  _mm_sub_pd(d128_a, d128_b)

#define st_m_mul_i32(i128_a, i128_b)  _mm_mullo_epi32(i128_a, i128_b)
#define st_m_mul_d64(d128_a, d128_b)  _mm_mul_pd(d128_a, d128_b)
#define st_m_mullo_i16(i128_a, i128_b) _mm_mullo_epi16(i128_a, i128_b)

#define st_m_and_i(i128_a, i128_b) _mm_and_si128(i128_a, i128_b)
#define st_m_or_i(i128_a, i128_b)  _mm_or_si128(i128_a, i128_b)
#define st_m_or_d(d128_a, d128_b)  _mm_or_pd(d128_a, d128_b)
#define st_m_xor_i(i128_a, i128_b) _mm_xor_si128(i128_a, i128_b)
#define st_m_xor_d(d128_a, d128_b) _mm_xor_pd(d128_a, d128_b)

#define st_m_zero_i() _mm_setzero_si128()
#define st_m_zero_d() _mm_setzero_pd()
#define st_m_set_i32(st_i32) _mm_set1_epi32(st_i32)

#define st_m_srai_i16(i128, imm8)      _mm_srai_epi16(i128, imm8)
#define st_m_slli_i16(i128, imm8)      _mm_slli_epi16(i128, imm8)

#define st_m_size_d64 2
#define st_m_size_i32 4
#define st_m_size_u8  16
#define st_m_size_b   16

#endif /* st_sse4_1 */


/* =================================================================================================
 * AVX2 settings
 */

#ifdef st_avx2

#define st_mi     __m256i
#define st_md     __m256d

#define st_load_i32(p)                _mm256_loadu_si256((__m256i *)p)
#define st_load_d64(p)                _mm256_loadu_pd((double *)p)
#define st_store_i32(p, i256)         _mm256_storeu_si256((__m256i *)p, i256)
#define st_store_d64(p, d256)         _mm256_storeu_pd((double *)p, d256)

#define st_m_add_i8(i256_a, i256_b)   _mm256_add_epi8(i256_a, i256_b)
#define st_m_add_i32(i256_a, i256_b)  _mm256_add_epi32(i256_a, i256_b)
#define st_m_add_d64(d256_a, d256_b)  _mm256_add_pd(d256_a, d256_b)

#define st_m_sub_i32(i256_a, i256_b)   _mm256_sub_epi32(i256_a, i256_b)
#define st_m_sub_d64(d256_a, d256_b)  _mm256_sub_pd(d256_a, d256_b)

#define st_m_mul_i32(i256_a, i256_b)  _mm256_mullo_epi32(i256_a, i256_b)
#define st_m_mul_d64(d256_a, d256_b)  _mm256_mul_pd(d256_a, d256_b)
#define st_m_mullo_i16(i256_a, i256_b) _mm256_mullo_epi16(i256_a, i256_b)

#define st_m_and_i(i256_a, i256_b) _mm256_and_si256(i256_a, i256_b)
#define st_m_or_i(i256_a, i256_b)  _mm256_or_si256(i256_a, i256_b)
#define st_m_or_d(d256_a, d256_b)  _mm256_or_pd(d256_a, d256_b)
#define st_m_xor_i(i256_a, i256_b) _mm256_xor_si256(i256_a, i256_b)
#define st_m_xor_d(d256_a, d256_b) _mm256_xor_pd(d256_a, d256_b)

#define st_m_zero_i() _mm256_setzero_si256()
#define st_m_zero_d() _mm256_setzero_pd()
#define st_m_set_i32(st_i32) _mm256_set1_epi32(st_i32)

#define st_m_srai_i16(i256, imm8)      _mm256_srai_epi16(i256, imm8)
#define st_m_slli_i16(i256, imm8)      _mm256_slli_epi16(i256, imm8)

#define st_m_size_d64 4
#define st_m_size_i32 8
#define st_m_size_u8  32
#define st_m_size_b   32

#endif /* st_sse4_1 */
