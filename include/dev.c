#include <string.h>
#include <stdio.h>
#include <math.h>


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


double stats_mean(double *arr, unsigned int len) {

    double sum = 0;
    double mean;

    for (unsigned int i = 0; i < len; i++) {
        sum += *(arr+i);
    }

    mean = sum / (double) len;
    return mean;
}


double stats_var(double *arr, unsigned int len, unsigned int freedom) {

    double mean = stats_mean(arr, len);
    double sum_sq_diff = 0;
    double variance;

    for (unsigned int i = 0; i < len; i++) {
        sum_sq_diff += ( *(arr+i)-mean ) * ( *(arr+i)-mean );
    }

    variance = sum_sq_diff / (double) (len-freedom);
    return variance;
}


double stats_std(double *arr, unsigned int len, unsigned int freedom) {

    double std = sqrt(stats_var(arr, len, freedom));
    return std;
}
