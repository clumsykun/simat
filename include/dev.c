#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


typedef struct _Array{

    double *head;
    unsigned int len;

} Array;


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



Array *create_array(unsigned int len) {
    Array *arr = (Array *) malloc(sizeof(Array));
    arr->len = len;
    arr->head = (double *) malloc(len*sizeof(double));
    return arr;
}


void free_array(Array *arr) {

    free(arr->head);
    arr->head = NULL;
    free(arr);
    arr = NULL;
}


double array_max(Array *arr) {

    double max = *(arr->head);

    for (unsigned int i=0; i < arr->len; i++) {
        if (*(arr->head+i) > max) {
            max = *(arr->head+i);
        }
    }

    return max;
}


double array_min(Array *arr) {
    double min = *(arr->head);

    for (unsigned int i=0; i < arr->len; i++) {
        if (min > *(arr->head+i)) {
            min = *(arr->head+i);
        }
    }

    return min;
}


double stats_mean(Array *arr) {

    double sum = 0;

    for (unsigned int i=0; i < arr->len; i++) {
        sum += *(arr->head+i);
    }

    return sum / (double) arr->len;
}


double stats_var(Array *arr, unsigned int freedom) {

    double mean = stats_mean(arr);
    double sum_sq_diff = 0;

    for (unsigned int i=0; i < arr->len; i++) {
        sum_sq_diff += ( *(arr->head+i)-mean ) * ( *(arr->head+i)-mean );
    }

    return sum_sq_diff / (double) (arr->len-freedom);
}


double stats_std(Array *arr, unsigned int freedom) {

    return sqrt(stats_var(arr, freedom));
}

/* Scale the array to make sure that its mean equals 0, its standard variance equals 1. */
void array_normalize(Array *arr) {

    double mean = stats_mean(arr);
    double std = stats_std(arr, 0);

    for (unsigned int i=0; i < arr->len; i++) {
        *(arr->head+i) = ( *(arr->head+i) - mean ) / std;
    }
}


// int stats_normalize_by_scale(double *arr, unsigned int len, double min, double max) {

//     double arr_min = stats_min(arr, len);
//     double diff = stats_max(arr, len) - arr_min;
//     double target_diff = max - min;

//     for (unsigned int i=0; i < len; i++) {
//         *(arr+i) = min + (*(arr+i) - arr_min)*target_diff/diff;
//     }

//     return 0;
// }
