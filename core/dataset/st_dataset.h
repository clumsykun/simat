#ifndef CORE_DATASET_H
#define CORE_DATASET_H

#include "simat.h"

typedef struct __st_dataset
{
    st_matrix *X;
    st_vector *Y;
    st_view *labels;
} st_dataset;

st_dataset *__st_load_iris(void);

#endif /* CORE_DATASET_H */
