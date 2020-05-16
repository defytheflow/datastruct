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
ArrayList* arraylist_init(size_t data_size, FreeFunc);

/* Destructor. */
void arraylist_free(ArrayList* al);

/* Accessors. */
static inline size_t arraylist_data_size(const ArrayList* al)
{
    return al->data_size;
}

static inline size_t arraylist_size(const ArrayList* al)
{
    return al->size;
}

static inline size_t arraylist_capacity(const ArrayList* al)
{
    return al->capacity;
}

static inline bool arraylist_is_empty(const ArrayList* al)
{
    return al->size == 0;
}

static inline bool arraylist_is_full(const ArrayList* al)
{
    return al->size == al->capacity;
}

bool arraylist_is_sorted(const ArrayList* al, CmpFunc);

/* Index operator. */
void* arraylist_get(const ArrayList* al, size_t pos);

void arraylist_set(ArrayList* al, size_t pos, const void* data_ptr);

/* Concatenation operator. */
ArrayList* arraylist_concat(ArrayList* dest, const ArrayList* src);

/* Equals operator. */
bool arraylist_equals(const ArrayList* al1, const ArrayList* al2, CmpFunc);

/* Insertion. */
void arraylist_push_back(ArrayList* al, const void* data_ptr);

void arraylist_insert(ArrayList* al, size_t pos, const void* data_ptr);

/* Removal. */
void* arraylist_pop(ArrayList* al);

void arraylist_erase(ArrayList* al, size_t pos);

/* Search. */
int arraylist_lsearch(const ArrayList* al, const void* needle, CmpFunc);

int arraylist_bsearch(const ArrayList* al, const void* needle, CmpFunc);

/* Resize. */
ArrayList* arraylist_resize(ArrayList* al, size_t new_size);

ArrayList* arraylist_shrink_to_fit(ArrayList* al);

ArrayList* arraylist_clear(ArrayList* al);

/* Sort. */
ArrayList* arraylist_sort(ArrayList* al, CmpFunc);

/* Reverse. */
ArrayList* arraylist_reverse(ArrayList* al);

/* Print. */
void arraylist_print(const ArrayList* al, PrintFunc);

void arraylist_info(const ArrayList* al);

#ifdef __cplusplus
}
#endif

#endif /* ARRAY_LIST_H */
