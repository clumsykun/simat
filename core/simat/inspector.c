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

/**
 * this code of linked list implements the the data space
 * all data of simat should be added to the data space as a member
 * which is an element of this linked list
 */
struct __mb {
    bool *temp;
    void *target;
    free_fp free;
    struct __mb * next;
};

struct __mb __ds_head = {
    NULL,
    NULL,
    NULL,
    NULL
};

void __st_ds_add(void *target, free_fp fp, bool *temp)
{
    struct __mb *p = &__ds_head;
    struct __mb *new = (struct __mb *)malloc(sizeof(struct __mb));

    new->temp = temp;
    new->target = target;
    new->free = fp;
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
