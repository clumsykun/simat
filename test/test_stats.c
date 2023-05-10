#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "basic.h"
#include "vector.h"
#include "stats.h"

int main()
{
    size_t len = 10;
    double min = -314.15;
    double max = 314.15;

    srand(time(NULL));
    st_vector *vec_bool = st_new_bool_vector(len);
    st_vector *vec_pixel = st_new_pixel_vector(len);
    st_vector *vec_int = st_new_int_vector(len);
    st_vector *vec_double = st_new_vector(len);

    st_vec_rand(vec_bool);
    st_vec_rand(vec_pixel);
    st_vec_rand(vec_int);
    st_vec_rand(vec_double);

    st_vec_display(vec_bool);
    st_vec_display(vec_pixel);
    st_vec_display(vec_int);
    st_vec_display(vec_double);

    printf("mean/var of vec_bool: %.2f/%.2f\n", st_vec_mean(vec_bool), st_vec_std(vec_bool, 0));
    printf("mean/var of vec_pixel: %.2f/%.2f\n", st_vec_mean(vec_pixel), st_vec_std(vec_pixel, 0));
    printf("mean/var of vec_int: %.2f/%.2f\n", st_vec_mean(vec_int), st_vec_std(vec_int, 0));
    printf("mean/var of vec_double: %.2f/%.2f\n", st_vec_mean(vec_double), st_vec_std(vec_double, 0));


    st_free_vector(vec_bool);
    st_free_vector(vec_pixel);
    st_free_vector(vec_int);
    st_free_vector(vec_double);

    return 0;
}
