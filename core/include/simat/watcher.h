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

void   __st_check_invalid_error(const void *target);
double __st_raise_access_error(void);
size_t __st_raise_dtype_error(void);
double __st_raise_out_range_error(void);
void   __st_raise_length_error(void);
void   __st_check__(const char *file, const size_t line);

#define __st_check() __st_check__(__FILE__, __LINE__)

#endif /* CORE_WATCHER_H */
