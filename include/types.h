#define loc(arr, i) arr->head[i]


/**
 * @head: pointer of the first number of the array
 * @len: length of the array
 */
typedef struct _Array
{
    double *head;
    unsigned int len;
} Array;


Array *create_array(unsigned int len);
void free_array(Array *arr);
void array_set_rand(Array *arr);

double array_max(Array *arr);
double array_min(Array *arr);

double stats_mean(Array *arr);
double stats_var(Array *arr, unsigned int freedom);
double stats_std(Array *arr, unsigned int freedom);

void array_normalize(Array *arr);
void array_scale(Array *arr, double min, double max);
void array_sort(Array *arr);
