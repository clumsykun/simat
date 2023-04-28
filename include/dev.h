#include "dev.c"


int swap_intp(int *a, int *b);
int swap_charp(char **a, char **b);

Array *create_array(unsigned int len);

double stats_mean(double *arr, unsigned int len);
double stats_max(double *arr, unsigned int len);
double stats_min(double *arr, unsigned int len);
double stats_var(double *arr, unsigned int len, unsigned int freedom);
double stats_std(double *arr, unsigned int len, unsigned int freedom);
