#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int size;
    int capacity;
    int* buffer_ptr;
} ArrayList;

void arraylist_init(ArrayList* al);

void arraylist_del(ArrayList* al);

inline int arraylist_size(const ArrayList* al);

inline int arraylist_capacity(const ArrayList* al);

inline bool arraylist_empty(const ArrayList* al);

int arraylist_get(const ArrayList* al, size_t pos);

void arraylist_set(ArrayList* al, size_t pos, int val);

void arraylist_push(ArrayList* al, int val);

int arraylist_pop(ArrayList* al);

void arraylist_sort(ArrayList* al, bool ascend);

void arraylist_print(const ArrayList* al);

void arraylist_clear(ArrayList* al);

void arraylist_resize(ArrayList* al, size_t count);

void arraylist_reverse(ArrayList* al);

void arraylist_insert(ArrayList* al, size_t pos, int val);

#endif /* ARRAY_LIST_H */