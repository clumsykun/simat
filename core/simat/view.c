#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "view.h"


static void check_view_length(st_view *a, st_view *b)
{
    if (a->len != b->len)
        __st_raise_length_error();

    __st_check();
}

double st_view_min(st_view *view)
{
    double min = __st_view_access(view, 0);

    for (size_t i = 0; i < view->len; i++)
        min = (min <= __st_view_access(view, i) ? min : __st_view_access(view, i));

    return min;
}

double st_view_max(st_view *view)
{
    double max = __st_view_access(view, 0);

    for (size_t i = 0; i < view->len; i++)
        max = (max >= __st_view_access(view, i) ? max : __st_view_access(view, i));

    return max;
}

double st_view_norm(st_view *view)
{
    double sum_square = 0;
    for (size_t i = 0; i < view->len; i++) {
        sum_square += __st_view_access(view, i)*__st_view_access(view, i);
    }
    return sqrt(sum_square);
}

void st_view_scale(st_view *view, double min, double max)
{
    double v_min = st_view_min(view);
    double scale = st_view_max(view) - v_min;
    double target_scale = max - min;
    double scaled;

    for (size_t i = 0; i < view->len; i++) {
        scaled = min + (__st_view_access(view, i) - v_min) * target_scale / scale;
        __st_view_assign(view, i, scaled);
    }
}


double st_view_dot(st_view *a, st_view *b)
{
    check_view_length(a, b);

    double ret = 0;
    for (size_t i = 0; i < a->len; i++)
        ret += __st_view_access(a, i) * __st_view_access(b, i);

    __st_check();
    return ret;
}
