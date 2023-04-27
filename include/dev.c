#include <string.h>
#include <stdio.h>


int swap_intp(int *a, int* b) {

    int tmp = *a;
    *a = *b;
    *b = tmp;

    return 0;
}

/*
 * int:
 * a -> *a -> char1
 * b -> *b -> char2
 * out:
 * a -> *a -> char2
 * b -> *b -> char1
*/
int swap_charp(char **a, char **b) {

    char *tmp = *a;  // tmp = *a -> char1
    *a = *b;  // *a = *b -> char2, **a -> char2
    *b = tmp;  // *b = tmp -> char1

    return 0;
}


float stats_mean(float *arr, unsigned int len) {

    float sum = 0;
    float mean;

    for (unsigned int i = 0; i < len; i++) {
        sum += *(arr+i);
    }

    mean = sum / (float) len;
    return mean;
}
