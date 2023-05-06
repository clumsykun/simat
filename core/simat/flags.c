#include <stdbool.h>
#include "flags.h"


bool __st_is_error = false;
bool __st_access_error = false;
bool __st_dtype_error = false;

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
