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

struct __node {
    bool *temp;
    void *data;
    free_fp free;
    struct __node * next;
};

struct __node __pool = {
    NULL,
    NULL,
    NULL,
    NULL
};

void *__st_pool_add(void *data, free_fp fp, bool *temp)
{
    struct __node *p = &__pool;
    struct __node *new = (struct __node *)malloc(sizeof(struct __node));

    new->temp = temp;
    new->data = data;
    new->free = fp;
    new->next = NULL;

    while (1) {
        if (p->next != NULL) {

            p = p->next;
            continue;;
        }

        p->next = new;
        break;
    }

    return &__pool;
}

void __st_free_all(void)
{
    struct __node *p = &__pool;
    struct __node *next;

    while (p->next != NULL) {

        next = p->next;

        if (*next->temp) {
            /* clear it */
            next->free(next->data);
            p->next = next->next;
            free(next);
            continue;
        }

        p = p->next;
    }
}
