#include "arraylist.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GROW_FACTOR    2
#define INIT_CAPACITY  4
#define NOT_FOUND     -1

static void* arraylist_get_internal(const ArrayList*, size_t pos);
static void  arraylist_set_internal(ArrayList*, size_t pos, const void*);

static ArrayList* arraylist_grow_buffer_by(ArrayList*, size_t n);
static ArrayList* arraylist_shrink_buffer_by(ArrayList*, size_t n);

static void swap(void*, void*, size_t);

/*
 *                                Construction.
 */

ArrayList* arraylist_create(size_t data_size, FreeFunc free_func)
{
    ArrayList* al = (ArrayList*) malloc(sizeof(ArrayList));
    assert(al);

    al->data_size = data_size;
    al->size = 0;
    al->capacity = INIT_CAPACITY;
    al->free_func = (*free_func);

    al->buffer_ptr = malloc(al->data_size * al->capacity);
    assert(al->buffer_ptr);

    return al;
}

/*
 *                                Destruction.
 */

void arraylist_free(ArrayList* al)
{
    if (al->free_func) {
        for (size_t i = 0; i < al->size; ++i)
            al->free_func(arraylist_get_internal(al, i));
    }
    free(al->buffer_ptr);
    free(al);
}

/*
 *                                   State.
 */

bool arraylist_is_sorted(const ArrayList* al, CmpFunc cmp_func)
{
    for (size_t i = 0; i < al->size - 1; ++i) {
        if ((*cmp_func)(arraylist_get_internal(al, i),
                        arraylist_get_internal(al, i + 1)) > 0)
            return false;
    }
    return true;
}

/*
 *                                  Indexing.
 */

void* arraylist_get(const ArrayList* al, size_t pos)
{
    assert(pos < al->size);
    return (char*) al->buffer_ptr + pos * al->data_size;
}

void arraylist_set(ArrayList* al, size_t pos, const void* data_ptr)
{
    assert(pos < al->size);
    memcpy((char*) al->buffer_ptr + pos * al->data_size, data_ptr, al->data_size);
}

/*
 *                               Concatenation.
 */

ArrayList* arraylist_concat(ArrayList* dest, const ArrayList* src)
{
    for (size_t i = 0; i < src->size; ++i)
        arraylist_push_back(dest, arraylist_get_internal(src, i));
    return dest;
}

/*
 *                                  Equality.
 */

bool arraylist_equals(const ArrayList* al1, const ArrayList* al2, CmpFunc cmp_func)
{
    if (al1->size != al2->size) return false;

    for (size_t i = 0; i < al1->size; ++i) {
        if ((*cmp_func)(arraylist_get_internal(al1, i),
                        arraylist_get_internal(al2, i)))
            return false;
    }
    return true;
}

/*
 *                                 Insertion.
 */

void arraylist_push_back(ArrayList* al, const void* data_ptr)
{
    if (arraylist_is_full(al))
        arraylist_resize(al, al->capacity * GROW_FACTOR);

    arraylist_set_internal(al, al->size++, data_ptr);
}

void arraylist_insert(ArrayList* al, size_t pos, const void* data_ptr)
{
    assert(pos < al->size);

    if (arraylist_is_full(al))
        arraylist_resize(al, al->capacity * GROW_FACTOR);

    for (size_t i = al->size - 1; i >= pos; --i)
        arraylist_set_internal(al, i + 1, arraylist_get_internal(al, i));

    arraylist_set_internal(al, pos, data_ptr);
    ++al->size;
}

/*
 *                                  Removal.
 */

void* arraylist_pop_back(ArrayList* al)
{
    assert(!(arraylist_is_empty(al)));
    return arraylist_get_internal(al, --al->size);
}

void arraylist_erase(ArrayList* al, size_t pos)
{
    assert(pos < al->size);

    for (size_t i = pos; i < al->size - 1; ++i)
        arraylist_set_internal(al, i, arraylist_get_internal(al, i + 1));

    --al->size;
}

/*
 *                                   Resize.
 */

ArrayList* arraylist_resize(ArrayList* al, size_t new_size)
{
    return (al->capacity < new_size) ?
        arraylist_grow_buffer_by(al, new_size - al->capacity) :
        arraylist_shrink_buffer_by(al, al->capacity - new_size);
}

ArrayList* arraylist_shrink_to_fit(ArrayList* al)
{
    return arraylist_resize(al, al->size);
}

ArrayList* arraylist_clear(ArrayList* al)
{
    if (arraylist_is_empty(al))
        return al;

    if (al->size <= INIT_CAPACITY) {
        al->size = 0;
        return al;
    }

    al->size = 0;
    return arraylist_resize(al, INIT_CAPACITY);
}

/*
 *                                 Reversion.
 */

ArrayList* arraylist_reverse(ArrayList* al)
{
    for (size_t i = 0; i < al->size / 2; ++i)
        swap(arraylist_get_internal(al, i),
             arraylist_get_internal(al, al->size - i - 1),
             al->data_size);
    return al;
}

/*
 *                                   Printing.
 */

void arraylist_info(const ArrayList* al)
{
    const char* format = "%10s - %2d\n";
    printf(format, "DATA_SIZE", al->data_size);
    printf(format, "SIZE",      al->size);
    printf(format, "CAPACITY",  al->capacity);
}

void arraylist_print(const ArrayList* al, PrintFunc print_func)
{
    if (arraylist_is_empty(al)) {
        puts("[]");
        return;
    }

    printf("[");
    for (size_t i = 0; i < al->size; ++i) {
        (*print_func)(arraylist_get_internal(al, i));
        if (i + 1 < al->size)
            printf(", ");
    }
    printf("]\n");
}

/*
 *                                  Internal.
 */

static void arraylist_set_internal(ArrayList* al, size_t pos, const void* data_ptr)
{
    memcpy((char*) al->buffer_ptr + pos * al->data_size, data_ptr, al->data_size);
}

static void* arraylist_get_internal(const ArrayList* al, size_t pos)
{
    return (char*) al->buffer_ptr + pos * al->data_size;
}

static ArrayList* arraylist_grow_buffer_by(ArrayList* al, size_t n)
{
    al->capacity += n;

    al->buffer_ptr = realloc(al->buffer_ptr, al->capacity * al->data_size);
    assert(al->buffer_ptr);

    return al;
}

static ArrayList* arraylist_shrink_buffer_by(ArrayList* al, size_t n)
{
    al->capacity -= n;
    al->size = (al->size > al->capacity) ? al->capacity : al->size;

    al->buffer_ptr = realloc(al->buffer_ptr, al->capacity * al->data_size);
    assert(al->buffer_ptr);

    return al;
}

static void swap(void* a_ptr, void* b_ptr, size_t data_size)
{
    char temp_buffer[data_size];
    memcpy(temp_buffer, a_ptr, data_size);
    memcpy(a_ptr, b_ptr, data_size);
    memcpy(b_ptr, temp_buffer, data_size);
}
