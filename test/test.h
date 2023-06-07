#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include "simat.h"
#include "simat_dataset.h"

typedef struct __result
{
    char *name;
    st_bool value;
} result;

typedef result *(*fp)(result *ret);

#define equal(v1, v2) ((v1) == (v2) ? true : false)

void call_test(fp fp);
st_vector *test_d_vec_1(void);
st_vector *test_d_vec_2(void);

st_i32 test__vector(void);
st_i32 test__stats(void);
st_i32 test__distance(void);
st_i32 test__matrix(void);

#endif /* TEST_H */
