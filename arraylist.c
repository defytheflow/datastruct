#include "arraylist.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

#define ARRAYLIST_GROW_FACTOR 2

static void arraylist_grow_buffer(ArrayList* al);
static void arraylist_check_index(const ArrayList* al, int pos);
static void swap(int* a, int* b);

void arraylist_init(ArrayList* al, size_t capacity)
{
    al->size = 0;
    al->capacity = capacity;
    al->buffer_ptr = malloc(sizeof(int) * capacity);
    if (al->buffer_ptr == NULL) {
        fprintf(stderr, "arraylist_init: memory allocation error\n");
        exit(1);
    }
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

int arraylist_get(const ArrayList* al, size_t pos)
{
    arraylist_check_index(al, pos);
    return al->buffer_ptr[pos];
}

void arraylist_set(ArrayList* al, size_t pos, int val)
{
    arraylist_check_index(al, pos);
    al->buffer_ptr[pos] = val;
}

bool arraylist_empty(const ArrayList* al)
{
    return al->size == 0;
}

void arraylist_push_back(ArrayList* al, int val)
{
    if (al->size == al->capacity)
        arraylist_grow_buffer(al);
    
    al->buffer_ptr[al->size] = val;
    ++al->size;
}

int arraylist_pop_back(ArrayList* al)
{
    if (al->size == 0) {
        fprintf(stderr, "arraylist_pop_back: array list is empty\n");
        exit(1);
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
static void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void arraylist_grow_buffer(ArrayList* al)
{
    al->capacity *= ARRAYLIST_GROW_FACTOR;
    int* new_buffer_ptr = malloc(sizeof(int) * al->capacity);

    if (new_buffer_ptr == NULL){
        fprintf(stderr, "arraylist_grow_buffer: memory allocation error\n");
        exit(1);
    }

    for (int i = 0; i < al->size; ++i) {
        new_buffer_ptr[i] = al->buffer_ptr[i];
    }

    free(al->buffer_ptr);

    al->buffer_ptr = new_buffer_ptr;
}

static void arraylist_check_index(const ArrayList* al, int pos)
{
    if (pos < 0 || pos >= al->size) {
        fprintf(stderr, "arraylist_at: index out of bounds\n");
        exit(1);
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
    for (int i = 0; i < arraylist_size(al); ++i) {
        swap(al->buffer_ptr + i, al->buffer_ptr + arraylist_size(al) - i);
    }
}