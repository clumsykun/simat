#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "test.h"

result *
test__st_mat_min(result *rp)
{
    rp->name = "st_mat_min";
    double target = 0.1;

    st_dataset *iris = st_load_iris();
    rp->value = !equal(st_mat_min(iris->X), target);

    return rp;
}

result *
test__st_mat_max(result *rp)
{
    rp->name = "st_mat_max";
    double target = 7.9;

    st_dataset *iris = st_load_iris();
    rp->value = !equal(st_mat_max(iris->X), target);

    return rp;
}

result *
test__st_mat_scale(result *rp)
{
    rp->name = "st_mat_scale";

    st_dataset *iris = st_load_iris();
    st_mat_scale(iris->X, 0, 1);
    rp->value = !equal(st_mat_min(iris->X), 0);
    rp->value = !equal(st_mat_max(iris->X), 1);

    return rp;
}

result *
test__st_mat_copy_t(result *rp)
{
    rp->name = "st_mat_copy_t";

    st_dataset *iris = st_load_iris();
    st_matrix *iris_t = st_mat_copy_t(iris->X);

    for (size_t i = 0; i < iris->X->nrow; i++) {
        for (size_t j = 0; j < iris->X->ncol; j++) {
            rp->value = !equal(
                __st_mat_access(iris->X, i, j),
                __st_mat_access(iris_t, j, i)
            );
        }
    }
    return rp;
}

result *
test__st_mat_dot(result *rp)
{
    rp->name = "st_mat_dot";

    st_dataset *iris = st_load_iris();
    st_matrix *iris_t = st_mat_copy_t(iris->X);

    st_matrix *ret = st_mat_dot(iris_t, iris->X);

    rp->value = !equal(st_precise(__st_mat_access(ret, 0, 0), 2), 5223.84);
    rp->value = !equal(st_precise(__st_mat_access(ret, 1, 1), 2), 1430.39);
    rp->value = !equal(st_precise(__st_mat_access(ret, 2, 2), 2), 2582.71);
    rp->value = !equal(st_precise(__st_mat_access(ret, 3, 3), 2), 302.33);

    return rp;
}

int
test__matrix(void)
{
    printf("unit test of matrix start:\n");

    call_test(test__st_mat_min);
    call_test(test__st_mat_max);
    call_test(test__st_mat_scale);
    call_test(test__st_mat_copy_t);
    call_test(test__st_mat_dot);

    printf("DONE\n\n");
    return 0;
}
