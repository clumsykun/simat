#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define loc(arr,i) arr->head[i]


/**
 * @head: address of the first number of the array
 * @len: length of the array
 */
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

    Array *arr = malloc(sizeof(Array));
    arr->len = len;
    arr->head = malloc(len*sizeof(double));
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
        if (loc(arr, i) > max) {
            max = loc(arr, i);
        }
    }

    return max;
}


double array_min(Array *arr) {
    double min = *(arr->head);

    for (unsigned int i=0; i < arr->len; i++) {
        if (min > loc(arr, i)) {
            min = loc(arr, i);
        }
    }

    return min;
}


double stats_mean(Array *arr) {

    double sum = 0;

    for (unsigned int i=0; i < arr->len; i++) {
        sum += loc(arr, i);
    }

    return sum / (double) arr->len;
}


double stats_var(Array *arr, unsigned int freedom) {

    double mean = stats_mean(arr);
    double sum_sq_diff = 0;

    for (unsigned int i=0; i < arr->len; i++) {
        sum_sq_diff += ( loc(arr, i)-mean ) * ( loc(arr, i)-mean );
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
        loc(arr, i) = ( loc(arr, i) - mean ) / std;
    }
}


/* Scale the array to make sure that its max value and min value match param max and min. */
void array_scale(Array *arr, double min, double max) {

    double arr_min = array_min(arr);
    double scale = array_max(arr) - arr_min;
    double target_scale = max - min;

    for (unsigned int i=0; i < arr->len; i++) {
        loc(arr, i) = min + (loc(arr, i) - arr_min) * target_scale / scale;
    }
}


/* Set random double value to array. */
void array_set_rand(Array *arr) {

    srand(time(NULL));
    for (unsigned int i = 0; i < arr->len; i++) {
        loc(arr, i) = rand() + ( (double) rand() / RAND_MAX );
    }
}


void _swap_double(double *left, double *right) {

    double tmp = *left;
    *left = *right;
    *right = tmp;
}

/** 
 * choosing the last value as pivot
 * @head: address of the first number of the array
 * @len: length of the array
 * @candidate: the candidate position of pivot
 */
unsigned int _partition_double(double *head, unsigned int len) {

    double pivot = head[len-1];
    int candidate = -1;

    for (int i=0; i<=len-1; i++) {
        if (head[i] < pivot) {

            candidate++;
            _swap_double(&head[candidate], &head[i]);
        }
    }
    _swap_double(&head[candidate+1], &head[len-1]);
    return (unsigned int) (candidate + 1);
}


void _quick_sort_double(double *head, unsigned int len) {

    if (len > 1) {
        /* [head, head + len] --> [head, head + pi], [head + pi + 1, head + len] */
        unsigned int pi = _partition_double(head, len);
        _quick_sort_double(head, pi);
        _quick_sort_double(head+pi+1, len-pi-1);
    }
}


void array_sort(Array *arr) {
    _quick_sort_double(arr->head, arr->len);
}
