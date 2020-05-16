#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void(*FreeFunc)(void*);

typedef int(*CmpFunc)(const void*, const void*);

typedef void(*PrintFunc)(const void*);

typedef struct LLNode LLNode;

typedef struct {
    size_t data_size;
    size_t size;
    FreeFunc free_func;
    LLNode* head;
} LinkedList;

/*
 * Construction.
 */

LinkedList* linkedlist_init(size_t data_size, FreeFunc);

/*
 * Destruction.
 */

void linkedlist_free(LinkedList*);

/*
 * Field Accessing.
 */

static inline size_t linkedlist_data_size(const LinkedList* ll)
{
    return ll->data_size;
}

static inline size_t linkedlist_size(const LinkedList* ll)
{
    return ll->size;
}

/*
 * State.
 */

static inline bool linkedlist_is_empty(const LinkedList* ll)
{
    return ll->head == NULL;
}

/*
 * Indexing.
 */

void* linkedlist_get(const LinkedList* ll, size_t pos);

void linkedlist_set(const LinkedList* ll, size_t pos, const void* data_ptr);

/*
 * Insertion.
 */

void linkedlist_push_back(LinkedList* ll, const void* data_ptr);

void linkedlist_push_front(LinkedList* ll, const void* data_ptr);

void linkedlist_insert(LinkedList* ll, size_t pos, const void* data_ptr);

/*
 * Removal.
 */

// TODO.

/*
 * Printing.
 */

void linkedlist_print(const LinkedList* ll, PrintFunc);

#ifdef __cplusplus
}
#endif

#endif /* LINKED_LIST_H */
