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

#define st_byte_bool 1
#define st_byte_u8   1
#define st_byte_i32  4
#define st_byte_d64  8

#define st_abs(x) ((x) >= 0 ? (x) : -(x))
