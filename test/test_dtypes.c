#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "flags.h"
#include "dtypes.h"

int main()
{
    size_t len = 99;
    double test_value = 3.14;

    st_vector *vec_bool = st_new_bool_vector(len);
    st_vector *vec_pixel = st_new_pixel_vector(len);
    st_vector *vec_int = st_new_int_vector(len);
    st_vector *vec_double = st_new_vector(len);

    st_vec_assign_all(vec_bool, test_value);
    st_vec_assign_all(vec_pixel, test_value);
    st_vec_assign_all(vec_int, test_value);
    st_vec_assign_all(vec_double, test_value);

    assert(st_vec_access(vec_double, 1) == test_value);
    assert(st_vec_access(vec_bool, 1) == (bool)test_value);

    // __st_assign_p(vec_double->data->head, test_value+2, vec_double->data->dtype);
    // assert(st_vec_access(vec_double, 0) == test_value+2);

    st_vec_display(vec_bool);
    st_vec_display(vec_pixel);
    st_vec_display(vec_int);
    st_vec_display(vec_double);

    st_free_vector(vec_bool);
    st_free_vector(vec_pixel);
    st_free_vector(vec_int);
    st_free_vector(vec_double);

    return 0;
}
