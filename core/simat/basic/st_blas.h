#include <stddef.h>

#define CBLAS_INDEX size_t
#define OPENBLAS_CONST const
#define BLASINT int

/** ================================================================================================
 * level 1 BLAS functions
 * =================================================================================================
 */

double cblas_dnrm2(OPENBLAS_CONST BLASINT N, OPENBLAS_CONST double *X, OPENBLAS_CONST BLASINT incX);
void cblas_dcopy(OPENBLAS_CONST BLASINT n, OPENBLAS_CONST double *x, OPENBLAS_CONST BLASINT incx, double *y, OPENBLAS_CONST BLASINT incy);
void cblas_daxpy(OPENBLAS_CONST BLASINT n, OPENBLAS_CONST double alpha, OPENBLAS_CONST double *x, OPENBLAS_CONST BLASINT incx, double *y, OPENBLAS_CONST BLASINT incy);

/** ================================================================================================
 * OpenBLAS Only
 * =================================================================================================
 */

CBLAS_INDEX cblas_idmax(OPENBLAS_CONST BLASINT n, OPENBLAS_CONST double *x, OPENBLAS_CONST BLASINT incx);
CBLAS_INDEX cblas_idmin(OPENBLAS_CONST BLASINT n, OPENBLAS_CONST double *x, OPENBLAS_CONST BLASINT incx);
double cblas_dsum(OPENBLAS_CONST BLASINT n, OPENBLAS_CONST double *x, OPENBLAS_CONST BLASINT incx);
