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

#define ASSERT_INDEX_IS_VALID(AL, POS) \
    assert((POS) < (AL)->size && "Index out of bounds.")

static void arraylist_set_internal(ArrayList* al, size_t pos, const void* data_ptr);
static void* arraylist_get_internal(ArrayList* al, size_t pos);

static void arraylist_grow_buffer_by(ArrayList* al, size_t n);
static void arraylist_shrink_buffer_by(ArrayList* al, size_t n);

static void swap(void* a, void* b, size_t data_size);

/* Constructor. */
ArrayList* arraylist_new(size_t data_size)
{
    ArrayList* al = (ArrayList*)malloc(sizeof(ArrayList));
    assert(al);

    al->data_size = data_size;
    al->size = 0;
    al->capacity = INIT_CAPACITY;

    al->buffer_ptr = malloc(al->data_size * al->capacity);
    assert(al->buffer_ptr);

    return al;
}

/* Destructor. */
void arraylist_del(ArrayList* al)
{  // TODO add free function.
    free(al->buffer_ptr);
    free(al);
    al->buffer_ptr = NULL;
}

/* Getters. */
size_t arraylist_data_size(const ArrayList* al) { return al->data_size; }

size_t arraylist_size(const ArrayList* al) { return al->size; }

size_t arraylist_capacity(const ArrayList* al) { return al->capacity; }

/* States. */
bool arraylist_is_empty(const ArrayList* al) { return al->size == 0; }

bool arraylist_is_full(const ArrayList* al) { return al->size == al->capacity; }

bool arraylist_is_sorted(const ArrayList* al, int(*cmp_func)(const void*, const void*))
{
    for (size_t i = 0; i < al->size - 1; ++i) {
        void* first_elem = arraylist_get(al, i);
        void* second_elem = arraylist_get(al, i + 1);
        if ((*cmp_func)(first_elem, second_elem) > 0)
            return false;
    }
    return true;
}

/* Index operator. */
void* arraylist_get(const ArrayList* al, size_t pos)
{
    ASSERT_INDEX_IS_VALID(al, pos);
    return (char*) al->buffer_ptr + pos * al->data_size;
}

void arraylist_set(ArrayList* al, size_t pos, const void* data_ptr)
{
    ASSERT_INDEX_IS_VALID(al, pos);
    memcpy((char*)al->buffer_ptr + pos * al->data_size, data_ptr, al->data_size);
}

/* Concatenation operator. */
ArrayList* arraylist_concat(ArrayList* al_dest, const ArrayList* al_src)
{
    for (size_t i = 0; i < al_src->size; ++i) {
        arraylist_push_back(al_dest, arraylist_get(al_src, i));
    }
    return al_dest;
}

/* Equals operator. */
bool arraylist_equals(const ArrayList* al1, const ArrayList* al2,
                      int(*cmp_func)(const void*, const void*))
{
    if (al1->size != al2->size) return false;

    for (size_t i = 0; i < al1->size; ++i) {
        if ((*cmp_func)(arraylist_get(al1, i), arraylist_get(al2, i)))
            return false;
    }
    return true;
}

/* Insertion. */
void arraylist_push_back(ArrayList* al, const void* data_ptr)
{
    if (arraylist_is_full(al)) {
        arraylist_resize(al, al->capacity * GROW_FACTOR);
    }

    ++al->size;
    arraylist_set(al, al->size - 1, data_ptr);
}

void arraylist_insert(ArrayList* al, size_t pos, const void* data_ptr)
{
    ASSERT_INDEX_IS_VALID(al, pos);

    if (arraylist_is_full(al)) {
        arraylist_resize(al, al->capacity * GROW_FACTOR);
    }

    for (size_t i = al->size - 1; i >= pos; --i) {
        arraylist_set_internal(al, i + 1, arraylist_get(al, i));
    }

    arraylist_set(al, pos, data_ptr);
    ++al->size;
}

/* Removal. */
void* arraylist_pop(ArrayList* al)
{
    assert(!(arraylist_is_empty(al)));
    return arraylist_get_internal(al, --al->size);
}


void arraylist_erase(ArrayList* al, size_t pos)
{
    ASSERT_INDEX_IS_VALID(al, pos);

    for (size_t i = pos; i < al->size - 1; ++i) {
        arraylist_set(al, i, arraylist_get(al, i + 1));
    }

    --al->size;
}

void arraylist_remove(ArrayList* al, const void* data_ptr)
{
    int pos = arraylist_lsearch(al, data_ptr);
    if (pos == NOT_FOUND) return;
    arraylist_erase(al, (size_t) pos);
}


/* Searching. */
int arraylist_lsearch(ArrayList* al, const void* data_ptr)
{
    for (size_t i = 0; i < al->size; ++i) {
        if (!memcmp(arraylist_get(al, i), data_ptr, al->data_size))
            return i;
    }
    return NOT_FOUND;
}

int arraylist_bsearch(ArrayList* al, const void* data_ptr)
{
    // TODO
    return 0;
}

/* Resizing. */
ArrayList* arraylist_shrink_to_fit(ArrayList* al)
{
    al->capacity = al->size;
    al->buffer_ptr = realloc(al->buffer_ptr, al->capacity * al->data_size);
    assert(al->buffer_ptr);
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
    if (arraylist_is_empty(al)) return al;

    if (al->size <= INIT_CAPACITY) {
        al->size = 0;
        return al;
    }

    al->size = 0;
    al->capacity = INIT_CAPACITY;

    al->buffer_ptr = realloc(al->buffer_ptr, INIT_CAPACITY * al->data_size);
    assert(al->buffer_ptr);

    return al;
}


/* Sorting. */
ArrayList* arraylist_sort(ArrayList* al, int(*cmp_func)(const void*, const void*))
{
    if (arraylist_is_empty(al) || al->size == 1) return al;

    for (size_t i = 0; i < al->size; ++i) {
        int min_index = i;
        for (size_t j = i + 1; j < al->size; ++j) {
            void* j_data_ptr = arraylist_get(al, j);
            void* min_index_data_ptr = arraylist_get(al, min_index);
            if ((*cmp_func)(j_data_ptr, min_index_data_ptr) < 0) {
                min_index = j;
            }
        }
        swap(arraylist_get(al, i), arraylist_get(al, min_index), al->data_size);
    }
    return al;
}

ArrayList* arraylist_reverse(ArrayList* al)
{
    for (size_t i = 0; i < al->size / 2; ++i) {
        swap(arraylist_get(al, i), arraylist_get(al, al->size - i - 1), al->data_size);
    }
    return al;
}

/* Printing. */
void arraylist_info(const ArrayList* al)
{
    const char* format = "%10s - %2d\n";
    printf(format, "data_size", al->data_size);
    printf(format, "SIZE",      al->size);
    printf(format, "CAPACITY",  al->capacity);
}

void arraylist_print(const ArrayList* al, void(*print_func)(const void*))
{
    if (arraylist_is_empty(al)) {
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

/* Internal. */
static void arraylist_set_internal(ArrayList* al, size_t pos, const void* data_ptr)
{
    memcpy((char*)al->buffer_ptr + pos * al->data_size, data_ptr, al->data_size);
}

static void* arraylist_get_internal(ArrayList* al, size_t pos)
{
    return (char*) al->buffer_ptr + pos * al->data_size;
}

static void arraylist_grow_buffer_by(ArrayList* al, size_t n)
{
    al->capacity += n;
    al->buffer_ptr = realloc(al->buffer_ptr, al->capacity * al->data_size);
    assert(al->buffer_ptr);
}

static void arraylist_shrink_buffer_by(ArrayList* al, size_t n)
{
    al->capacity = al->capacity - n;
    al->size = (al->size > al->capacity) ? al->capacity : al->size;

    al->buffer_ptr = realloc(al->buffer_ptr, al->capacity * al->data_size);
    assert(al->buffer_ptr);
}

static void swap(void* a_ptr, void* b_ptr, size_t data_size)
{
    char temp_buffer[data_size];

    memcpy(temp_buffer, a_ptr, data_size);
    memcpy(a_ptr, b_ptr, data_size);
    memcpy(b_ptr, temp_buffer, data_size);
}
