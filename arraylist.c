#include "arraylist.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

#define ARRAYLIST_GROW_FACTOR 2
#define ARRAYLIST_INIT_CAPACITY 4

static void arraylist_grow_buffer(ArrayList* al);
static void arraylist_grow_buffer_by(ArrayList* al, size_t count);
static void arraylist_shrink_buffer_by(ArrayList* al, size_t count);

static void arraylist_check_index(const ArrayList* al, size_t pos, const char* fun_name);
static void arraylist_check_memory_allocation(const ArrayList* al, const char* fun_name);
static void arraylist_error(const char* fun_name, const char* error_msg);

static void swap(int* a, int* b);

void arraylist_init(ArrayList* al)
{
    al->size = 0;
    al->capacity = ARRAYLIST_INIT_CAPACITY;
    al->buffer_ptr = malloc(sizeof(int) * al->capacity);
    arraylist_check_memory_allocation(al, "arraylist_init");
}

void arraylist_del(ArrayList* al)
{
    free(al->buffer_ptr);
}

int arraylist_size(const ArrayList* al)
{
    return al->size;
}

int arraylist_capacity(const ArrayList* al)
{
    return al->capacity;
}

bool arraylist_empty(const ArrayList* al)
{
    return al->size == 0;
}

int arraylist_get(const ArrayList* al, size_t pos)
{
    arraylist_check_index(al, pos, "arraylist_get");
    return al->buffer_ptr[pos];
}

void arraylist_set(ArrayList* al, size_t pos, int val)
{
    arraylist_check_index(al, pos, "arraylist_set");
    al->buffer_ptr[pos] = val;
}

void arraylist_push(ArrayList* al, int val)
{
    if (al->size == al->capacity)
        arraylist_grow_buffer(al);
    
    al->buffer_ptr[al->size] = val;
    ++al->size;
}

int arraylist_pop(ArrayList* al)
{
    if (arraylist_empty(al)) {
        arraylist_error("arraylist_pop", "array list is empty");
    }
    
    --al->size;
    return al->buffer_ptr[al->size];
}

void arraylist_sort(ArrayList* al, bool ascend)
{
    if (al->size == 0 || al->size == 1)
            return;

    if (ascend) {
        for (int i = 0; i < al->size; ++i) {
            int min_index = i;
            for (int j = i + 1; j < al->size; ++j) {
                if (al->buffer_ptr[j] < al->buffer_ptr[min_index])
                    min_index = j;
            }
            swap(al->buffer_ptr + i, al->buffer_ptr + min_index);
        }
    } else {
        for (int i = 0; i < al->size; ++i) {
            int max_index = i;
            for (int j = i + 1; j < al->size; ++j) {
                if (al->buffer_ptr[j] > al->buffer_ptr[max_index])
                    max_index = j;
            }
            swap(al->buffer_ptr + i, al->buffer_ptr + max_index);
        }
    }
}

void arraylist_print(const ArrayList* al)
{
    if (arraylist_empty(al)) {
        puts("[]");
        return;
    }

    printf("[");
    for (int i = 0; i < arraylist_size(al); ++i) {
        printf("%d, ", arraylist_get(al, i));
    }
    printf("\b\b]\n");
}

void arraylist_reverse(ArrayList* al)
{
    for (int i = 0; i < arraylist_size(al) / 2; ++i) {
        swap(al->buffer_ptr + i, al->buffer_ptr + arraylist_size(al) - i - 1);
    }
}

void arraylist_clear(ArrayList* al)
{
    if (arraylist_empty(al))
        return;
    
    if (arraylist_size(al) <= ARRAYLIST_INIT_CAPACITY) {
        al->size = 0;
        return;
    }

    al->size = 0;
    al->capacity = ARRAYLIST_INIT_CAPACITY;
    al->buffer_ptr = (int*)realloc(al->buffer_ptr, sizeof(int) * ARRAYLIST_INIT_CAPACITY);
    arraylist_check_memory_allocation(al, "arraylist_clear");
}

void arraylist_resize(ArrayList* al, size_t count)
{
    if (arraylist_capacity(al) < count) {
        arraylist_grow_buffer_by(al, count - arraylist_capacity(al));
    } else {
        arraylist_shrink_buffer_by(al, arraylist_capacity(al) - count);
    }
}

void arraylist_insert(ArrayList* al, size_t pos, int val)
{
    arraylist_check_index(al, pos , "arraylist_insert");

    if (arraylist_size(al) == arraylist_capacity(al)) {
        arraylist_grow_buffer(al);
    }

    for (int i = pos; i < arraylist_size(al) - 1; ++i) {
       int temp = arraylist_get(al, i + 1);
       arraylist_set(al, i + 1, arraylist_get(al, i));
    }
}
    
static void arraylist_grow_buffer(ArrayList* al)
{
    al->capacity *= ARRAYLIST_GROW_FACTOR;

    int* new_buffer_ptr = malloc(sizeof(int) * al->capacity);
    arraylist_check_memory_allocation(al, "arraylist_grow_buffer");

    for (int i = 0; i < al->size; ++i) {
        new_buffer_ptr[i] = al->buffer_ptr[i];
    }

    free(al->buffer_ptr);

    al->buffer_ptr = new_buffer_ptr;
}

static void arraylist_check_index(const ArrayList* al, size_t pos, const char* fun_name)
{
    if (pos < 0 || pos >= al->size) {
        arraylist_error("arraylist_check_index", "index out of bounds");
    }
}

static void arraylist_check_memory_allocation(const ArrayList* al, const char* fun_name)
{
    if (!al->buffer_ptr) {
        arraylist_error(fun_name, "memory allocation error");
    }
}

static void arraylist_grow_buffer_by(ArrayList* al, size_t count)
{
    al->capacity += count;
    al->buffer_ptr = (int*)realloc(al->buffer_ptr, al->capacity * sizeof(int));
    arraylist_check_memory_allocation(al, "arraylist_grow_buffer_by");
}

static void arraylist_shrink_buffer_by(ArrayList* al, size_t count)
{
    int new_capacity = arraylist_capacity(al) - count;
    if (arraylist_size(al) > new_capacity) {
        al->size = new_capacity;
    }
    al->capacity = new_capacity;
    al->buffer_ptr = (int*)realloc(al->buffer_ptr, sizeof(int) * new_capacity);
    arraylist_check_memory_allocation(al, "arraylist_shrink_buffer_by");
}

static void arraylist_error(const char* fun_name, const char* error_msg)
{
    fprintf(stderr, "%s: %s\n", fun_name, error_msg);
    exit(1);
}

static void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}