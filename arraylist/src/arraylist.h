#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void(*FreeFunc)(void*);

typedef int(*CmpFunc)(const void*, const void*);

typedef void(*PrintFunc)(const void*);

typedef struct {
    size_t data_size;
    size_t size;
    size_t capacity;
    FreeFunc free_func;
    void*  buffer_ptr;
} ArrayList;

/*
 * Construction.
 */

ArrayList* arraylist_create(size_t data_size, FreeFunc);

/*
 * Destruction.
 */

void arraylist_free(ArrayList* al);

/*
 * Field Accessing.
 */

static inline size_t arraylist_data_size(const ArrayList* al)
{
    return al->data_size;
}

static inline size_t arraylist_size(const ArrayList* al)
{
    return al->size;
}

static inline size_t arraylist_capacity(const ArrayList* al)
{
    return al->capacity;
}

// TODO add buffer_ptr access (for qsort, lsearch, e.c.).

/*
 * State.
 */

static inline bool arraylist_is_empty(const ArrayList* al)
{
    return al->size == 0;
}

static inline bool arraylist_is_full(const ArrayList* al)
{
    return al->size == al->capacity;
}

bool arraylist_is_sorted(const ArrayList* al, CmpFunc);


/*
 * Indexing.
 */

void* arraylist_get(const ArrayList* al, size_t pos);

void arraylist_set(ArrayList* al, size_t pos, const void* data_ptr);


/*
 * Concatenation.
 */

ArrayList* arraylist_concat(ArrayList* dest, const ArrayList* src);

/*
 * Equality.
 */

bool arraylist_equals(const ArrayList* al1, const ArrayList* al2, CmpFunc);

/*
 * Insertion.
 */

void arraylist_push_back(ArrayList* al, const void* data_ptr);

void arraylist_insert(ArrayList* al, size_t pos, const void* data_ptr);

/*
 * Removal.
 */

void* arraylist_pop_back(ArrayList* al);

void arraylist_erase(ArrayList* al, size_t pos);

/*
 * Resize.
 */

ArrayList* arraylist_resize(ArrayList* al, size_t new_size);

ArrayList* arraylist_shrink_to_fit(ArrayList* al);

ArrayList* arraylist_clear(ArrayList* al);

/*
 * Reversion.
 */

ArrayList* arraylist_reverse(ArrayList* al);

/*
 * Printing.
 */

void arraylist_print(const ArrayList* al, PrintFunc);

void arraylist_info(const ArrayList* al);

#ifdef __cplusplus
}
#endif

#endif /* ARRAY_LIST_H */
