#include "include/dev.h"


int debug() {

    double data[] = {1,2,3,4,333,6, 112};
    double out = stats_min(data, 7);
    printf("%f\n", out);

    return 0;
}


int main() {

    debug();
    return 0;

}
