#include "test.h"

/**
 * [3.141592653589793, 2.718281828459045, 0.577215664901532, 1.414213562373095, 1.618033988749894]
 */
st_vector *
test_vec_1(void)
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
st_vector *
test_vec_2(void)
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

void
call_test(fp fp)
{
    result ret = {NULL, 0};
    result *rp = &ret;

    if (fp(rp)->value)
        printf("FAILED --> %s\n", rp->name);
    else
        printf("    OK --> %s\n", rp->name);
}

void
test__st_vec_min(void)
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

result *
test__st_vec_max(result *rp)
{
    rp->name = "st_vec_max";

    st_vector *vec1 = test_vec_1();
    st_vector *vec3 = st_vec_copy_cast(vec1, st_pixel);

    rp->value = !equal(st_vec_max(vec1), 3.141592653589793);
    rp->value = !equal(st_vec_max(vec3), 3);

    return rp;
}

void
test__st_vec_norm(void)
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

void
test__st_vec_scale(void)
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

void
test__st_vec_equal(void)
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

result *
test__st_vec_add(result *rp)
{
    rp->name = "st_vec_add";

    st_vector *vec1 = test_vec_1();
    st_vector *vec2 = test_vec_2();
    st_vector *vec3 = st_vec_add(vec1, vec2);;
    st_vector *ret = st_new_vector(vec1->len);

    __st_vec_assign(ret, 0, 9.815872653589793);
    __st_vec_assign(ret, 1, 11.827663978459045);
    __st_vec_assign(ret, 2, 7.203284624901531);
    __st_vec_assign(ret, 3, 6.705985648273095);
    __st_vec_assign(ret, 4, 3.220210475749894);

    rp->value = !st_vec_equal(vec3, ret);

    return rp;
}

result *
test__st_vec_sub(result *rp)
{
    rp->name = "st_vec_sub";

    st_vector *vec1 = test_vec_1();
    st_vector *vec2 = test_vec_2();
    st_vector *vec3 = st_vec_sub(vec1, vec2);
    st_vector *ret = st_new_vector(vec1->len);

    __st_vec_assign(ret, 0, -3.5326873464102073);
    __st_vec_assign(ret, 1, -6.391100321540955);
    __st_vec_assign(ret, 2, -6.048853295098468);
    __st_vec_assign(ret, 3, -3.877558523526905);
    __st_vec_assign(ret, 4, 0.015857501749894087);

    rp->value = !st_vec_equal(vec3, ret);

    return rp;
}

result *
test__st_vec_mul(result *rp)
{
    rp->name = "st_vec_mul";

    st_vector *vec1 = test_vec_1();
    st_vector *vec2 = test_vec_2();
    st_vector *vec3 = st_vec_mul(vec1, vec2);
    st_vector *ret = st_new_vector(vec1->len);

    __st_vec_assign(ret, 0, 20.967869016001284);
    __st_vec_assign(ret, 1, 24.76186796683419);
    __st_vec_assign(ret, 2, 3.8246708004298022);
    __st_vec_assign(ret, 3, 7.483695852867142);
    __st_vec_assign(ret, 4, 2.592376011941903);

    rp->value = !st_vec_equal(vec3, ret);

    return rp;
}

result *
test__st_vec_div(result *rp)
{
    rp->name = "st_vec_div";

    st_vector *vec1 = test_vec_1();
    st_vector *vec2 = test_vec_2();
    st_vector *vec3 = st_vec_div(vec1, vec2);
    st_vector *ret = st_new_vector(vec1->len);

    __st_vec_assign(ret, 0, 0.47070135708867367);
    __st_vec_assign(ret, 1, 0.2984046320264481);
    __st_vec_assign(ret, 2, 0.08711283694541144);
    __st_vec_assign(ret, 3, 0.2672476326297738);
    __st_vec_assign(ret, 4, 1.0098974750151193);

    rp->value = !st_vec_equal(vec3, ret);

    return rp;
}

result *
test__st_vec_dot(result *rp)
{
    rp->name = "st_vec_dot";

    st_vector *vec1 = test_vec_1();
    st_vector *vec2 = test_vec_2();
    double re = st_vec_dot(vec1, vec2);

    rp->value = !equal(st_precise(st_vec_dot(vec1, vec2), 13), 59.6304796480743);

    return rp;
}

result *
test__st_vec_mul_scalar(result *rp)
{
    rp->name = "st_vec_mul_scalar";

    st_vector *vec1 = test_vec_1();
    st_vector *vec2 = test_vec_1();
    st_vec_mul_scalar(vec1, -1);

    for (size_t i = 0; i < vec1->len; i++) {
        rp->value = !equal(
            st_vec_access(vec1, i),
            -1*st_vec_access(vec2, i)
        );
    }

    return rp;
}

result *
test__st_vec_abs(result *rp)
{
    rp->name = "st_vec_abs";

    st_vector *vec1 = test_vec_1();
    st_vector *vec2 = test_vec_1();

    st_vec_mul_scalar(vec1, -1);
    
    st_vec_abs(vec1);
    st_vec_abs(vec2);

    st_vec_mul_scalar(vec1, -1);
    
    for (size_t i = 0; i < vec1->len; i++) {
        rp->value = !equal(
            st_vec_access(vec1, i),
            -1*st_vec_access(vec2, i)
        );
    }

    return rp;
}

int
test__vector()
{
    printf("unit test of vector start:\n");

    st_vector *vec = test_vec_1();

    test__st_vec_min();
    test__st_vec_norm();
    test__st_vec_scale();
    test__st_vec_equal();

    call_test(test__st_vec_max);
    call_test(test__st_vec_add);
    call_test(test__st_vec_sub);
    call_test(test__st_vec_mul);
    call_test(test__st_vec_div);
    call_test(test__st_vec_dot);
    call_test(test__st_vec_mul_scalar);
    call_test(test__st_vec_abs);

    printf("\n");
    return 0;
}
