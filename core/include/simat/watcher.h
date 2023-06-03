#ifndef CORE_WATCHER_H
#define CORE_WATCHER_H

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "ds.h"

extern bool __st_is_error;
extern bool __st_access_error;
extern bool __st_dtype_error;
extern bool __st_out_range_error;
extern bool __st_length_error;
extern bool __st_is_invalid;

double __st_raise_invalid_error__(const char *file, const size_t line);
size_t __st_raise_dtype_error__(const char *file, const size_t line);
double __st_raise_out_range_error__(const char *file, const size_t line);
void   __st_raise_length_error__(const char *file, const size_t line);

#define __st_raise_invalid_error() __st_raise_invalid_error__(__FILE__, __LINE__)
#define __st_raise_dtype_error() __st_raise_dtype_error__(__FILE__, __LINE__)
#define __st_raise_out_range_error() __st_raise_out_range_error__(__FILE__, __LINE__)
#define __st_raise_length_error() __st_raise_length_error__(__FILE__, __LINE__)

#define __st_check_valid(target) \
    if (st_is_invalid(target))   \
        __st_raise_invalid_error__(__FILE__, __LINE__)

#endif /* CORE_WATCHER_H */
