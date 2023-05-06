#include <stdbool.h>
#include "flags.h"


bool __st_is_error = false;

double __st_access_error(void)
{
    __st_is_error = true;
    return 0;
}

size_t __st_dtype_error(void)
{
    __st_is_error = true;
    return 0;
}
