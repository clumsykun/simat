#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "test.h"

result *test__st_mat_min(result *rp)
{
    rp->name = "st_mat_min";
    double target = 0.1;

    st_dataset *iris = st_load_iris();
    rp->value = !equal(st_mat_min(iris->X), target);

    return rp;
}


int test__matrix(void)
{
    printf("unit test of matrix start:\n");

    call_test(test__st_mat_min);

    printf("\n");
    return 0;
}
