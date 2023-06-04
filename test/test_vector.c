#include "test.h"

/**
 * [3.141592653589793, 2.718281828459045, 0.577215664901532, 1.414213562373095, 1.618033988749894]
 */
st_vector *
test_d_vec_1(void)
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
test_d_vec_2(void)
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
}

result *
test__st_vec_min(result *rp)
{
    rp->name = "st_vec_min";

    st_vector *dv = test_d_vec_1();
    st_vector *iv = st_vec_copy_cast(dv, st_int);

    rp->value += !equal(st_vec_min(dv), 0.577215664901532);
    rp->value += !equal(st_vec_min(iv), 0);

    return rp;
}

result *
test__st_vec_max(result *rp)
{
    rp->name = "st_vec_max";

    st_vector *dv = test_d_vec_1();
    st_vector *iv = st_vec_copy_cast(iv, st_int);

    rp->value += !equal(st_vec_max(dv), 3.141592653589793);
    rp->value += !equal(st_vec_max(iv), 3);

    return rp;
}

result *
test__st_vec_norm(result *rp)
{
    rp->name = "st_vec_norm";

    st_vector *dv = test_d_vec_1();
    st_vector *iv = st_vec_copy_cast(dv, st_int);

    rp->value += !equal(st_vec_norm(dv), 4.712735130747071);
    rp->value += !equal(st_vec_norm(iv), 3.872983346207417);
    return rp;
}

result *
test__st_vec_scale(result *rp)
{
    rp->name = "st_vec_scale";

    st_vector *vec = test_d_vec_1();
    st_vec_scale(vec, 0, 1);

    rp->value = !equal(st_vec_max(vec), 1);
    rp->value = !equal(st_vec_min(vec), 0);
    return rp;
}

result *
test__st_vec_equal(result *rp)
{
    rp->name = "st_vec_equal";

    st_vector *vec1 = test_d_vec_1();
    st_vector *vec2 = test_d_vec_2();
    st_vector *vec3 = test_d_vec_1();

    rp->value = st_vec_equal(vec1, vec2);
    rp->value = !st_vec_equal(vec1, vec3);
    return rp;
}

result *
test__st_vec_add(result *rp)
{
    rp->name = "st_vec_add";

    st_vector *vec1 = test_d_vec_1();
    st_vector *vec2 = test_d_vec_2();
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
test__st_vec_mul(result *rp)
{
    rp->name = "st_vec_mul";

    st_vector *vec1 = test_d_vec_1();
    st_vector *vec2 = test_d_vec_2();
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
test__st_vec_dot(result *rp)
{
    rp->name = "st_vec_dot";

    st_vector *vec1 = test_d_vec_1();
    st_vector *vec2 = test_d_vec_2();
    double re = st_vec_dot(vec1, vec2);

    rp->value = !equal(st_precise(st_vec_dot(vec1, vec2), 13), 59.6304796480743);

    return rp;
}

result *
test__st_vec_mul_scalar(result *rp)
{
    rp->name = "st_vec_mul_scalar";

    st_vector *vec1 = test_d_vec_1();
    st_vector *vec2 = test_d_vec_1();
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

    st_vector *vec1 = test_d_vec_1();
    st_vector *vec2 = test_d_vec_1();

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
    st_vector *vec = test_d_vec_1();

    call_test(test__st_vec_equal);
    call_test(test__st_vec_norm);
    call_test(test__st_vec_min);
    call_test(test__st_vec_max);
    call_test(test__st_vec_scale);
    call_test(test__st_vec_add);
    call_test(test__st_vec_mul);
    call_test(test__st_vec_dot);
    call_test(test__st_vec_mul_scalar);
    call_test(test__st_vec_abs);

    printf("DONE\n\n");
    return 0;
}
