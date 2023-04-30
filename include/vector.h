#ifndef VECTOR_H
#define VECTOR_H

Array *create_array(unsigned int len);
void free_array(Array *arr);
double array_max(Array *arr);
double array_min(Array *arr);
void array_scale(Array *arr, double min, double max);
void array_sort(Array *arr);
void array_set_rand(Array *arr);

#endif
