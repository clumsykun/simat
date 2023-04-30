#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "core/vector.h"

int test_vector()
{
    unsigned int len = 500;
    Vector *vec = create_vector(len);
    vec->label = "vec";

    for (size_t i = 0; i < 500; i ++) {
        idx(vec, i) = 500-i;
    }

    assert(vector_max(vec) == 500);
    assert(vector_min(vec) == 1);

    vector_set_rand(vec);
    assert(vector_max(vec) != 500);
    assert(vector_min(vec) != 1);

    vector_scale(vec, 0, 1);
    assert(vector_max(vec) == 1);
    assert(vector_min(vec) == 0);

    vector_set_rand(vec);
    vector_sort(vec);
    vector_display(vec);
    free_vector(vec);
    return 0;
}


int test_matrix()
{
    unsigned int len = 10;
    unsigned int num = 5;
    // double (*head)[num] = malloc(len * num * sizeof(double));

    int idx = 1;

    printf("------------------------------\n");

    printf("------------------------------\n");
    return 0;
}

int test_stats()
{
    return 0;
}


int main()
{
    test_vector();
    return 0;
}
