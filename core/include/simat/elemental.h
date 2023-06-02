#ifndef CORE_ELEMENTAL_H
#define CORE_ELEMENTAL_H

#include "dtypes.h"

/* =================================================================================================
 * elemental function
 */
typedef double (*fp_elem)(double, void **);

double st_vec_elemental(st_vector *vec, fp_elem fp, void *argv[]);
double st_mat_elemental(st_vector *mat, fp_elem fp, void *argv[]);
double st_view_elemental(st_view *view, fp_elem fp, void *argv[]);

void st_vec_abs(st_vector *vec);

#endif /* CORE_ELEMENTAL_H */