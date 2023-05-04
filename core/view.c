#include <stdio.h>
#include <string.h>
#include <time.h>
#include "view.h"
#include "tools.h"

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
    __std_free(view->head);  /* still need to free this ptr */
    __std_free(view);
}

void matrix_view_col(View *view, Matrix *mat, unsigned int idx)
{
    if (view->len != mat->nrow) {
        view->len = mat->nrow;
        view->head = (double **) realloc(view->head, view->len * sizeof(double *));
    }

    for (size_t i = 0; i < view->len; i++) {
        view->head[i] = &mat->head[idx*mat->nrow + i];
    }
}

void matrix_view_row(View *view, Matrix *mat, unsigned int idx)
{
    if (view->len != mat->ncol) {
        view->len = mat->ncol;
        view->head = (double **) realloc(view->head, view->len * sizeof(double *));
    }

    double(*head)[mat->nrow] = (double(*)[mat->nrow])mat->head;
    for (size_t i = 0; i < view->len; i ++) {
        view->head[i] = &head[i][idx];
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

void view_set_rand(View *view)
{
    srand(time(NULL));
    for (size_t i = 0; i < view->len; i ++) {
        *idx(view, i) = rand() + ((double)rand() / RAND_MAX);
    }
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

void view_scale(View *view, double min, double max)
{
    double v_min = view_min(view);
    double scale = view_max(view) - v_min;
    double target_scale = max - min;

    for (size_t i = 0; i < view->len; i++) {
        *idx(view, i) = min + (*idx(view, i) - v_min) * target_scale / scale;
    }
}

void view_reverse(View *view)
{
    for (size_t i = 0; i < (view->len) / 2; i++) {
        __swap_double(idx(view, i), idx(view, view->len-i-1));
    }
}

unsigned int _partition_double_p(double **head, unsigned int len)
{
    double pivot = *head[len - 1];
    int candidate = -1;

    for (int i = 0; i <= len - 1; i++) {
        if (*head[i] < pivot) {

            candidate++;
            __swap_double_p(&head[candidate], &head[i]);
        }
    }
    __swap_double_p(&head[candidate + 1], &head[len - 1]);
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
