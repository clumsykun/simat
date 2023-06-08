#include <stdlib.h>
#include <stdio.h>
#include "st_b_watcher.h"

st_bool __st_is_debug = false;
st_bool __st_is_error = false;
st_bool __st_dtype_error = false;
st_bool __st_out_range_error = false;
st_bool __st_length_error = false;
st_bool __st_invalid_error = false;

/* exit simat program */
static void
__exit(void)
{
    abort();
}

/**
 * check program is correct or not after any operation
 * probably need some advanced handling
 */
static void
__st_check(const char *file, const size_t line)
{

    if (__st_is_error)
        printf("%s:%d: ", file, line);

    if (__st_invalid_error)
        printf("Error: Invalid simat member!\n");

    if (__st_dtype_error)
        printf("Error: Data type not found!\n");

    if (__st_out_range_error)
        printf("Error: Index out of range!\n");

    if (__st_length_error)
        printf("Error: Length not match!\n");

    if (__st_is_error)
        __exit();
}

st_d64
__st_raise_invalid_error__(const char *file, const size_t line)
{
    __st_invalid_error = true;
    __st_is_error = true;
    __st_check(file, line);
    return 0;
}

size_t
__st_raise_dtype_error__(const char *file, const size_t line)
{
    __st_is_error = true;
    __st_dtype_error = true;
    __st_check(file, line);
    return 0;
}

st_d64
__st_raise_out_range_error__(const char *file, const size_t line)
{
    __st_is_error = true;
    __st_out_range_error = true;
    __st_check(file, line);
    return 0;
}

void
__st_raise_length_error__(const char *file, const size_t line)
{
    __st_is_error = true;
    __st_length_error = true;
    __st_check(file, line);
}
