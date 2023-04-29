#include <stdio.h>
#include <stdlib.h>
#include "include/types.h"


int debug()
{
    unsigned int len = 10;
    unsigned int num = 5;
    // double (*head)[num] = malloc(len * num * sizeof(double));
    Matrix *mat = create_matrix(len, num);

    double(*head)[mat->num] = (double(*)[mat->num])mat->head;

    int idx = 1;
    for (size_t i = 0; i < len; i++) {
        for (size_t j = 0; j < num; j++) {
            head[i][j] = idx++;
            printf("%.2f    ", head[i][j]);
        }
        printf("\n");
    }

    printf("------------------------------\n");

    matrix_display(mat);

    printf("------------------------------\n");

    Array *arr;
    loc_array(arr, mat, 2);
    for (size_t i = 0; i < arr->len; i++) {
        printf("%.2f    ", loc(arr, i));
    }

    printf("\n");
    return 0;
}


int main()
{
    debug();
    return 0;
}
