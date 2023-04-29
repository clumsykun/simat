#define loc(arr, i) arr->head[i]


/**
 * @head: ptr of the first number of the array
 * @len: length of this array
 */
typedef struct _Array
{
    double *head;
    unsigned int len;
} Array;


/**
 * matrix is basically an ordered collection of same sized arrays
 * @head: ptr of the first array of this matrix
 * @len: length of arrays
 * @num: number of arrays
 */
typedef struct _Matrix
{
    double *head;
    unsigned int len;
    unsigned int num;
} Matrix;


Array *create_array(unsigned int len);
Matrix *create_matrix(unsigned int len, unsigned int num);

void free_array(Array *arr);
void loc_array(Array *arr, Matrix *mat, unsigned int idx);
void matrix_display(Matrix *mat);
void array_set_rand(Array *arr);

double array_max(Array *arr);
double array_min(Array *arr);

double stats_mean(Array *arr);
double stats_var(Array *arr, unsigned int freedom);
double stats_std(Array *arr, unsigned int freedom);

void array_normalize(Array *arr);
void array_scale(Array *arr, double min, double max);
void array_sort(Array *arr);
