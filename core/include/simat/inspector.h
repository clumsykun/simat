#ifndef SIMAT_INSPECTOR_H
#define SIMAT_INSPECTOR_H
#include <stdbool.h>
#include <stddef.h>

typedef void (*free_fp)(void *);
typedef void (*status_fp)(void *);

void __st_ds_add(void *target, free_fp ffp, status_fp sfp, bool *temp);
void st_ds_clear_all(void);
void st_ds_clear_temp(void);
void st_ds_display(void);

extern bool __st_is_error;
extern bool __st_access_error;
extern bool __st_dtype_error;
extern bool __st_out_range_error;
extern bool __st_length_error;
extern bool __st_is_invalid;

bool     st_is_invalid(const void *target);
void   __st_check_invalid_error(const void *target);
double __st_raise_access_error(void);
size_t __st_raise_dtype_error(void);
double __st_raise_out_range_error(void);
void   __st_raise_length_error(void);
void   __st_check__(const char *file, const size_t line);

#define __st_check() __st_check__(__FILE__, __LINE__)

#endif /* SIMAT_INSPECTOR_H */
