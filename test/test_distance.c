#include "test.h"

result *test__st_dist_euclid(result *rp)
{
    rp->name = "st_dist_euclid";
    rp->value = false;
    double target = 10.2445293;

    st_vector *vec1 = test_vec_1();
    st_vector *vec2 = test_vec_2();
    double dist = st_dist_euclid(vec1, vec2);
    rp->value = !equal(st_precise(dist, 7), target);
    return rp;
}

result *test__st_dist_cosine(result *rp)
{
    rp->name = "st_dist_cosine";
    rp->value = false;
    double target = 0.8902623;

    st_vector *vec1 = test_vec_1();
    st_vector *vec2 = test_vec_2();
    double dist = st_dist_cosine(vec1, vec2);
    rp->value = !equal(st_precise(dist, 7), target);

    return rp;
}

result *test__st_dist_manhattan(result *rp)
{
    rp->name = "st_dist_manhattan";
    double target = 19.8660569;

    /* test content start */

    st_vector *vec1 = test_vec_1();
    st_vector *vec2 = test_vec_2();
    double dist = st_dist_manhattan(vec1, vec2);
    rp->value = !equal(st_precise(dist, 7), target);

    return rp;
}


void test__st_dist_chebyshev(void)
{
    char *name = "st_dist_chebyshev";
    double ret, target = 6.39110032;

    /* test content start */

    st_vector *vec1 = test_vec_1();
    st_vector *vec2 = test_vec_2();

    /* test content end */

    if (ret == target) printf("    OK --> %s\n", name);
    else printf("FAILED --> %s\n", name);
}


void test__st_dist_minkowski(void)
{
    char *name = "st_dist_minkowski";
    double ret, target = 10.24452932;

    /* test content start */

    st_vector *vec1 = test_vec_1();
    st_vector *vec2 = test_vec_2();

    /* test content end */

    if (ret == target) printf("    OK --> %s\n", name);
    else printf("FAILED --> %s\n", name);
}

int test__distance(void)
{
    printf("unit test of distance start:\n");

    call_test(test__st_dist_euclid);
    call_test(test__st_dist_cosine);
    call_test(test__st_dist_manhattan);

    printf("\n");
    return 0;
    return 0;
}
