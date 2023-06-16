
#define st_sse4_1
// #define st_avx2

/* =================================================================================================
 * SSE4.1 settings
 */

#ifdef st_sse4_1

#define __st_mi         __m128i
#define __st_md         __m128d
#define __st_m_psize_d64 2
#define __st_m_psize_i32 4
#define __st_m_psize_u8  16
#define __st_m_psize_b   16

#define __st_load_i32(p)         _mm_loadu_si128((__m128i *)p)
#define __st_load_d64(p)         _mm_loadu_pd((double *)p)
#define __st_store_i32(p, i)     _mm_storeu_si128((__m128i *)p, i)
#define __st_store_d64(p, d)     _mm_storeu_pd((double *)p, d)

#define __st_m_abs_i8(i)         _mm_abs_epi8(i)
#define __st_m_abs_i32(i)        _mm_abs_epi32(i)

#define __st_m_add_i8(i1, i2)    _mm_add_epi8(i1, i2)
#define __st_m_add_i32(i1, i2)   _mm_add_epi32(i1, i2)
#define __st_m_add_d64(d1, d2)   _mm_add_pd(d1, d2)

#define __st_m_sub_i32(i1, i2)   _mm_sub_epi32(i1, i2)
#define __st_m_sub_d64(d1, d2)   _mm_sub_pd(d1, d2)

#define __st_m_mul_i32(i1, i2)   _mm_mullo_epi32(i1, i2)
#define __st_m_mul_d64(d1, d2)   _mm_mul_pd(d1, d2)
#define __st_m_mullo_i16(i1, i2) _mm_mullo_epi16(i1, i2)

#define __st_m_min_u8(i1,i2)     _mm_min_epu8 (i1, i2)
#define __st_m_min_i32(i1, i2)   _mm_min_epi32(i1, i2)
#define __st_m_min_d64(d1, d2)   _mm_min_pd(d1, d2)

#define __st_m_and_i(i1, i2)     _mm_and_si128(i1, i2)
#define __st_m_and_d(d1, d2)     _mm_and_pd(d1, d2)
#define __st_m_or_i(i1, i2)      _mm_or_si128(i1, i2)
#define __st_m_or_d(d1, d2)      _mm_or_pd(d1, d2)
#define __st_m_xor_i(i1, i2)     _mm_xor_si128(i1, i2)
#define __st_m_xor_d(d1, d2)     _mm_xor_pd(d1, d2)

#define __st_m_zero_i()          _mm_setzero_si128()
#define __st_m_zero_d()          _mm_setzero_pd()

#define __st_m_setall_i32(i32)   _mm_set1_epi32(i32)
#define __st_m_setall_i64(i64)   _mm_set1_epi64x(i64)
#define __st_m_setall_d64(d64)   _mm_set1_pd(d64)

/* Cast */
#define __st_m_cast_i2d(i)       _mm_castsi128_pd(i)

/* Shift left and right */
#define __st_m_sr_i16(i, imm8)   _mm_srai_epi16(i, imm8)
#define __st_m_sl_i16(i, imm8)   _mm_slli_epi16(i, imm8)

#endif /* st_sse4_1 */


/* =================================================================================================
 * AVX2 settings
 */

#ifdef st_avx2

#define __st_mi         __m256i
#define __st_md         __m256d
#define __st_m_psize_d64 4
#define __st_m_psize_i32 8
#define __st_m_psize_u8  32
#define __st_m_psize_b   32

#define __st_load_i32(p)         _mm256_loadu_si256((__m256i *)p)
#define __st_load_d64(p)         _mm256_loadu_pd((double *)p)
#define __st_store_i32(p, i)     _mm256_storeu_si256((__m256i *)p, i)
#define __st_store_d64(p, d)     _mm256_storeu_pd((double *)p, d)

#define __st_m_abs_i8(i)         _mm256_abs_epi8(i)
#define __st_m_abs_i32(i)        _mm256_abs_epi32(i)

#define __st_m_add_i8(i1, i2)    _mm256_add_epi8(i1, i2)
#define __st_m_add_i32(i1, i2)   _mm256_add_epi32(i1, i2)
#define __st_m_add_d64(d1, d2)   _mm256_add_pd(d1, d2)

#define __st_m_sub_i32(i1, i2)   _mm256_sub_epi32(i1, i2)
#define __st_m_sub_d64(d1, d2)   _mm256_sub_pd(d1, d2)

#define __st_m_mul_i32(i1, i2)   _mm256_mullo_epi32(i1, i2)
#define __st_m_mul_d64(d1, d2)   _mm256_mul_pd(d1, d2)
#define __st_m_mullo_i16(i1, i2) _mm256_mullo_epi16(i1, i2)

#define __st_m_min_u8(i1,i2)     _mm256_min_epu8 (i1, i2)
#define __st_m_min_i32(i1, i2)   _mm256_min_epi32(i1, i2)
#define __st_m_min_d64(d1, d2)   _mm256_min_pd(d1, d2)

#define __st_m_and_i(i1, i2)     _mm256_and_si256(i1, i2)
#define __st_m_and_d(da, db)     _mm256_and_pd(da, db)
#define __st_m_or_i(i1, i2)      _mm256_or_si256(i1, i2)
#define __st_m_or_d(d1, d2)      _mm256_or_pd(d1, d2)
#define __st_m_xor_i(i1, i2)     _mm256_xor_si256(i1, i2)
#define __st_m_xor_d(d1, d2)     _mm256_xor_pd(d1, d2)

#define __st_m_zero_i()          _mm256_setzero_si256()
#define __st_m_zero_d()          _mm256_setzero_pd()

#define __st_m_setall_i32(i32)   _mm256_set1_epi32(i32)
#define __st_m_setall_i64(i64)   _mm256_set1_epi64x(i64)
#define __st_m_setall_d64(d64)   _mm256_set1_pd(d64)

/* Cast */
#define __st_m_cast_i2d(i)       _mm256_castsi256_pd(i)

/* Shift left and right */
#define __st_m_sr_i16(i, imm8)   _mm256_srai_epi16(i, imm8)
#define __st_m_sl_i16(i, imm8)   _mm256_slli_epi16(i, imm8)

#endif /* st_sse4_1 */
