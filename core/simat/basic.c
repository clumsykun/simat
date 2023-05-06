#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tools.h"

/* the standard way to free memory */
void __std_free(void *ptr)
{
    free(ptr);
    ptr = NULL;
}

/**
 * check program is correct or not after any operation
 * probably need some advanced handling
 */
void __check()
{
    if (__is_error)
        abort();
}

void __swap(char *a, char *b, size_t len)
{
    char tmp;
    while (len--) {
        tmp = *a;
        *a++ = *b;
        *b++ = tmp;
    }
}

void __swap_double(double *left, double *right)
{
    double tmp = *left;
    *left = *right;
    *right = tmp;
}

void __swap_double_p(double **left, double **right)
{
    double tmp = **left;
    **left = **right;
    **right = tmp;
}

/* min and max are inclusive */
int __rand_int(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

double __rand_double(int min, int max)
{
    return (rand() % (max - min)) + min +((double)rand() / RAND_MAX);
}

void assign(void *__restrict__ dest, const void *__restrict__ src, size_t len)
{
    const char *s = src;
    char *d = dest;

    while (len--)
        *d++ = *s++;
}

void dassign(char *dest, double src, enum st_dtype dtype)
{
    switch (dtype) {
        case st_bool:
            *(bool *)dest = (bool)src;
            break;

        case st_pixel:
            *(unsigned char *)dest = (unsigned char)src;
            break;

        case st_int:
            *(int *)dest = (int)src;
            break;

        case st_double:
            *(double *)dest = (double)src;
            break;

        default:
            break;
    }
}