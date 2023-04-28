#include "include/dev.h"


int debug() {

    Array *arr = create_array(10);
    array_set_rand(arr);

    for (unsigned int i = 0; i < 10; i++)
        printf("arr[%d]: %f\n", i, arr->head[i]);

    array_sort(arr);
    // // Function call
    // quickSort(arr, 0, N - 1);
    // printf("Sorted array: \n");
    // for (int i = 0; i < N; i++)
    //     printf("%d ", arr[i]);

    for (unsigned int i = 0; i < 10; i++)
        printf("arr[%d]: %f\n", i, arr->head[i]);

    return 0;
}


int main() {

    debug();
    return 0;

}
