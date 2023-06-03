#ifndef CORE_ELEMENTAL_H
#define CORE_ELEMENTAL_H

#include "dtypes.h"

/* =================================================================================================
 * elemental function
 */

typedef void (*fp_elem)(void *elem, __st_dtype dtype, void *argv[]);
typedef void (*fp_pair)(void *l, void *r, __st_dtype dtype, void *argv[]);

double st_vec_elemental(st_vector *vec, fp_elem fp, void *argv[]);
double st_mat_elemental(st_matrix *mat, fp_elem fp, void *argv[]);
double st_view_elemental(st_view *view, fp_elem fp, void *argv[]);

void       st_vec_abs(st_vector *vec);
double     st_vec_min(st_vector *vec);
double     st_vec_max(st_vector *vec);
double     st_vec_sum(st_vector *vec);
double     st_vec_norm(st_vector *vec);
st_vector *st_vec_mul(st_vector *a, st_vector *b);
st_vector *st_vec_add(st_vector *a, st_vector *b);

double st_mat_min(st_matrix *mat);
double st_mat_max(st_matrix *mat);

#endif /* CORE_ELEMENTAL_H */