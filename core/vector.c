#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "tools.h"
#include "dtypes.h"

Vector *create_vector(enum dtype dtype, unsigned int len)
{
    size_t size;
    Vector *vec = malloc(sizeof(Vector));
    // Vector _vec;
    switch (dtype) {

        case dtype_bool: {
            Vector _vec = {
                malloc(len * sizeof(bool)),
                dtype_bool,
                len,
            };
            memcpy(vec, &_vec, sizeof(Vector));
            break;
        }

        case dtype_char: {
            Vector _vec = {
                malloc(len * sizeof(char)),
                dtype_char,
                len,
            };
            memcpy(vec, &_vec, sizeof(Vector));
            break;
        }

        case dtype_int: {
            Vector _vec = {
                malloc(len * sizeof(int)),
                dtype_int,
                len,
            };
            memcpy(vec, &_vec, sizeof(Vector));
            break;
        }

        case dtype_double: {
            Vector _vec = {
                malloc(len * sizeof(double)),
                dtype_double,
                len,
            };
            memcpy(vec, &_vec, sizeof(Vector));
            break;
        }

        default:
            dtype_error();
    }

    return vec;
}

void free_vector(Vector *vec)
{
    _std_free(vec->head);
    _std_free(vec);
}

View *create_view()
{
    View *view = malloc(sizeof(View));
    View _view = {
        NULL, /* initialize it to NULL so that realloc() will work properly */
        0
    };
    memcpy(
        view,
        &_view,
        sizeof(View)
    );

    return view;
}

void free_view(View *view)
{
    view->len = 0;
    _std_free(view->head);  /* still need to free this ptr */
    _std_free(view);
}

void vector_display(Vector *vec)
{
    printf("Vector([");
    switch (vec->dtype) {

        case dtype_char: {
                char *p = (char *) vec->head;
                for (size_t i = 0; i < vec->len - 1; i++, p++)
                    printf("%c, ", *p);

                printf("%c])\n", idx(vec, vec->len - 1));
                break;
        }

        case dtype_int: {
            int *p = (int *) vec->head;
            for (size_t i = 0; i < vec->len - 1; i++, p++)
                printf("%d, ", *p);

            printf("%d])\n", idx(vec, vec->len - 1));
            break;
        }

        case dtype_double:{
            double *p = (double *) vec->head;
            for (size_t i = 0; i < vec->len - 1; i++, p++)
                printf("%.4f, ", *p);

            printf("%.4f])\n", idx(vec, vec->len - 1));
            break;
        }

        default:
            dtype_error();
    }
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
    switch (vec->dtype) {

        case dtype_int: {
            int *p = (int *)vec->head;
            for (size_t i = 0; i < vec->len; i++, p++)
                    *p = rand();

            break;
        }

        case dtype_double: {
            double *p = (double *) vec->head;
            for (size_t i = 0; i < vec->len; i++, p++)
                *p = rand() + ((double)rand() / RAND_MAX);

            break;
        }
        
        default:
            dtype_error();
    }
}

void view_set_rand(View *view)
{
    srand(time(NULL));
    for (size_t i = 0; i < view->len; i ++) {
        *idx(view, i) = rand() + ((double)rand() / RAND_MAX);
    }
}

double vector_min(Vector *vec)
{
    double min;
    switch (vec->dtype) {

        case dtype_bool: {
            bool *p = (bool *) vec->head;
            for (size_t i = 0; i < vec->len; i++, p++)
                min = (min <= *p ? min : *p);

            break;
        }

        case dtype_int: {
            int *p = (int *) vec->head;
            for (size_t i = 0; i < vec->len; i++, p++)
                min = (min <= *p ? min : *p);

            break;
        }

        case dtype_double: {
            double *p = (double *) vec->head;
            for (size_t i = 0; i < vec->len; i++, p++)
                min = (min <= *p ? min : *p);

            break;
        }

        default:
            dtype_error();
    }

    return (double) min;
}

double view_min(View *view)
{
    double min = **(view->head);

    for (size_t i = 0; i < view->len; i++) {
        if (min > *idx(view, i)) {
            min = *idx(view, i);
        }
    }
    return min;
}

double vector_max(Vector *vec)
{
    double max;
    switch (vec->dtype) {

        case dtype_bool: {
            bool *p = (bool *) vec->head;
            for (size_t i = 0; i < vec->len; i++, p++)
                max = (max >= *p ? max : *p);

            break;
        }

        case dtype_int: {
            int *p = (int *) vec->head;
            for (size_t i = 0; i < vec->len; i++, p++)
                max = (max >= *p ? max : *p);

            break;
        }

        case dtype_double: {
            double *p = (double *) vec->head;
            for (size_t i = 0; i < vec->len; i++, p++)
                max = (max >= *p ? max : *p);

            break;
        }

        default:
            dtype_error();
    }

    return (double) max;
}

double view_max(View *view)
{
    double max = **(view->head);

    for (size_t i = 0; i < view->len; i++) {
        if (max < *idx(view, i)) {
            max = *idx(view, i);
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

    for (size_t i =0; i < vec->len; i++) {
        idx(vec, i) = min + (idx(vec, i) - vec_min) * target_scale / scale;
    }
}

void view_scale(View *view, double min, double max)
{
    double v_min = view_min(view);
    double scale = view_max(view) - v_min;
    double target_scale = max - min;

    for (size_t i = 0; i < view->len; i++) {
        *idx(view, i) = min + (*idx(view, i) - v_min) * target_scale / scale;
    }
}

void vector_reverse(Vector *vec)
{
    for (size_t i = 0; i < (vec->len) / 2; i++) {
        _swap_double(&idx(vec, i), &idx(vec, vec->len-i-1));
    }
}

void view_reverse(View *view)
{
    for (size_t i = 0; i < (view->len) / 2; i++) {
        _swap_double(idx(view, i), idx(view, view->len-i-1));
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

void vector_sort(Vector *vec, enum order order)
{
    _quick_sort_double(vec->head, vec->len);
    if (order == descend) {
        vector_reverse(vec);
    }
}

unsigned int _partition_double_p(double **head, unsigned int len)
{
    double pivot = *head[len - 1];
    int candidate = -1;

    for (int i = 0; i <= len - 1; i++) {
        if (*head[i] < pivot) {

            candidate++;
            _swap_double_p(&head[candidate], &head[i]);
        }
    }
    _swap_double_p(&head[candidate + 1], &head[len - 1]);
    return (unsigned int)(candidate + 1);
}

void _quick_sort_double_p(double **head, unsigned int len)
{
    if (len > 1) {
        /* [head, head + len] --> [head, head + pi], [head + pi + 1, head + len] */
        unsigned int pi = _partition_double_p(head, len);
        _quick_sort_double_p(head, pi);
        _quick_sort_double_p(head + pi + 1, len - pi - 1);
    }
}

void view_sort(View *view, enum order order)
{
    _quick_sort_double_p(view->head, view->len);
    if (order == descend) {
        view_reverse(view);
    }
}
