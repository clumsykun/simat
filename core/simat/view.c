#include <stdio.h>
#include <string.h>
#include <time.h>
#include "view.h"


double st_view_min(st_view *view)
{
    double min = st_view_access(view, 0);

    for (size_t i = 0; i < view->len; i++)
        min = (min <= st_view_access(view, i) ? min : st_view_access(view, i));

    return min;
}

double st_view_max(st_view *view)
{
    double max = st_view_access(view, 0);

    for (size_t i = 0; i < view->len; i++)
        max = (max >= st_view_access(view, i) ? max : st_view_access(view, i));

    return max;
}

void st_view_scale(st_view *view, double min, double max)
{
    double v_min = st_view_min(view);
    double scale = st_view_max(view) - v_min;
    double target_scale = max - min;
    double scaled;

    for (size_t i = 0; i < view->len; i++) {
        scaled = min + (st_view_access(view, i) - v_min) * target_scale / scale;
        st_view_assign(view, i, scaled);
    }
}

// void view_reverse(View *view)
// {
//     for (size_t i = 0; i < (view->len) / 2; i++) {
//         __swap_double(idx(view, i), idx(view, view->len-i-1));
//     }
// }

// unsigned int _partition_double_p(double **head, unsigned int len)
// {
//     double pivot = *head[len - 1];
//     int candidate = -1;

//     for (int i = 0; i <= len - 1; i++) {
//         if (*head[i] < pivot) {

//             candidate++;
//             __swap_double_p(&head[candidate], &head[i]);
//         }
//     }
//     __swap_double_p(&head[candidate + 1], &head[len - 1]);
//     return (unsigned int)(candidate + 1);
// }

// void _quick_sort_double_p(double **head, unsigned int len)
// {
//     if (len > 1) {
//         /* [head, head + len] --> [head, head + pi], [head + pi + 1, head + len] */
//         unsigned int pi = _partition_double_p(head, len);
//         _quick_sort_double_p(head, pi);
//         _quick_sort_double_p(head + pi + 1, len - pi - 1);
//     }
// }

// void view_sort(View *view, enum order order)
// {
//     _quick_sort_double_p(view->head, view->len);
//     if (order == descend) {
//         view_reverse(view);
//     }
// }
