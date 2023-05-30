#include "test.h"

/**
 * [3.141592653589793, 2.718281828459045, 0.577215664901532, 1.414213562373095, 1.618033988749894]
 */
st_vector *test_vec_1(void)
{
    st_vector *vec = st_new_vector(5);
    double arr[5] = {
        3.141592653589793,
        2.718281828459045,
        0.577215664901532,
        1.414213562373095,
        1.618033988749894
    };

    memcpy(vec->data->head, arr, sizeof(arr));
    return vec;
}

/**
 * [6.67428, 9.10938215, 6.62606896, 5.2917720859, 1.602176487]
 */
st_vector *test_vec_2(void)
{
    st_vector *vec = st_new_vector(5);
    double arr[5] = {
        6.67428,
        9.10938215,
        6.62606896,
        5.2917720859,
        1.602176487
    };

    memcpy(vec->data->head, arr, sizeof(arr));
    return vec;
}

void call_test(fp fp)
{
    result ret = {NULL, 0};
    result *rp = &ret;

    if (fp(rp)->value)
        printf("FAILED --> %s\n", rp->name);
    else
        printf("    OK --> %s\n", rp->name);
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
    double ret, target = 3.141592653589793;

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
    double ret, target = 4.712735130747071;

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

void test__st_vec_equal(void)
{
    char *name = "st_vec_equal";
    double ret, target = 0;

    /* test content start */

    ret = 0;
    st_vector *vec1 = test_vec_1();
    st_vector *vec2 = test_vec_2();
    st_vector *vec3 = test_vec_1();

    if (!st_vec_equal(vec1, vec1))
        ret = 1;

    if (st_vec_equal(vec1, vec2))
        ret = 1;

    if (!st_vec_equal(vec1, vec3))
        ret = 1;

    /* test content end */

    if (ret == target) printf("    OK --> %s\n", name);
    else printf("FAILED --> %s\n", name);
}

int test__vector()
{
    printf("unit test of vector start:\n");

    test__st_vec_min();
    test__st_vec_max();
    test__st_vec_norm();
    test__st_vec_scale();
    test__st_vec_equal();

    printf("\n");
    return 0;
}
