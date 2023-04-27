#include "include/dev.h"


int debug() {

    double data[] = {1,2,3,4,5};
    // double out = stats_min(data, 7);
    // printf("%f\n", out);
    stats_normalize_by_stats(data, 5);

    printf("%f, %f\n", stats_mean(data, 5), stats_std(data, 5, 0));

    return 0;
}


int main() {

    debug();
    return 0;

}
