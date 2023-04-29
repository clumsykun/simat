#include <math.h>
#include "types.h"


double stats_mean(Array *arr)
{
    double sum = 0;

    for (unsigned int i = 0; i < arr->len; i++) {
        sum += loc(arr, i);
    }

    return sum / (double)arr->len;
}


double stats_var(Array *arr, unsigned int freedom)
{
    double mean = stats_mean(arr);
    double sum_sq_diff = 0;

    for (unsigned int i = 0; i < arr->len; i++) {
        sum_sq_diff += (loc(arr, i) - mean) * (loc(arr, i) - mean);
    }

    return sum_sq_diff / (double)(arr->len - freedom);
}


double stats_std(Array *arr, unsigned int freedom)
{
    return sqrt(stats_var(arr, freedom));
}
