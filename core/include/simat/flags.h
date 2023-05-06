#ifndef SIMAT_FLAGS_H
#define SIMAT_FLAGS_H
#include <stdbool.h>
#include <stddef.h>

extern bool __st_is_error;
extern bool __st_access_error;
extern bool __st_dtype_error;

double __st_raise_access_error(void);
size_t __st_raise_dtype_error(void);

#endif /* SIMAT_FLAGS_H */
