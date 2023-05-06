#include <stdlib.h>
#include <string.h>
#include "dtypes.h"


static st_vector *__st_new_vector(__st_dtype dtype, size_t len)
{
    st_vector *vec = malloc(sizeof(st_vector));
    __st_data *data = malloc(sizeof(__st_data));
    void *head = malloc(len * st_byteof(dtype));

    __st_data _data = {
        head,
        head+(len-1)*st_byteof(dtype),
        st_byteof(dtype),
        len,
        dtype,
    };
    
    st_vector _vec = {
        data,
        len,
    };

    memcpy(data, &_data, sizeof(__st_data));
    memcpy(vec, &_vec, sizeof(st_vector));
    return vec;
}

st_vector *st_new_double_vector(size_t len)
{
    return __st_new_vector(__st_double, len);
}

static double __check_assign_value(double value, __st_dtype dtype)
{
    switch (dtype) {

        case __st_bool:
            value = (value == 0 ? 0 : 1);
            break;
        
        case __st_pixel:
            value = (value < 0 ? 0 : (value > 255 ? 255 : (int)value));
            break;

        case __st_int:
            value = (int)value;
            break;

        case __st_double:
            value = (double)value;
            break;

        default:
            __st_raise_dtype_error();
            break;
    }
    return value;
}

void st_vec_assign(st_vector *vec, double value)
{
    void *p;
    value = __check_assign_value(value, vec->data->dtype);

    switch (vec->data->dtype) {
        case __st_bool:
            for __st_data_iter(p, vec->data)
                __st_assign_bool(p, value);

            break;
    
        case __st_pixel:
            for __st_data_iter(p, vec->data)
                __st_assign_pixel(p, value);

            break;

        case __st_int:
            for __st_data_iter(p, vec->data)
                __st_assign_int(p, value);

            break;

        case __st_double:
            for __st_data_iter(p, vec->data)
                __st_assign_double(p, value);

            break;

    default:
        __st_raise_dtype_error();
        break;
    }

    __st_check();
}

