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
