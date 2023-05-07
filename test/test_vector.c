#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "basic.h"
#include "vector.h"

int main()
{
    size_t len = 10;
    double min = -314.15;
    double max = 314.15;
    srand(time(NULL));

    st_vector *vec_bool = st_new_bool_vector(len);
    st_vector *vec_pixel = st_new_pixel_vector(len);
    st_vector *vec_int = st_new_int_vector(len);
    st_vector *vec_double = st_new_double_vector(len);

    st_vec_rand(vec_bool);
    st_vec_rand(vec_pixel);
    st_vec_rand(vec_int);
    st_vec_rand(vec_double);

    st_vec_display(vec_bool);
    st_vec_display(vec_pixel);
    st_vec_display(vec_int);
    st_vec_display(vec_double);

    st_vec_sort(vec_bool);
    st_vec_display(vec_bool);
    st_vec_sort(vec_pixel);
    st_vec_display(vec_pixel);
    printf("max is:%d\n", st_vec_max(vec_pixel));;
    st_vec_sort(vec_int);
    st_vec_display(vec_int);
    printf("max is:%d\n", st_vec_max(vec_int));
    st_vec_sort(vec_double);
    st_vec_display(vec_double);
    printf("max is:%f\n", st_vec_max(vec_double));

    st_vec_scale(vec_bool, 0, 100);
    st_vec_scale(vec_pixel, 0, 100);
    st_vec_scale(vec_int, 0, 100);
    st_vec_scale(vec_double, 0, 100);

    st_vec_display(vec_bool);
    st_vec_display(vec_pixel);
    st_vec_display(vec_int);
    st_vec_display(vec_double);

    st_vec_reverse(vec_bool);
    st_vec_reverse(vec_pixel);
    st_vec_reverse(vec_int);
    st_vec_reverse(vec_double);

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
