#include "test.h"

int main()
{
    __st_is_debug = true;
    test__vector();
    test__matrix();
    test__distance();
    test__stats();
    return 0;
}
