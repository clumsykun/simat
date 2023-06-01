#ifndef CORE_DS_H
#define CORE_DS_H

#include <stdbool.h>

#define st_sha_vector "3ff3d90423dc062ed477b765bdf9e8f39ac3ff5298c10b270b31fc71bd10565e"
#define st_sha_matrix "6e00cd562cc2d88e238dfb81d9439de7ec843ee9d0c9879d549cb1436786f975"
#define st_sha_view   "d60736f872c6b6d0cdeddd69b30c6df0d492c0756f07b13b47b4fb2c23b751b3"

typedef void (*free_fp)(void *);
typedef void (*status_fp)(void *);

void __st_ds_add(void *target, free_fp ffp, status_fp sfp, bool *temp);
void st_ds_clear_all(void);
void st_ds_clear_temp(void);
void st_ds_display(void);
bool st_is_invalid(const void *target);
int  st_free(const void *target);

#endif /* CORE_DS_H */
