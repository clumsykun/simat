#include "distance.h"

/**
 * 
 */
double st_dist_cos_vv(st_vector *v1, st_vector *v2)
{
    return st_vec_dot(v1,v2)/(st_vec_norm(v1)*st_vec_norm(v2));;
}
