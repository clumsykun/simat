#include "include/dev.h"


int debug() {

    // int a = 12;
    // int b = 14;
    // swap_intp(&a, &b);
    // printf("value of a is %d.\n", a);
    // printf("value of b is %d.\n", b);

    char *str1 = "string 1";
    char *str2 = "string 2";
    swap_charp(&str1, &str2);
    printf("str1 is %s, str2 is %s\n", str1, str2);

    return 0;
}


int main() {

    debug();
    return 0;

}
