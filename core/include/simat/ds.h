#ifndef CORE_DS_H
#define CORE_DS_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef void (*free_fp)(void *);
typedef void (*status_fp)(void *);

void __st_ds_add(void *target, free_fp ffp, status_fp sfp, bool *temp);
void st_ds_clear_all(void);
void st_ds_clear_temp(void);
void st_ds_display(void);
bool st_is_invalid(const void *target);


#endif /* CORE_DS_H */
