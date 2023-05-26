#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "inspector.h"

bool __st_is_error = false;
bool __st_access_error = false;
bool __st_dtype_error = false;
bool __st_out_range_error = false;
bool __st_length_error = false;
bool __st_invalid_error = false;

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

void __st_ds_add(void *target, free_fp ffp, status_fp sfp, bool *temp)
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
static void __clear_ds(bool only_temp)
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
void st_ds_clear_all(void)
{
    __clear_ds(false);
}

/* clear temporary member of the data space */
void st_ds_clear_temp(void)
{
    __clear_ds(true);
}

/* check if the target is a invalid member of data space */
bool st_is_invalid(const void *target)
{
    struct __mb *p = &__ds_head;
    bool is_invalid = true;

    while (p->next != NULL) {

        p = p->next;
        if (p->target == target)
            is_invalid = false;
    }

    return is_invalid;
}

void st_ds_display(void)
{
    struct __mb *p = &__ds_head;
    while (p->next != NULL) {
        p = p->next;

        if (p->status != NULL)
            p->status(p->target);
    }
    printf("OK\n");
}

/**
 * check and raise error here.
 */

void __st_check_invalid_error(const void *target)
{
    __st_invalid_error = st_is_invalid(target);
    if (__st_invalid_error)
        __st_is_error = true;

    __st_check();
}

double __st_raise_access_error(void)
{
    __st_is_error = true;
    __st_access_error = true;
    return 0;
}

size_t __st_raise_dtype_error(void)
{
    __st_is_error = true;
    __st_dtype_error = true;
    return 0;
}

double __st_raise_out_range_error(void)
{
    __st_is_error = true;
    __st_out_range_error = true;
    return 0;
}

void __st_raise_length_error(void)
{
    __st_is_error = true;
    __st_length_error = true;
}

/**
 * check program is correct or not after any operation
 * probably need some advanced handling
 */
void __st_check__(const char *file, const size_t line)
{

    if (__st_is_error)
    printf("%s:%d: ", file, line);

    if (__st_invalid_error)
        printf("Error: Invalid simat member!\n");

    if (__st_access_error)
        printf("Error: Access failed!\n");

    if (__st_dtype_error)
        printf("Error: Data type not found!\n");

    if (__st_out_range_error)
        printf("Error: Index out of range!\n");

    if (__st_length_error)
        printf("Error: length not match!\n");

    assert(!__st_is_error);
}
