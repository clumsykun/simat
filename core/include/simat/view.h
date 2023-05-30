#ifndef CORE_VIEW_H
#define CORE_VIEW_H
#include "dtypes.h"

double st_view_max(st_view *view);
double st_view_min(st_view *view);
double st_view_norm(st_view *view);
void   st_view_scale(st_view *view, double min, double max);

double st_view_dot(st_view *a, st_view *b);

#endif /* CORE_VIEW_H */
