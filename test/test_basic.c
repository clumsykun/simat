#include "test.h"

int main()
{

    double x = -4;
    st_pixel c = __st_cast_pixel(x);
    test__vector();
    test__matrix();
    return 0;
}
