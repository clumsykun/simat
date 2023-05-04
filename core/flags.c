#include <stdlib.h>
#include <stdbool.h>


bool __is_error = false;

double __double_raise_error(void)
{
    __is_error = true;
    return 0;
}

size_t __size_raise_error(void)
{
    __is_error = true;
    return 0;
}
