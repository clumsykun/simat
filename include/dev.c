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


// double stats_std(double *arr, unsigned int len, unsigned int freedom) {

//     double std = sqrt(stats_var(arr, len, freedom));
//     return std;
// }


// double stats_max(double *arr, unsigned int len) {
//     double max = *arr;

//     for (unsigned int i=0; i < len; i++) {
//         if (*(arr+i) > max) {
//             max = *(arr+i);
//         }
//     }

//     return max;
// }


// double stats_min(double *arr, unsigned int len) {
//     double min = *arr;

//     for (unsigned int i=0; i < len; i++) {
//         if (min > *(arr+i)) {
//             min = *(arr+i);
//         }
//     }

//     return min;
// }


// int stats_normalize_by_stats(double *arr, unsigned int len) {

//     double mean = stats_mean(arr, len);
//     double std = stats_std(arr, len, 0);

//     for (unsigned int i=0; i < len; i++) {
//         *(arr+i) = ( *(arr+i) - mean ) / std;
//     }

//     return 0;
// }


// int stats_normalize_by_scale(double *arr, unsigned int len, double min, double max) {

//     double arr_min = stats_min(arr, len);
//     double diff = stats_max(arr, len) - arr_min;
//     double target_diff = max - min;

//     for (unsigned int i=0; i < len; i++) {
//         *(arr+i) = min + (*(arr+i) - arr_min)*target_diff/diff;
//     }

//     return 0;
// }
