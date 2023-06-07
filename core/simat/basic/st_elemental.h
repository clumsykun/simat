#ifndef CORE_ELEMENTAL_H
#define CORE_ELEMENTAL_H

#include "st_dtypes.h"
#include "st_copy.h"

/* =================================================================================================
 * elemental function
 */

// // typedef void (*fp_elem)(void *elem, st_dtype dtype, void *argv[]);
// typedef void (*fp_pair)(void *l, void *r, st_dtype dtype, void *argv[]);

// typedef void (*fp_elem_d)(double *elem, double argv[]);
// typedef void (*fp_elem_i)(int *elem, void *argv[]);
// typedef void (*fp_elem_p)(unsigned char *elem, void *argv[]);
// typedef void (*fp_elem_b)(char *elem, void *argv[]);

// typedef struct __st_elemental
// {
//     fp_elem_d d;
//     fp_elem_i i;
//     fp_elem_p p;
//     fp_elem_b b;
// } st_elemental;

// void st_vec_elemental(st_vector *vec, st_elemental *fp, void *argv[]);
// void st_mat_elemental(st_matrix *mat, st_elemental *elemental, void *argv[]);
// // double st_view_elemental(st_view *view, st_elemental fp, void *argv[]);

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