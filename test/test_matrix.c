#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "basic.h"
#include "dtypes.h"
#include "vector.h"

int main()
{
    size_t nrow = 10;
    size_t ncol = 5;
    st_matrix *mat = st_new_matrix(nrow, ncol);

    void *p;
    double v = 3.14;
    for __st_iter_data(p, mat->data) {
        __st_assign_p(p, v, __st_double);
        v++;
    }

    st_mat_display(mat);

    for (size_t i = 0; i < mat->ncol; i++) {
        st_vec_display(st_mat_access_col(mat, i));
    }
    

    return 0;
}
