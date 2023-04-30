#ifndef CORE_STATS_H
#define CORE_STATS_H

double stats_mean(Array *arr);
double stats_var(Array *arr, unsigned int freedom);
double stats_std(Array *arr, unsigned int freedom);
void array_normalize(Array *arr);

#endif /* CORE_STATS_H */
