#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void(*FreeFunc)(void*);

typedef void(*PrintFunc)(const void*);

typedef struct ListNode {
    void* data_ptr;
    struct ListNode* next;
} ListNode;

typedef struct {
    size_t data_size;
    size_t size;
    ListNode* head;
    ListNode* tail;
    FreeFunc free_func;
} LinkedList;

/*
 * Construction.
 */

LinkedList* linkedlist_create(LinkedList* list, size_t data_size, FreeFunc);

/*
 * Destruction.
 */

void linkedlist_free(LinkedList* list);

/*
 * Size.
 */

static inline size_t linkedlist_size(const LinkedList* list)
{
    return list->size;
}

/*
 * Sizeof.
 */

static inline size_t linkedlist_sizeof(const LinkedList* list)
{
    return sizeof(LinkedList) + linkedlist_size(list) * sizeof(struct ListNode);
}

/*
 * Emptiness.
 */

static inline bool linkedlist_is_empty(const LinkedList* list)
{
    return list->head == NULL;
}

/*
 * Indexing.
 */

void* linkedlist_get(const LinkedList* list, size_t pos);

void linkedlist_set(const LinkedList* list, size_t pos, const void* data_ptr);

/*
 * Insertion.
 */

void linkedlist_push_back(LinkedList* list, const void* data_ptr);

void linkedlist_push_front(LinkedList* list, const void* data_ptr);

void linkedlist_insert(LinkedList* list, size_t pos, const void* data_ptr);

/*
 * Removal.
 */

void* linkedlist_pop_back(LinkedList* list);

void* linkedlist_pop_front(LinkedList* list);

void linkedlist_erase(LinkedList* list, size_t pos);

/*
 * Printing.
 */

void linkedlist_print(const LinkedList* list, PrintFunc);

#ifdef __cplusplus
}
#endif

#endif /* LINKED_LIST_H */
