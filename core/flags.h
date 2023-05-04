#ifndef CORE_FLAGS_H
#define CORE_FLAGS_H
#include <stdlib.h>
#include <stdbool.h>

extern bool __is_error;

double __double_raise_error(void);
size_t __size_raise_error(void);

#endif /* CORE_FLAGS_H */