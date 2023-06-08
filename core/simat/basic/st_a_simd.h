
/* =================================================================================================
 * datatypes
 */


#define st_simd_128      __m128
#define st_simd_i128     __m128i
#define st_simd_d128     __m128d
#define st_access_d128   _mm_loadu_pd 
#define st_access_i128   _mm_loadu_si128
#define st_assign_d128   _mm_storeu_pd
#define st_assign_i128   _mm_storeu_si128
#define st_simd_mul_d64 _mm_mul_pd
#define st_simd_or_i128  _mm_or_si128
#define st_simd_add_i32  _mm_add_epi32

