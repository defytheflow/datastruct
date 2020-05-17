#ifndef VECTOR_H
#define VECTOR_H

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
    void*  buffer_ptr;
    FreeFunc free_func;
} Vector;

/*
 * Construction.
 */

Vector* vector_create(Vector* v, size_t data_size, FreeFunc);

/*
 * Destruction.
 */

void vector_free(Vector* v);

/*
 * Size/Capacity.
 */

static inline size_t vector_size(const Vector* v)
{
    return v->size;
}

static inline size_t vector_capacity(const Vector* v)
{
    return v->capacity;
}

// TODO add buffer_ptr access (for qsort, lsearch, e.c.).

/*
 * Emptiness/Fullness.
 */

static inline bool vector_is_empty(const Vector* v)
{
    return v->size == 0;
}

static inline bool vector_is_full(const Vector* v)
{
    return v->size == v->capacity;
}

bool vector_is_sorted(const Vector* v, CmpFunc);


/*
 * Indexing.
 */

void* vector_get(const Vector* v, size_t pos);

void vector_set(Vector* v, size_t pos, const void* data_ptr);


/*
 * Concatenation.
 */

Vector* vector_concat(Vector* dest, const Vector* src);

/*
 * Equality.
 */

bool vector_equals(const Vector* v1, const Vector* v2, CmpFunc);

/*
 * Insertion.
 */

void vector_push_back(Vector* v, const void* data_ptr);

void vector_insert(Vector* v, size_t pos, const void* data_ptr);

/*
 * Remove.
 */

void* vector_pop_back(Vector* v);

void vector_erase(Vector* v, size_t pos);

/*
 * Resize.
 */

Vector* vector_resize(Vector* v, size_t new_capacity);

Vector* vector_shrink_to_fit(Vector* v);

Vector* vector_clear(Vector* v);

/*
 * Reversion.
 */

Vector* vector_reverse(Vector* v);

/*
 * Printing.
 */

void vector_print(const Vector* v, PrintFunc);

void vector_info(const Vector* v);

#ifdef __cplusplus
}
#endif

#endif /* VECTOR_H */
