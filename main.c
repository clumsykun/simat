#include "include/dev.h"


int debug() {

    float data[] = {1,2,3,4,333,6, 112};
    float out = stats_mean(data, 7);

    return 0;
}


int main() {

    debug();
    return 0;

}
