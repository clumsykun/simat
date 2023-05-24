#ifndef SIMAT_INSPECTOR_H
#define SIMAT_INSPECTOR_H
#include <stdbool.h>
#include <stddef.h>

#define MAX_ERROR_TRACK 100

extern bool __st_is_error;
extern bool __st_access_error;
extern bool __st_dtype_error;
extern bool __st_out_range_error;
extern bool __st_length_error;

double __st_raise_access_error(void);
size_t __st_raise_dtype_error(void);
double __st_raise_out_range_error(void);
void   __st_raise_length_error(void);
void __st_check__(const char *file, const size_t line);

typedef void (*free_fp)(void *);
void *__st_pool_add(void *data, free_fp fp, bool *temp);
void __st_free_all(void);

#endif /* SIMAT_INSPECTOR_H */
