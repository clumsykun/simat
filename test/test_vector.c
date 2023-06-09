#include "test.h"

/**
 * [3.141592653589793, 2.718281828459045, 0.577215664901532, 1.414213562373095, 1.618033988749894]
 */
st_vector *
test_d_vec_1(void)
{
    st_vector *vec = st_new_vector(5);
    st_d64 arr[5] = {
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
    st_d64 arr[5] = {
        6.67428,
        9.10938215,
        6.62606896,
        5.2917720859,
        1.602176487
    };

    memcpy(vec->data->head, arr, sizeof(arr));
    return vec;
}

st_vector *
test_i_vec_1(void)
{
    st_vector *vec = st_new_int_vector(1000);
    for (size_t i = 0; i < 1000; i++) {
        st_vec_assign(vec, i, i);
    }

    return vec;
}

st_vector *
test_u_vec_1(void)
{
    st_vector *vec = st_new_pixel_vector(1000);
    for (size_t i = 0; i < 1000; i++) {
        st_vec_assign(vec, i, i%256);
    }

    return vec;
}

st_vector *
test_b_vec_1(void)
{
    st_vector *vec = st_new_bool_vector(1000);
    for (size_t i = 0; i < 1000; i++) {
        st_vec_assign(vec, i, i%2);
    }

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
    st_vector *iv = st_vec_copy_cast(dv, st_dtype_i32);

    rp->value += !equal(st_vec_min(dv), 0.577215664901532);
    rp->value += !equal(st_vec_min(iv), 0);

    return rp;
}

result *
test__st_vec_max(result *rp)
{
    rp->name = "st_vec_max";

    st_vector *dv = test_d_vec_1();
    st_vector *iv = st_vec_copy_cast(iv, st_dtype_i32);

    rp->value += !equal(st_vec_max(dv), 3.141592653589793);
    rp->value += !equal(st_vec_max(iv), 3);

    return rp;
}

result *
test__st_vec_norm(result *rp)
{
    rp->name = "st_vec_norm";

    st_vector *dv = test_d_vec_1();
    st_vector *iv = st_vec_copy_cast(dv, st_dtype_i32);

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
test__st_vec_is_equal(result *rp)
{
    rp->name = "st_vec_is_equal";

    st_vector *vec1 = st_new_vector(1000);
    st_vector *vec2 = st_vec_copy(vec1);

    rp->value = !st_vec_is_equal(vec1, vec2);
    return rp;
}

result *
test__st_vec_copy(result *rp)
{
    rp->name = "st_vec_copy";

    st_vector *vec1 = test_d_vec_1();
    st_vector *vec2 = test_d_vec_2();

    st_vector *cp_vec1 = st_vec_copy(vec1);
    st_vector *cp_vec2 = st_vec_copy(vec2);

    rp->value += !st_vec_is_equal(vec1, cp_vec1);
    rp->value += !st_vec_is_equal(vec2, cp_vec2);

    vec1 = test_i_vec_1();
    cp_vec1 = st_vec_copy(vec1);

    rp->value += !st_vec_is_equal(vec1, cp_vec1);
    rp->value += !st_vec_is_equal(vec2, cp_vec2);

    vec1 = test_u_vec_1();
    cp_vec1 = st_vec_copy(vec1);

    rp->value += !st_vec_is_equal(vec1, cp_vec1);
    rp->value += !st_vec_is_equal(vec2, cp_vec2);

    vec1 = test_b_vec_1();
    cp_vec1 = st_vec_copy(vec1);

    rp->value += !st_vec_is_equal(vec1, cp_vec1);
    rp->value += !st_vec_is_equal(vec2, cp_vec2);


    return rp;
}

result *
test__st_vec_add(result *rp)
{
    rp->name = "st_vec_add";

    st_vector *vec1 = test_d_vec_1();
    st_vector *vec2 = test_d_vec_2();
    st_vector *ret = st_vec_add(vec1, vec2);

    rp->value += !equal(st_vec_access(ret, 0), 9.815872653589793);
    rp->value += !equal(st_vec_access(ret, 1), 11.827663978459045);
    rp->value += !equal(st_vec_access(ret, 2), 7.203284624901531);
    rp->value += !equal(st_vec_access(ret, 3), 6.705985648273095);
    rp->value += !equal(st_vec_access(ret, 4), 3.220210475749894);

    vec1 = test_i_vec_1();
    vec2 = test_i_vec_1();
    ret = st_vec_add(vec1, vec2);

    rp->value += !equal(st_vec_access(ret, 0), 0);
    rp->value += !equal(st_vec_access(ret, 1), 2);
    rp->value += !equal(st_vec_access(ret, 200), 400);
    rp->value += !equal(st_vec_access(ret, 144), 288);
    rp->value += !equal(st_vec_access(ret, 500), 1000);

    vec1 = test_u_vec_1();
    vec2 = test_u_vec_1();

    ret = st_vec_add(vec1, vec2);

    rp->value += !equal(st_vec_access(ret, 0), 0);
    rp->value += !equal(st_vec_access(ret, 1), 2);
    rp->value += !equal(st_vec_access(ret, 2), 4);
    rp->value += !equal(st_vec_access(ret, 100), 200);
    rp->value += !equal(st_vec_access(ret, 200), 144);

    vec1 = test_b_vec_1();
    vec2 = test_b_vec_1();
    ret = st_vec_add(vec1, vec2);

    rp->value += !equal(st_vec_access(ret, 0), 0);
    rp->value += !equal(st_vec_access(ret, 1), 1);
    rp->value += !equal(st_vec_access(ret, 2), 0);
    rp->value += !equal(st_vec_access(ret, 100), 0);
    rp->value += !equal(st_vec_access(ret, 200), 0);
    return rp;
}

result *
test__st_vec_mul(result *rp)
{
    rp->name = "st_vec_mul";

    st_vector *vec1 = test_d_vec_1();
    st_vector *vec2 = test_d_vec_2();
    st_vector *ret = st_vec_mul(vec1, vec2);

    rp->value += !equal(st_vec_access(ret, 0), 20.967869016001284);
    rp->value += !equal(st_vec_access(ret, 1), 24.76186796683419);
    rp->value += !equal(st_vec_access(ret, 2), 3.8246708004298022);
    rp->value += !equal(st_vec_access(ret, 3), 7.483695852867142);
    rp->value += !equal(st_vec_access(ret, 4), 2.592376011941903);

    vec1 = test_i_vec_1();
    vec2 = test_i_vec_1();
    ret = st_vec_mul(vec1, vec2);

    rp->value += !equal(st_vec_access(ret, 0), 0);
    rp->value += !equal(st_vec_access(ret, 1), 1);
    rp->value += !equal(st_vec_access(ret, 2), 4);
    rp->value += !equal(st_vec_access(ret, 3), 9);
    rp->value += !equal(st_vec_access(ret, 4), 16);

    vec1 = test_u_vec_1();
    vec2 = test_u_vec_1();
    ret = st_vec_mul(vec1, vec2);

    rp->value += !equal(st_vec_access(ret, 0), 0);
    rp->value += !equal(st_vec_access(ret, 1), 1);
    rp->value += !equal(st_vec_access(ret, 2), 4);
    rp->value += !equal(st_vec_access(ret, 10), 100);
    rp->value += !equal(st_vec_access(ret, 12), 144);

    return rp;
}

result *
test__st_vec_dot(result *rp)
{
    rp->name = "st_vec_dot";

    st_vector *vec1 = test_d_vec_1();
    st_vector *vec2 = test_d_vec_2();
    st_d64 re = st_vec_dot(vec1, vec2);

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

st_i32
test__vector()
{
    printf("unit test of vector start:\n");
    st_vector *vec = test_d_vec_1();
    call_test(test__st_vec_is_equal);
    call_test(test__st_vec_copy);
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
