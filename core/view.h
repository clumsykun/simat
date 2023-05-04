#ifndef CORE_VIEW_H
#define CORE_VIEW_H
#include "dtypes.h"

View *create_view();
void free_view(View *view);

double view_max(View *view);
double view_min(View *view);

void view_display(View *view);
void view_set_rand(View *view);
void view_scale(View *view, double min, double max);
void view_reverse(View *view);
void view_sort(View *view, enum order order);

#endif
