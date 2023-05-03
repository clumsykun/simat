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

void __swap_int(int *left, int *right)
{
    int tmp = *left;
    *left = *right;
    *right = tmp;
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

size_t __size_t_dtype_unknown_error(void)
{
    fprintf(stderr, "Data type unknown error! Exiting...\n");
    exit(EXIT_FAILURE);
    return 0;
}

double __double_dtype_unknown_error(void)
{
    fprintf(stderr, "Data type unknown error! Exiting...\n");
    exit(EXIT_FAILURE);
    return 0;
}

void __dtype_unknown_error(void)
{
    fprintf(stderr, "Data type unknown error! Exiting...\n");
    exit(EXIT_FAILURE);
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

void assign(char *dest, const void *src, size_t len)
{
    const char *p = src;

    while (len--)
        *dest++ = *p++;
}

void dassign(char *dest, double src, enum dtype dtype)
{
    switch (dtype) {
        case dtype_bool:
            *(bool *)dest = (bool)src;
            break;

        case dtype_pixel:
            *(pixel *)dest = (pixel)src;
            break;

        case dtype_int:
            *(int *)dest = (int)src;
            break;

        case dtype_double:
            *(double *)dest = (double)src;
            break;

        default:
            break;
    }
}
