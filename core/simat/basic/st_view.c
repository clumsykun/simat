#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "st_view.h"


static void
check_view_length(st_view *a, st_view *b)
{
    if (a->len != b->len)
        __st_raise_length_error();
}

st_d64
st_view_min(st_view *view)
{
    st_d64 min = __st_view_access(view, 0);

    for (size_t i = 0; i < view->len; i++)
        min = (min <= __st_view_access(view, i) ? min : __st_view_access(view, i));

    return min;
}

st_d64
st_view_max(st_view *view)
{
    st_d64 max = __st_view_access(view, 0);

    for (size_t i = 0; i < view->len; i++)
        max = (max >= __st_view_access(view, i) ? max : __st_view_access(view, i));

    return max;
}

st_d64
st_view_norm(st_view *view)
{
    st_d64 sum_square = 0;
    for (size_t i = 0; i < view->len; i++) {
        sum_square += __st_view_access(view, i)*__st_view_access(view, i);
    }
    return sqrt(sum_square);
}

void
st_view_scale(st_view *view, st_d64 min, st_d64 max)
{
    st_d64 v_min = st_view_min(view);
    st_d64 scale = st_view_max(view) - v_min;
    st_d64 target_scale = max - min;
    st_d64 scaled;

    for (size_t i = 0; i < view->len; i++) {
        scaled = min + (__st_view_access(view, i) - v_min) * target_scale / scale;
        __st_view_assign(view, i, scaled);
    }
}

st_d64
st_view_dot(st_view *a, st_view *b)
{
    check_view_length(a, b);

    st_d64 ret = 0;
    for (size_t i = 0; i < a->len; i++)
        ret += __st_view_access(a, i) * __st_view_access(b, i);

    return ret;
}
