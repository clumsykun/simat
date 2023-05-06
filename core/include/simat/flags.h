#ifndef CORE_FLAGS_H
#define CORE_FLAGS_H
#include <stdbool.h>
#include <stddef.h>


extern bool __st_is_error;

double __st_access_error(void);
size_t __st_dtype_error(void);

#endif /* CORE_FLAGS_H */
