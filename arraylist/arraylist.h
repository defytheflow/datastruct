#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    size_t data_size;
    size_t size;
    size_t capacity;
    void*  buffer_ptr;
} ArrayList;

/* Constructor. */
ArrayList* arraylist_new(size_t data_size);

/* Destructor. */
void arraylist_del(ArrayList* al);

/* Getters. */
size_t arraylist_data_size(const ArrayList* al);

size_t arraylist_size(const ArrayList* al);

size_t arraylist_capacity(const ArrayList* al);

/* State. */
bool arraylist_is_empty(const ArrayList* al);

bool arraylist_is_full(const ArrayList* al);

bool arraylist_is_sorted(const ArrayList* al, int(*cmp_func)(const void*, const void*));

/* Index operator. */
void* arraylist_get(const ArrayList* al, size_t pos);

void arraylist_set(ArrayList* al, size_t pos, const void* data_ptr);

/* Concatenation operator. */
ArrayList* arraylist_concat(ArrayList* al_dest, const ArrayList* al_src);

/* Equals operator. */
bool arraylist_equals(const ArrayList* al1, const ArrayList* al2,
                      int(*cmp_func)(const void*, const void*));

/* Insertion. */
void arraylist_push_back(ArrayList* al, const void* data_ptr);

void arraylist_insert(ArrayList* al, size_t pos, const void* data_ptr);

/* Removal. */
void* arraylist_pop(ArrayList* al);

void arraylist_erase(ArrayList* al, size_t pos);

void arraylist_remove(ArrayList* al, const void* data_ptr);

/* Searching. */
int arraylist_lsearch(ArrayList* al, const void* data_ptr);

int arraylist_bsearch(ArrayList* al, const void* data_ptr);

/* Resizing. */
ArrayList* arraylist_shrink_to_fit(ArrayList* al);

ArrayList* arraylist_resize(ArrayList* al, size_t new_size);

ArrayList* arraylist_clear(ArrayList* al);

/* Sorting. */
ArrayList* arraylist_sort(ArrayList* al, int(*cmp_func)(const void*, const void*));

ArrayList* arraylist_reverse(ArrayList* al);

/* Printing. */
void arraylist_info(const ArrayList* al);

void arraylist_print(const ArrayList* al, void(*print_func)(const void*));

#ifdef __cplusplus
}
#endif

#endif /* ARRAY_LIST_H */
