#ifndef CORE_DS_H
#define CORE_DS_H

#include <stdlib.h>
#include <stdbool.h>

typedef enum __st_dtype__ {
    st_dtype_bool = 1,
    st_dtype_u8,         /* 8-bit unsigned char */
    st_dtype_i32,        /* 32-bit st_i32 */
    st_dtype_d64,        /* 64-bit decimal */
} st_dtype;

#define st_bool    bool
#define st_u8      unsigned char
#define st_i32     int
#define st_d64     double
#define st_decimal st_d64

#define st_simd_128  __m128
#define st_simd_i128 __m128i
#define st_simd_d128 __m128d

#define st_byte_bool 1
#define st_byte_u8   1
#define st_byte_i32  4
#define st_byte_d64  8


#define st_abs(x) ((x) >= 0 ? (x) : -(x))

typedef void (*free_fp)(void *);
typedef void (*status_fp)(void *);

void __st_ds_add(void *target, free_fp ffp, status_fp sfp, st_bool *temp);
void st_ds_clear_all(void);
void st_ds_clear_temp(void);
void st_ds_display(void);
st_bool st_is_invalid(const void *target);
st_i32  st_free(const void *target);

#endif /* CORE_DS_H */
