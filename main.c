#include "include/dev.h"


int debug() {

    // double data[] = {1,2,3,4,5};
    // double out = stats_min(data, 7);
    // printf("%f\n", out);
    // stats_normalize_by_stats(data, 5);

    unsigned int len = 5;
    Array *arr = create_array(len);
    array_set_rand(arr);

    for (unsigned int i = 0; i < len; i++)
        printf("arr[%d]: %f\n", i, *(arr->head+i));

    double max = array_max(arr);
    double min = array_min(arr);
    double mean = stats_mean(arr);
    double var = stats_var(arr, 0);
    double std = stats_std(arr, 0);

    array_normalize(arr);

    mean = stats_mean(arr);
    var = stats_var(arr, 0);
    std = stats_std(arr, 0);
    max = array_max(arr);
    min = array_min(arr);

    array_scale(arr, 0, 4);

    mean = stats_mean(arr);
    var = stats_var(arr, 0);
    std = stats_std(arr, 0);
    max = array_max(arr);
    min = array_min(arr);

    free_array(arr);
    printf("arr: %s\n", *arr);

    return 0;
}


int main() {

    debug();
    return 0;

}
