#include <string.h>
#include <stdio.h>


int swap_intp(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return 0;
}
