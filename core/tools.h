#ifndef CORE_TOOLS_H
#define CORE_TOOLS_H
#include "dtypes.h"

void __std_free(void *ptr);
void __swap_int(int *left, int *right);
void __swap_double(double *left, double *right);
void __swap_double_p(double **left, double **right);
size_t __size_t_dtype_unknown_error(void);
double __double_dtype_unknown_error(void);
void __dtype_unknown_error(void);
int __rand_int(int min, int max);
void __double_assign(char *dest, double src, enum dtype dtype);

#endif /* CORE_TOOLS_H */
