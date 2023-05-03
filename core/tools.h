#ifndef CORE_TOOLS_H
#define CORE_TOOLS_H
#include "dtypes.h"

void __std_free(void *ptr);
void __swap_int(int *left, int *right);
void __swap_double(double *left, double *right);
void __swap_double_p(double **left, double **right);
void __swap(char *a, char *b, size_t len);
size_t __size_t_dtype_unknown_error(void);
double __double_dtype_unknown_error(void);
void __dtype_unknown_error(void);
int __rand_int(int min, int max);
double __rand_double(int min, int max);
void assign(char *dest, const void *src, size_t len);
void dassign(char *dest, double src);
void iassign(char *dest, int src);

#endif /* CORE_TOOLS_H */
