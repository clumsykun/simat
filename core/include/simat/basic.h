#ifndef CORE_TOOLS_H
#define CORE_TOOLS_H
#include "dtypes.h"

void st_vec_rand(const st_vector *vec);
void st_vec_sort(st_vector *vec);
void st_vec_reverse(st_vector *vec);

void st_mat_rand(const st_matrix *mat);

void st_view_rand(st_view *view);
void st_view_sort(st_view *view);

#endif /* CORE_TOOLS_H */
