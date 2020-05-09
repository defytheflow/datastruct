#include "arraylist.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GROW_FACTOR   2
#define INIT_CAPACITY 4
#define NOT_FOUND    -1

#define ASSERT_MEMORY_ALLOCATED(PTR) \
    assert((PTR) && "Memory allocation error");
#define ASSERT_INDEX_IS_VALID(AL, POS) \
    assert((POS) < (AL)->size && "Index out of bounds error")
#define ASSERT_NOT_EMPTY(AL) \
    assert(!arraylist_empty((AL)) && "ArrayList is empty");

static void arraylist_grow_buffer_by(ArrayList* al, size_t n);
static void arraylist_shrink_buffer_by(ArrayList* al, size_t n);
static void swap(void* a, void* b, size_t data_size);

/* Constructor */
ArrayList* arraylist_new(size_t data_size)
{
    ArrayList* al = malloc(sizeof(ArrayList));
    ASSERT_MEMORY_ALLOCATED(al);

    al->data_size = data_size;
    al->size = 0;
    al->capacity = INIT_CAPACITY;

    al->buffer_ptr = malloc(al->data_size * al->capacity);
    ASSERT_MEMORY_ALLOCATED(al->buffer_ptr);

    return al;
}

/* Destructor */
void arraylist_del(ArrayList* al)
{
    free(al->buffer_ptr);
    free(al);
}

/* Getters */
size_t arraylist_data_size(const ArrayList* al) { return al->data_size; }

size_t arraylist_size(const ArrayList* al) { return al->size; }

size_t arraylist_capacity(const ArrayList* al) { return al->capacity; }

/* States */
bool arraylist_empty(const ArrayList* al) { return al->size == 0; }

bool arraylist_full(const ArrayList* al) { return al->size == al->capacity; }

/* Index operator */
void* arraylist_get(const ArrayList* al, size_t pos)
{
    return al->buffer_ptr + pos * al->data_size;
}

void arraylist_set(ArrayList* al, size_t pos, const void* data_ptr)
{
    memcpy(al->buffer_ptr + pos * al->data_size, data_ptr, al->data_size);
}

/* Methods */
void arraylist_push_back(ArrayList* al, const void* data_ptr)
{
    if (arraylist_full(al)) {
        arraylist_resize(al, al->capacity * GROW_FACTOR);
    }

    arraylist_set(al, al->size, data_ptr);
    ++al->size;
}

void* arraylist_pop(ArrayList* al)
{
    ASSERT_NOT_EMPTY(al);

    --al->size;
    return arraylist_get(al, al->size);
}

void arraylist_insert(ArrayList* al, size_t pos, const void* data_ptr)
{
    ASSERT_INDEX_IS_VALID(al, pos);

    if (arraylist_full(al)) {
        arraylist_resize(al, al->capacity * GROW_FACTOR);
    }

    for (size_t i = al->size - 1; i >= pos; --i) {
        arraylist_set(al, i + 1, arraylist_get(al, i));
    }

    arraylist_set(al, pos, data_ptr);
    ++al->size;
}

void arraylist_erase(ArrayList* al, size_t pos)
{
    ASSERT_INDEX_IS_VALID(al, pos);

    for (size_t i = pos; i < al->size - 1; ++i) {
        arraylist_set(al, i, arraylist_get(al, i + 1));
    }

    --al->size;
}

int arraylist_find(ArrayList* al, const void* data_ptr)
{
    for (size_t i = 0; i < al->size; ++i) {
        if (!memcmp(arraylist_get(al, i), data_ptr, al->data_size))
            return i;
    }
    return NOT_FOUND;
}

void arraylist_remove(ArrayList* al, const void* data_ptr)
{
    int pos = arraylist_find(al, data_ptr);
    if (pos == NOT_FOUND) return;
    arraylist_erase(al, (size_t) pos);
}

ArrayList* arraylist_shrink_to_fit(ArrayList* al)
{
    al->capacity = al->size;
    al->buffer_ptr = realloc(al->buffer_ptr, al->capacity * al->data_size);
    ASSERT_MEMORY_ALLOCATED(al->buffer_ptr);
    return al;
}

ArrayList* arraylist_resize(ArrayList* al, size_t new_size)
{
    if (al->capacity < new_size) {
        arraylist_grow_buffer_by(al, new_size - al->capacity);
    } else {
        arraylist_shrink_buffer_by(al, al->capacity - new_size);
    }
    return al;
}

ArrayList* arraylist_clear(ArrayList* al)
{
    if (arraylist_empty(al)) return al;

    if (al->size <= INIT_CAPACITY) {
        al->size = 0;
        return al;
    }

    al->size = 0;
    al->capacity = INIT_CAPACITY;

    al->buffer_ptr = realloc(al->buffer_ptr, INIT_CAPACITY * al->data_size);
    ASSERT_MEMORY_ALLOCATED(al->buffer_ptr);

    return al;
}

ArrayList* arraylist_reverse(ArrayList* al)
{
    for (size_t i = 0; i < al->size / 2; ++i) {
        swap(arraylist_get(al, i), arraylist_get(al, al->size - i - 1), al->data_size);
    }
    return al;
}

ArrayList* arraylist_sort(ArrayList* al, int(*compare_func)(const void*, const void*))
{
    if (arraylist_empty(al) || al->size == 1) return al;

    for (size_t i = 0; i < al->size; ++i) {
        int min_index = i;
        for (size_t j = i + 1; j < al->size; ++j) {
            void* j_data_ptr = arraylist_get(al, j);
            void* min_index_data_ptr = arraylist_get(al, min_index);
            if ((*compare_func)(j_data_ptr, min_index_data_ptr) < 0) {
                min_index = j;
            }
        }
        swap(arraylist_get(al, i), arraylist_get(al, min_index), al->data_size);
    }
    return al;
}

ArrayList* arraylist_concat(ArrayList* al_dest, const ArrayList* al_src)
{
    for (size_t i = 0; i < al_src->size; ++i) {
        arraylist_push_back(al_dest, arraylist_get(al_src, i));
    }
    return al_dest;
}

void arraylist_print(const ArrayList* al, void(*print_func)(const void*))
{
    if (arraylist_empty(al)) {
        puts("[]");
        return;
    }

    printf("[");
    for (size_t i = 0; i < al->size; ++i) {
        (*print_func)(arraylist_get(al, i));
        if (i + 1 < al->size) {
            printf(", ");
        }
    }
    printf("]\n");
}

void arraylist_info(const ArrayList* al)
{
    const char* format = "%10s - %2d\n";
    printf(format, "data_size", al->data_size);
    printf(format, "SIZE",      al->size);
    printf(format, "CAPACITY",  al->capacity);
}

static void arraylist_grow_buffer_by(ArrayList* al, size_t n)
{
    al->capacity += n;
    al->buffer_ptr = realloc(al->buffer_ptr, al->capacity * al->data_size);
    ASSERT_MEMORY_ALLOCATED(al->buffer_ptr);
}

static void arraylist_shrink_buffer_by(ArrayList* al, size_t n)
{
    al->capacity = al->capacity - n;
    al->size = (al->size > al->capacity) ? al->capacity : al->size;

    al->buffer_ptr = realloc(al->buffer_ptr, al->capacity * al->data_size);
    ASSERT_MEMORY_ALLOCATED(al->buffer_ptr);
}

static void swap(void* a_ptr, void* b_ptr, size_t data_size)
{
    char temp_buffer[data_size];

    memcpy(temp_buffer, a_ptr, data_size);
    memcpy(a_ptr, b_ptr, data_size);
    memcpy(b_ptr, temp_buffer, data_size);
}
