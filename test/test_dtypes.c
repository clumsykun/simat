#include <stdio.h>
#include <assert.h>
#include "flags.h"
#include "dtypes.h"


int main()
{
    size_t len = 100;
    double assign_value = 3.14;

    st_vector *vec = st_new_double_vector(len);
    st_vec_assign(vec, assign_value);

    printf("idx 1 %.2f\n", st_vec_access(vec, 1));

    assert(st_vec_access(vec, 1) == assign_value);

    return 0;
}
