#ifndef CORE_VIEW_H
#define CORE_VIEW_H
#include "st_c_elemental.h"

st_d64 st_view_max(st_view *view);
st_d64 st_view_min(st_view *view);
st_d64 st_view_norm(st_view *view);
void   st_view_scale(st_view *view, st_d64 min, st_d64 max);

st_d64 st_view_dot(st_view *a, st_view *b);

#endif /* CORE_VIEW_H */
