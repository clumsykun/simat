#include "dev.c"


int swap_intp(int *a, int *b);
int swap_charp(char **a, char **b);

Array *create_array(unsigned int len);
void free_array(Array *arr);

double array_max(Array *arr);
double array_min(Array *arr);

double stats_mean(Array *arr);
double stats_var(Array *arr, unsigned int freedom);
double stats_std(Array *arr, unsigned int freedom);
