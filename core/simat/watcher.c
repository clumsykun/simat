#include "watcher.h"

bool __st_is_error = false;
bool __st_access_error = false;
bool __st_dtype_error = false;
bool __st_out_range_error = false;
bool __st_length_error = false;
bool __st_invalid_error = false;

void __st_check_invalid_error(const void *target)
{
    __st_invalid_error = st_is_invalid(target);
    if (__st_invalid_error)
        __st_is_error = true;
}

double __st_raise_access_error(void)
{
    __st_is_error = true;
    __st_access_error = true;
    return 0;
}

size_t __st_raise_dtype_error(void)
{
    __st_is_error = true;
    __st_dtype_error = true;
    return 0;
}

double __st_raise_out_range_error(void)
{
    __st_is_error = true;
    __st_out_range_error = true;
    return 0;
}

void __st_raise_length_error(void)
{
    __st_is_error = true;
    __st_length_error = true;
}

/**
 * check program is correct or not after any operation
 * probably need some advanced handling
 */
void __st_check__(const char *file, const size_t line)
{

    if (__st_is_error)
    printf("%s:%d: ", file, line);

    if (__st_invalid_error)
        printf("Error: Invalid simat member!\n");

    if (__st_access_error)
        printf("Error: Access failed!\n");

    if (__st_dtype_error)
        printf("Error: Data type not found!\n");

    if (__st_out_range_error)
        printf("Error: Index out of range!\n");

    if (__st_length_error)
        printf("Error: length not match!\n");

    assert(!__st_is_error);
}
