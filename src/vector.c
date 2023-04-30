#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "tools.h"
#include "types.h"

Vector *create_vector(unsigned int len)
{
    Vector *vec = malloc( sizeof(Vector) );
    vec->len = len;
    vec->head = malloc( len * sizeof(double) );
    vec->label = NULL;
    return vec;
}

void free_vector(Vector *vec)
{
    vec->len = 0;
    vec->label = NULL;
    _std_free(vec->head);
    _std_free(vec);
}

void vector_display(Vector *vec)
{
    printf("%s\n", vec->label);
    for (size_t i = 0; i < vec->len; i++) {
        printf("%.2f\n", loc(vec,i));
    }
}

/* set random double value to vector. */
void vector_set_rand(Vector *vec)
{
    srand(time(NULL));
    for (unsigned int i = 0; i < vec->len; i++) {
        loc(vec, i) = rand() + ( (double) rand() / RAND_MAX );
    }
}

/**
 * @idx: the index of array which you want locate
 */
// void loc_array(Vector *vec, Matrix *mat, unsigned int idx)
// {
//     vec->len = mat->len;
//     vec->head = &(mat->head[idx * mat->len]);
// }

// double array_max(Vector *vec)
// {
//     double max = *(vec->head);

//     for (unsigned int i=0; i < vec->len; i++) {
//         if (loc(vec, i) > max) {
//             max = loc(vec, i);
//         }
//     }

//     return max;
// }

// double array_min(Vector *vec)
// {
//     double min = *(vec->head);

//     for (unsigned int i=0; i < vec->len; i++) {
//         if (min > loc(vec, i)) {
//             min = loc(vec, i);
//         }
//     }

//     return min;
// }

// /* scale the array to make sure that its max value and min value match param max and min. */
// void array_scale(Vector *vec, double min, double max)
// {
//     double arr_min = array_min(vec);
//     double scale = array_max(vec) - arr_min;
//     double target_scale = max - min;

//     for (unsigned int i=0; i < vec->len; i++) {
//         loc(vec, i) = min + (loc(vec, i) - arr_min) * target_scale / scale;
//     }
// }

// /** 
//  * choosing the last value as pivot
//  * @head: address of the first number of the array
//  * @len: length of the array
//  * @candidate: the candidate position of pivot
//  */
// unsigned int _partition_double(double *head, unsigned int len)
// {
//     double pivot = head[len-1];
//     int candidate = -1;

//     for (int i=0; i<=len-1; i++) {
//         if (head[i] < pivot) {

//             candidate++;
//             _swap_double(&head[candidate], &head[i]);
//         }
//     }
//     _swap_double(&head[candidate+1], &head[len-1]);
//     return (unsigned int) (candidate + 1);
// }


// void _quick_sort_double(double *head, unsigned int len) {

//     if (len > 1) {
//         /* [head, head + len] --> [head, head + pi], [head + pi + 1, head + len] */
//         unsigned int pi = _partition_double(head, len);
//         _quick_sort_double(head, pi);
//         _quick_sort_double(head+pi+1, len-pi-1);
//     }
// }


// void array_sort(Vector *vec)
// {
//     _quick_sort_double(vec->head, vec->len);
// }
