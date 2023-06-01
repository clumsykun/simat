#include <stdlib.h>
#include <stdio.h>
#include "ds.h"

/**
 * this linked list implements the the data space.
 * all data of simat should be added to the data space as a member,
 * which is an element of this linked list.
 */
struct __mb {
    bool *temp;
    void *target;
    free_fp free;
    status_fp status;
    struct __mb * next;
};

struct __mb __ds_head = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

void
__st_ds_add(void *target, free_fp ffp, status_fp sfp, bool *temp)
{
    struct __mb *p = &__ds_head;
    struct __mb *new = (struct __mb *)malloc(sizeof(struct __mb));

    new->temp = temp;
    new->target = target;
    new->free = ffp;
    new->status = sfp;
    new->next = NULL;

    while (p->next != NULL) 
        p = p->next;

    p->next = new;
}

/* clear the data space */
static void
__clear_ds(bool only_temp)
{
    struct __mb *p = &__ds_head;
    struct __mb *next = p->next;

    while (next != NULL) {
        
        if (only_temp) {
            if (!*next->temp) {

                /**
                 * here implement the case of delete temporary node only
                 * this node is not temporary, so skip this node
                 */

                p = next;
                next = p->next;
                continue;
            }
        }

        /* clear it */
        p->next = next->next;

        /**
         * every row of matrix is registered as a valid member,
         * but its free function is NULL, you can not free a row of matrix,
         * you should free the whole matrix
         */
        if (next->free != NULL)
            next->free(next->target);

        free(next);
        next = p->next;
    }
}

/* clear all member of the data space */
void
st_ds_clear_all(void)
{
    __clear_ds(false);
}

/* clear temporary member of the data space */
void
st_ds_clear_temp(void)
{
    __clear_ds(true);
}

/* check if the target is a invalid member of data space */
bool
st_is_invalid(const void *target)
{
    struct __mb *p = &__ds_head;
    bool is_invalid = true;

    while (p->next != NULL) {
        if (p->next->target == target)
            is_invalid = false;

        p = p->next;
    }

    return is_invalid;
}

int
st_free(const void *target)
{
    struct __mb *p = &__ds_head;
    while (p->next != NULL) {

        if (p->next->target == target) {
            p->next->free(p->next->target);
            p->next = p->next->next;
            return 0;
        }
        p = p->next;
    }
    return 1;
}

void
st_ds_display(void)
{
    struct __mb *p = &__ds_head;

    if (p->next == NULL) {
        printf("status of simat data space: empty!\n\n");
        return;
    }

    printf("status of simat data space:\n");
    while (p->next != NULL) {
        p = p->next;

        if (p->status != NULL)
            p->status(p->target);
    }
    printf("\n");
}
