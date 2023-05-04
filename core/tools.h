#ifndef CORE_TOOLS_H
#define CORE_TOOLS_H
#include "dtypes.h"

void __std_free(void *ptr);
void __swap_double(double *left, double *right);
void __swap_double_p(double **left, double **right);
void __swap(char *a, char *b, size_t len);
int __rand_int(int min, int max);
double __rand_double(int min, int max);
void assign(void *__restrict__ dest, const void *__restrict__ src, size_t len);
void dassign(char *dest, double src, enum dtype dtype);
void __check();

#endif /* CORE_TOOLS_H */
