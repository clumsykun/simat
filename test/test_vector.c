#include <stdio.h>
#include <math.h>
#include <simat.h>

st_vector *test_vec_1(void) {

    /**
     * [3.141592653589793, 2.718281828459045, 0.577215664901532, 1.414213562373095, 5.391247]
     */

    st_vector *vec = st_new_vector(5);
    st_vec_assign(vec, 0, 3.141592653589793);
    st_vec_assign(vec, 1, 2.718281828459045);
    st_vec_assign(vec, 2, 0.577215664901532);
    st_vec_assign(vec, 3, 1.414213562373095);
    st_vec_assign(vec, 4, 5.391247);
    return vec;
}

void test__st_vec_min(void)
{
    char *name = "st_vec_min";
    double ret, target = 0.577215664901532;

    /* test content start */

    st_vector *vec = test_vec_1();
    ret = st_vec_min(vec);

    /* test content end */

    if (ret == target) printf("    OK --> %s\n", name);
    else printf("FAILED --> %s\n", name);
}

void test__st_vec_max(void)
{
    char *name = "st_vec_max";
    double ret, target = 5.391247;

    /* test content start */

    st_vector *vec = test_vec_1();
    ret = st_vec_max(vec);

    /* test content end */

    if (ret == target) printf("    OK --> %s\n", name);
    else printf("FAILED --> %s\n", name);
}

void test__st_vec_norm(void)
{
    char *name = "st_vec_norm";
    double ret, target = 6.975484401734171;

    /* test content start */

    st_vector *vec = test_vec_1();
    ret = st_vec_norm(vec);

    /* test content end */

    if (ret == target) printf("    OK --> %s\n", name);
    else printf("FAILED --> %s\n", name);
}

void test__st_vec_scale(void)
{
    char *name = "st_vec_scale";
    double ret, target = 0;

    /* test content start */

    ret = 0;
    st_vector *vec = test_vec_1();
    st_vec_scale(vec, 0, 1);

    if (st_vec_max(vec) != 1)
        ret = 1;

    if (st_vec_min(vec) != 0)
        ret = 1;

    /* test content end */

    if (ret == target) printf("    OK --> %s\n", name);
    else printf("FAILED --> %s\n", name);
}

int main()
{
    printf("unit test of vector start:\n");

    test__st_vec_min();
    test__st_vec_max();
    test__st_vec_norm();
    test__st_vec_scale();

    printf("\n");
    st_ds_display();

    printf("\n");
    return 0;
}
