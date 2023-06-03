#include "test.h"

int main()
{
    __st_is_debug = true;
    test__vector();
    test__matrix();
    return 0;
}
