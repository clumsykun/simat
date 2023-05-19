#include <stdio.h>
#include <assert.h>
#include "inspector.h"


int main()
{

    assert(__st_is_error == false);
    assert(__st_access_error == false);
    assert(__st_dtype_error == false);

    __st_raise_access_error();
    assert(__st_is_error == true);
    assert(__st_access_error == true);
    assert(__st_dtype_error == false);

    __st_raise_dtype_error();
    assert(__st_dtype_error == true);

    printf("OK: inspector\n");
    return 0;
}
