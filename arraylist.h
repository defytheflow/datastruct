#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    size_t elem_size;
    size_t size;
    size_t capacity;
    void*  buffer_ptr;
} ArrayList;

/* Constructor/Destructor */
ArrayList* arraylist_new(size_t elem_size);

void arraylist_del(ArrayList* al);

/* Getters */
size_t arraylist_elem_size(const ArrayList* al);

size_t arraylist_size(const ArrayList* al);

size_t arraylist_capacity(const ArrayList* al);

/* States */
bool arraylist_empty(const ArrayList* al);

bool arraylist_full(const ArrayList* al);

/* Index operator */
void* arraylist_get(const ArrayList* al, size_t pos);

void arraylist_set(ArrayList* al, size_t pos, const void* val_ptr);

/* Methods. */
void arraylist_push(ArrayList* al, const void* val_ptr);

void arraylist_insert(ArrayList* al, size_t pos, const void* val_ptr);

void* arraylist_pop(ArrayList* al);

void arraylist_erase(ArrayList* al, size_t pos);

int arraylist_find(ArrayList* al, const void* val_ptr);

void arraylist_remove(ArrayList* al, const void* val_ptr);

ArrayList* arraylist_shrink_to_fit(ArrayList* al);

ArrayList* arraylist_resize(ArrayList* al, size_t new_size);

ArrayList* arraylist_clear(ArrayList* al);

ArrayList* arraylist_reverse(ArrayList* al);

ArrayList* arraylist_sort(ArrayList* al, int(*compare_func)(const void*, const void*));

ArrayList* arraylist_concat(ArrayList* al_dest, const ArrayList* al_src);

void arraylist_info(const ArrayList* al);

void arraylist_print(const ArrayList* al, void(*print_func)(const void*));

#endif /* ARRAY_LIST_H */
