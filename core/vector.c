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
    return vec;
}

void free_vector(Vector *vec)
{
    vec->len = 0;
    _std_free(vec->head);
    _std_free(vec);
}

View *create_view()
{
    View *view = malloc(sizeof(View));
    view->len = 0;
    view->head = NULL; /* initialize it to NULL so that realloc() will work properly */
    return view;
}

void free_view(View *view)
{
    view->len = 0;
    _std_free(view->head);
    _std_free(view);
}

void vector_display(Vector *vec)
{
    printf("Vector([");
    for (size_t i = 0; i < vec->len-1; i++) {
        printf("%.2f, ", idx(vec,i));
    }
    printf("%.2f])\n", idx(vec, vec->len-1));
}

void view_display(View *view)
{
    printf("View([");
    for (size_t i = 0; i < view->len - 1; i++) {
        printf("%.2f, ", *idx(view, i));
    }
    printf("%.2f])\n", *idx(view, view->len - 1));
}

/* set random double value to vector. */
void vector_set_rand(Vector *vec)
{
    srand(time(NULL));
    for (unsigned int i = 0; i < vec->len; i++) {
        idx(vec, i) = rand() + ( (double) rand() / RAND_MAX );
    }
}

double vector_min(Vector *vec)
{
    double min = *(vec->head);

    for (unsigned int i=0; i < vec->len; i++) {
        if (min > idx(vec, i)) {
            min = idx(vec, i);
        }
    }
    return min;
}

double vector_max(Vector *vec)
{
    double max = *(vec->head);

    for (unsigned int i=0; i < vec->len; i++) {
        if (idx(vec, i) > max) {
            max = idx(vec, i);
        }
    }
    return max;
}

/* scale the vector to make sure that its max value and min value match param max and min. */
void vector_scale(Vector *vec, double min, double max)
{
    double vec_min = vector_min(vec);
    double scale = vector_max(vec) - vec_min;
    double target_scale = max - min;

    for (unsigned int i=0; i < vec->len; i++) {
        idx(vec, i) = min + (idx(vec, i) - vec_min) * target_scale / scale;
    }
}

/** 
 * choosing the last value as pivot
 * @head: address of the first number of the vector
 * @len: length of the vector
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

void vector_sort(Vector *vec)
{
    _quick_sort_double(vec->head, vec->len);
}
