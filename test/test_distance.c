#include "test.h"

// /**
//  * [3.141592653589793, 2.718281828459045, 0.577215664901532, 1.414213562373095, 1.618033988749894]
//  */
// st_vector *test_vec_1(void) {

//     st_vector *vec = st_new_vector(5);
//     st_vec_assign(vec, 0, 3.141592653589793);
//     st_vec_assign(vec, 1, 2.718281828459045);
//     st_vec_assign(vec, 2, 0.577215664901532);
//     st_vec_assign(vec, 3, 1.414213562373095);
//     st_vec_assign(vec, 4, 1.618033988749894);
//     return vec;
// }

// /**
//  * [6.67428, 9.10938215, 6.62606896, 5.2917720859, 1.602176487]
//  */
// st_vector *test_vec_2(void) {

//     st_vector *vec = st_new_vector(5);
//     st_vec_assign(vec, 0, 6.67428);
//     st_vec_assign(vec, 1, 9.10938215);
//     st_vec_assign(vec, 2, 6.62606896);
//     st_vec_assign(vec, 3, 5.2917720859);
//     st_vec_assign(vec, 4, 1.602176487);
//     return vec;
// }

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


void test__st_dist_manhattan(void)
{
    char *name = "st_dist_manhattan";
    double ret, target = 19.86605699;

    /* test content start */

    st_vector *vec1 = test_vec_1();
    st_vector *vec2 = test_vec_2();

    /* test content end */

    if (ret == target) printf("    OK --> %s\n", name);
    else printf("FAILED --> %s\n", name);
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

    printf("\n");
    return 0;
    return 0;
}
