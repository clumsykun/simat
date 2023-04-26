#include <string.h>
#include <stdio.h>


int swap_intp(int *a, int* b) {

    int tmp = *a;
    *a = *b;
    *b = tmp;

    return 0;
}


int swap_charp(char **a, char **b) {

    char *tmp = *a;
    *a = *b;
    *b = tmp;

    return 0;
}
