#include <stdio.h>
#include <math.h>
#include <simat.h>

st_vector *test_vec_1(void) {

    st_vector *vec = st_new_vector(5);
    st_vec_assign(vec, 0, 3.1415926535);
    st_vec_assign(vec, 1, 2.7182818284);
    st_vec_assign(vec, 2, 0.5772156649);
    st_vec_assign(vec, 3, 4.6692016091);
    st_vec_assign(vec, 4, 2.5029078750);
    return vec;
}

void test__st_vec_min(void)
{
    char *name = "st_vec_min";
    double ret, target = 0.5772156649;

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
    double ret, target = 4.6692016091;

    /* test content start */

    st_vector *vec = test_vec_1();
    ret = st_vec_max(vec);

    /* test content end */

    if (ret == target) printf("    OK --> %s\n", name);
    else printf("FAILED --> %s\n", name);

}


int main()
{
    printf("unit test start:\n");

    test__st_vec_min();
    test__st_vec_max();

    printf("\n");
    return 0;
}
