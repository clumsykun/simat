#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int test_vector()
{
    unsigned int len = 10;
    Vector *vec = create_vector(len);
    vec->label = "vec";

    vector_set_rand(vec);
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
