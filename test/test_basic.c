#include "test.h"
#include <stdbool.h>
#include <stdlib.h>
#include <immintrin.h>

int main()
{
    // printf("%d\n", sizeof(int));
    test__vector();
    test__matrix();
    return 0;
}
