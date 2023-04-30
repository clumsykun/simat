#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "tools.h"
#include "types.h"


Array *create_array(unsigned int len)
{
    Array *arr = malloc( sizeof(Array) );
    arr->len = len;
    arr->head = malloc( len * sizeof(double) );
    return arr;
}

/**
 * @idx: the index of array which you want locate
 */
void loc_array(Array *arr, Matrix *mat, unsigned int idx)
{
    arr->len = mat->len;
    arr->head = &(mat->head[idx * mat->len]);
}


void free_array(Array *arr)
{
    _std_free(arr->head);
    _std_free(arr);
}

double array_max(Array *arr)
{
    double max = *(arr->head);

    for (unsigned int i=0; i < arr->len; i++) {
        if (loc(arr, i) > max) {
            max = loc(arr, i);
        }
    }

    return max;
}

double array_min(Array *arr)
{
    double min = *(arr->head);

    for (unsigned int i=0; i < arr->len; i++) {
        if (min > loc(arr, i)) {
            min = loc(arr, i);
        }
    }

    return min;
}

/* scale the array to make sure that its max value and min value match param max and min. */
void array_scale(Array *arr, double min, double max)
{
    double arr_min = array_min(arr);
    double scale = array_max(arr) - arr_min;
    double target_scale = max - min;

    for (unsigned int i=0; i < arr->len; i++) {
        loc(arr, i) = min + (loc(arr, i) - arr_min) * target_scale / scale;
    }
}


/* set random double value to array. */
void array_set_rand(Array *arr)
{
    srand(time(NULL));
    for (unsigned int i = 0; i < arr->len; i++) {
        loc(arr, i) = rand() + ( (double) rand() / RAND_MAX );
    }
}


/** 
 * choosing the last value as pivot
 * @head: address of the first number of the array
 * @len: length of the array
 * @candidate: the candidate position of pivot
 */
unsigned int _partition_double(double *head, unsigned int len)
{
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


void array_sort(Array *arr)
{
    _quick_sort_double(arr->head, arr->len);
}
