#include "test.h"

result * test__st_vec_mean(result *rp)
{
    rp->name = "st_vec_mean";
    double target = 1.89386753961467;

    st_vector *vec = test_vec_1();
    double mean = st_vec_mean(vec);
    rp->value = !equal(st_precise(mean, 14), target);

    return rp;
}

result * test__st_vec_var(result *rp)
{
    rp->name = "st_vec_var";

    st_vector *vec = test_vec_1();
    double var = st_vec_var(vec, 0);
    rp->value = !equal(st_precise(var, 14), 0.85524022490939);

    var = st_vec_var(vec, 1);
    rp->value = !equal(st_precise(var, 14), 1.06905028113674);

    return rp;
}

result * test__st_vec_std(result *rp)
{
    rp->name = "st_vec_std";
    double target = 0.92479199007635;

    st_vector *vec = test_vec_1();
    double std = st_vec_std(vec, 0);
    rp->value = !equal(st_precise(std, 14), target);

    return rp;
}

result * test__st_vec_cov(result *rp)
{
    rp->name = "st_vec_cov";

    st_vector *vec1 = test_vec_1();
    st_vector *vec2 = test_vec_2();
    double cov = st_stats_cov(vec1, vec2, 1);
    rp->value = !equal(st_precise(cov, 14), 1.03329797634101);
    rp->value = !equal(st_stats_cov(vec1, vec1, 1), st_vec_var(vec1, 1));

    return rp;
}

int test__stats()
{
    printf("unit test of stats start:\n");

    call_test(test__st_vec_mean);
    call_test(test__st_vec_var);
    call_test(test__st_vec_std);
    call_test(test__st_vec_cov);

    printf("\n");
    return 0;
}
