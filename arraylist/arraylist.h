#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

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
    FreeFunc free_func;
    void*  buffer_ptr;
} ArrayList;

/* Constructor. */
ArrayList* arraylist_new(size_t data_size, FreeFunc);

/* Destructor. */
void arraylist_del(ArrayList*);

/* Fields. */
size_t arraylist_data_size(const ArrayList*);

size_t arraylist_size(const ArrayList*);

size_t arraylist_capacity(const ArrayList*);

/* State. */
bool arraylist_is_empty(const ArrayList*);

bool arraylist_is_full(const ArrayList*);

bool arraylist_is_sorted(const ArrayList*, CmpFunc);

/* Index operator. */
void* arraylist_get(const ArrayList*, size_t pos);

void arraylist_set(ArrayList*, size_t pos, const void* data_ptr);

/* Concatenation operator. */
ArrayList* arraylist_concat(ArrayList* dest, const ArrayList* src);

/* Equals operator. */
bool arraylist_equals(const ArrayList* al1, const ArrayList* al2, CmpFunc);

/* Insertion. */
void arraylist_push_back(ArrayList*, const void* data_ptr);

void arraylist_insert(ArrayList*, size_t pos, const void* data_ptr);

/* Removal. */
void* arraylist_pop(ArrayList*);

void arraylist_erase(ArrayList*, size_t pos);

/* Search. */
int arraylist_lsearch(const ArrayList*, const void* needle, CmpFunc);

int arraylist_bsearch(const ArrayList*, const void* needle, CmpFunc);

/* Resize. */
ArrayList* arraylist_resize(ArrayList*, size_t new_size);

ArrayList* arraylist_shrink_to_fit(ArrayList*);

ArrayList* arraylist_clear(ArrayList*);

/* Sort. */
ArrayList* arraylist_sort(ArrayList*, CmpFunc);

/* Reverse. */
ArrayList* arraylist_reverse(ArrayList*);

/* Print. */
void arraylist_print(const ArrayList*, PrintFunc);

void arraylist_info(const ArrayList*);

// TODO foreach

#ifdef __cplusplus
}
#endif

#endif /* ARRAY_LIST_H */
