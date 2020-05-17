#include "vector.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GROW_FACTOR    2
#define INIT_CAPACITY  4
#define NOT_FOUND     -1

static void* vector_get_internal(const Vector*, size_t pos);
static void  vector_set_internal(Vector*, size_t pos, const void*);

static Vector* vector_grow_buffer_by(Vector*, size_t n);
static Vector* vector_shrink_buffer_by(Vector*, size_t n);

static void swap(void*, void*, size_t);

/*
 *                                Construction.
 */

Vector* vector_create(Vector* v, size_t data_size, FreeFunc free_func)
{
    v->data_size = data_size;
    v->size = 0;
    v->capacity = INIT_CAPACITY;
    v->free_func = (*free_func);
    v->buffer_ptr = malloc(v->data_size * v->capacity);
    memset(v->buffer_ptr, 0, INIT_CAPACITY);
    assert(v->buffer_ptr);

    return v;
}

/*
 *                                Destruction.
 */

void vector_free(Vector* v)
{
    if (v->free_func) {
        for (size_t i = 0; i < v->size; ++i)
            v->free_func(vector_get_internal(v, i));
    }
    free(v->buffer_ptr);
}

/*
 *                                   State.
 */

bool vector_is_sorted(const Vector* v, CmpFunc cmp_func)
{
    for (size_t i = 0; i < v->size - 1; ++i) {
        if ((*cmp_func)(vector_get_internal(v, i),
                        vector_get_internal(v, i + 1)) > 0)
            return false;
    }
    return true;
}

/*
 *                                  Indexing.
 */

void* vector_get(const Vector* v, size_t pos)
{
    assert(pos < v->size);
    return (char*) v->buffer_ptr + pos * v->data_size;
}

void vector_set(Vector* v, size_t pos, const void* data_ptr)
{
    assert(pos < v->size);
    memcpy((char*) v->buffer_ptr + pos * v->data_size, data_ptr, v->data_size);
}

/*
 *                               Concatenation.
 */

Vector* vector_concat(Vector* dest, const Vector* src)
{
    for (size_t i = 0; i < src->size; ++i)
        vector_push_back(dest, vector_get_internal(src, i));
    return dest;
}

/*
 *                                  Equality.
 */

bool vector_equals(const Vector* v1, const Vector* v2, CmpFunc cmp_func)
{
    if (v1->size != v2->size) return false;

    for (size_t i = 0; i < v1->size; ++i) {
        if ((*cmp_func)(vector_get_internal(v1, i),
                        vector_get_internal(v2, i)))
            return false;
    }
    return true;
}

/*
 *                                 Insertion.
 */

void vector_push_back(Vector* v, const void* data_ptr)
{
    if (vector_is_full(v))
        vector_resize(v, v->capacity * GROW_FACTOR);

    vector_set_internal(v, v->size++, data_ptr);
}

void vector_insert(Vector* v, size_t pos, const void* data_ptr)
{
    assert(pos < v->size);

    if (vector_is_full(v))
        vector_resize(v, v->capacity * GROW_FACTOR);

    for (size_t i = v->size - 1; i >= pos; --i)
        vector_set_internal(v, i + 1, vector_get_internal(v, i));

    vector_set_internal(v, pos, data_ptr);
    ++v->size;
}

/*
 *                                  Removal.
 */

void* vector_pop_back(Vector* v)
{
    assert(!(vector_is_empty(v)));
    return vector_get_internal(v, --v->size);
}

void vector_erase(Vector* v, size_t pos)
{
    assert(pos < v->size);

    for (size_t i = pos; i < v->size - 1; ++i)
        vector_set_internal(v, i, vector_get_internal(v, i + 1));

    --v->size;
}

/*
 *                                   Resize.
 */

Vector* vector_resize(Vector* v, size_t new_capacity)
{
    if (vector_capacity(v) == new_capacity)
        return v;

    return (v->capacity < new_capacity) ?
        vector_grow_buffer_by(v, new_capacity - v->capacity) :
        vector_shrink_buffer_by(v, v->capacity - new_capacity);
}

Vector* vector_shrink_to_fit(Vector* v)
{
    return (v->size != v->capacity) ? vector_resize(v, v->size) : v;
}

Vector* vector_clear(Vector* v)
{
    if (vector_is_empty(v))
        return v;

    v->size = 0;
    memset(v->buffer_ptr, 0, INIT_CAPACITY);
    vector_resize(v, INIT_CAPACITY);

    return v;
}

/*
 *                                 Reversion.
 */

Vector* vector_reverse(Vector* v)
{
    for (size_t i = 0; i < v->size / 2; ++i)
        swap(vector_get_internal(v, i),
             vector_get_internal(v, v->size - i - 1),
             v->data_size);
    return v;
}

/*
 *                                   Printing.
 */

void vector_info(const Vector* v)
{
    const char* format = "%10s - %2d\n";
    printf(format, "DATA_SIZE", v->data_size);
    printf(format, "SIZE",      v->size);
    printf(format, "CAPACITY",  v->capacity);
}

void vector_print(const Vector* v, PrintFunc print_func)
{
    if (vector_is_empty(v)) {
        puts("[]");
        return;
    }

    printf("[");
    for (size_t i = 0; i < v->size; ++i) {
        (*print_func)(vector_get_internal(v, i));
        if (i + 1 < v->size)
            printf(", ");
    }
    printf("]\n");
}

/*
 *                                  Internal.
 */

static void vector_set_internal(Vector* v, size_t pos, const void* data_ptr)
{
    memcpy((char*) v->buffer_ptr + pos * v->data_size, data_ptr, v->data_size);
}

static void* vector_get_internal(const Vector* v, size_t pos)
{
    return (char*) v->buffer_ptr + pos * v->data_size;
}

static Vector* vector_grow_buffer_by(Vector* v, size_t n)
{
    v->capacity += n;

    v->buffer_ptr = realloc(v->buffer_ptr, v->capacity * v->data_size);
    assert(v->buffer_ptr);
    memset(v->buffer_ptr + vector_size(v) * v->data_size, 0, n);

    return v;
}

static Vector* vector_shrink_buffer_by(Vector* v, size_t n)
{
    v->capacity -= n;
    v->size = (v->size > v->capacity) ? v->capacity : v->size;

    v->buffer_ptr = realloc(v->buffer_ptr, v->capacity * v->data_size);
    assert(v->buffer_ptr);

    return v;
}

static void swap(void* a_ptr, void* b_ptr, size_t data_size)
{
    char temp_buffer[data_size];
    memcpy(temp_buffer, a_ptr, data_size);
    memcpy(a_ptr, b_ptr, data_size);
    memcpy(b_ptr, temp_buffer, data_size);
}
