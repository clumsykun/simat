#include "include/dev.h"


int debug() {

    // char str1[] = "string 1\n";
    // char str2[] = "string 2\n";
    // char *p1 = &str1[0];
    // char *p2 = &str2[0];

    int a = 12;
    int b = 14;

    swap_intp(&a, &b);

    printf("value of a is %d.\n", a);
    printf("value of b is %d.\n", b);

    return 0;
}


int main() {

    debug();
    return 0;

}
