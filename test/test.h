#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "simat.h"

typedef struct __result
{
    char *name;
    bool value;
} result;

typedef result *(*fp)(result *ret);

#define equal(v1, v2) (v1 == v2 ? true : false)

void call_test(fp fp);
st_vector *test_vec_1(void);
st_vector *test_vec_2(void);
int test__distance(void);
int test__vector(void);

#endif /* TEST_H */
