#include <immintrin.h>
#include "test.h"


st_i32 main()
{
    __st_is_debug = true;
    test__vector();
    test__matrix();
    test__distance();
    test__stats();
    return 0;
}
