#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "dtypes.h"
#include "tools.h"

static Vector *__create_vector(enum dtype dtype, unsigned int len)
{
    Vector *vec = malloc(sizeof(Vector));
    char *p = malloc(len * __sizeof(dtype));
    Vector _vec = {
        dtype,
        p,
        p+(len-1) * __sizeof(dtype),
        __sizeof(dtype),
        len,
    };
    memcpy(vec, &_vec, sizeof(Vector));
    return vec;
}

Vector *create_bool_vector(unsigned int len)
{
    return __create_vector(dtype_bool, len);
}

Vector *create_pixel_vector(unsigned int len)
{
    return __create_vector(dtype_pixel, len);
}

Vector *create_int_vector(unsigned int len)
{
    return __create_vector(dtype_int, len);
}

Vector *create_double_vector(unsigned int len)
{
    return __create_vector(dtype_double, len);
}

void free_vector(Vector *vec)
{
    __std_free(vec->head);
    __std_free(vec);
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
    __std_free(view->head);  /* still need to free this ptr */
    __std_free(view);
}

void vector_display(Vector *vec)
{
    size_t i = 0;
    switch (vec->dtype) {

        case dtype_bool: {
            printf("BoolVector([\n");
            char c;
            for (char *p = vec->head; p < vec->bott; p += vec->esize, i++) {
                c = (access(vec->dtype, p) == false ? '-' : '+');
                printf("(%c), ", c);

                if ((i + 1) % 10 == 0)
                    printf("\n");
            }

            printf("(%c)])\n", (access(vec->dtype, vec->bott) == false ? '-' : '+'));
            break;
        }

        case dtype_pixel: {
            printf("PixelVector([\n");
            for (char *p = vec->head; p < vec->bott; p += vec->esize, i++) {
                printf("(%3d), ", (int)access(vec->dtype, p));

                if ((i + 1) % 10 == 0)
                    printf("\n");
            }
            printf("(%3d)])\n", (int)access(vec->dtype, vec->bott));
            break;
        }

        case dtype_int: {
            printf("IntVector([\n");
            for (char *p = vec->head; p < vec->bott; p += vec->esize, i++) {
                printf("%10d, ", (int)access(vec->dtype, p));

                if ((i + 1) % 5 == 0)
                    printf("\n");
            };
            printf("%10d])\n", (int)access(vec->dtype, vec->bott));
            break;
        }

        case dtype_double: {
            printf("DoubleVector([\n");
            for (char *p = vec->head; p < vec->bott; p += vec->esize, i++) {
                printf("%10.2f, ", access(vec->dtype, p));

                if ((i + 1) % 5 == 0)
                    printf("\n");
            }
            printf("%10.2f])\n", access(vec->dtype, vec->bott));
            break;
        }

        default:
            __is_error = true;
    }
    __check();
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

        case dtype_bool: {
            for (char *p = vec->head; p <= vec->bott; p += vec->esize)
                *p = (bool)__rand_int(0, 1);

            break;
        }

        case dtype_pixel: {
            for (char *p = vec->head; p <= vec->bott; p += vec->esize)
                *p = (pixel) __rand_int(0, 255);

            break;
        }

        case dtype_int: {
            for (char *p = vec->head; p <= vec->bott; p += vec->esize)
                dassign(p, __rand_int(-RAND_MAX/2, RAND_MAX/2), vec->dtype);

            break;
        }

        case dtype_double: {
            for (char *p = vec->head; p <= vec->bott; p += vec->esize)
                dassign(p, __rand_double(-100/2, 100/2), vec->dtype);

            break;
        }
        
        default:
            __is_error = true;
    }
    __check();
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
    char *p = vec->head;
    double min = access(vec->dtype, p);
    for (size_t i = 0; i < vec->len; i++, p += vec->esize)
        min = (min <= access(vec->dtype, p) ? min : access(vec->dtype, p));

    __check();
    return min;
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
    char *p = vec->head;
    double max = access(vec->dtype, p);
    for (size_t i = 0; i < vec->len; i++, p += vec->esize)
        max = (max >= access(vec->dtype, p) ? max : access(vec->dtype, p));

    __check();
    return max;
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

    for (char *p = vec->head; p <= vec->bott; p += vec->esize)
        dassign(
            p,
            min + (access(vec->dtype, p) - vec_min) * target_scale / scale,
            vec->dtype
        );

    __check();
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
    char *mid = vec->head + (vec->len/2)*(vec->esize);
    char *r = vec->bott;
    for (char *l = vec->head; l <= mid; l += vec->esize, r -= vec->esize)
        __swap(l, r, vec->esize);
}

void view_reverse(View *view)
{
    for (size_t i = 0; i < (view->len) / 2; i++) {
        __swap_double(idx(view, i), idx(view, view->len-i-1));
    }
}

/**
 * choosing the last value as pivot
 * @head: address of the first number of the vector
 * @len: length of the vector
 * @candidate: the candidate position of pivot
 */
char *__partition(enum dtype dtype, char *start, char *end)
{
    size_t size = __sizeof(dtype);
    double pivot = access(dtype, end);
    char *candidate = start - size;

    for (char *p = start; p < end; p+=size) {
        if (access(dtype, p) < pivot) {

            candidate += size;
            __swap(candidate, p, size);
        }
    }

    candidate += size;
    __swap(candidate, end, size);
    return candidate;
}

static void __quick_sort(enum dtype dtype, char *start, char *end)
{
    if (start < end) {
        /**
         * [p, p + len*size] -->
         * [p, p + pi*size], [p + (pi+1)*size, p+len*size]
         */
        char* p = __partition(dtype, start, end);
        __quick_sort(dtype, start, p-__sizeof(dtype));
        __quick_sort(dtype, p+__sizeof(dtype), end);
    }
}

void vector_sort(Vector *vec, enum order order)
{
    __quick_sort(vec->dtype, vec->head, vec->bott);
    if (order == descend) {
        vector_reverse(vec);
    }
    __check();
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
