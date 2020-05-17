#ifndef LIST_H
#define LIST_H

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
} List;

/*
 * Construction.
 */

List* list_create(List* list, size_t data_size, FreeFunc);

/*
 * Destruction.
 */

void list_free(List* list);

/*
 * Size.
 */

static inline size_t list_size(const List* list)
{
    return list->size;
}

/*
 * Sizeof.
 */

static inline size_t list_sizeof(const List* list)
{
    return sizeof(List) + list_size(list) * sizeof(struct ListNode);
}

/*
 * Emptiness.
 */

static inline bool list_is_empty(const List* list)
{
    return list->head == NULL;
}

/*
 * Indexing.
 */

void* list_get(const List* list, size_t pos);

void list_set(const List* list, size_t pos, const void* data_ptr);

/*
 * Insertion.
 */

void list_push_back(List* list, const void* data_ptr);

void list_push_front(List* list, const void* data_ptr);

void list_insert(List* list, size_t pos, const void* data_ptr);

/*
 * Removal.
 */

void* list_pop_back(List* list, void* data_out);

void* list_pop_front(List* list);

void list_erase(List* list, size_t pos);

/*
 * Printing.
 */

void list_print(const List* list, PrintFunc);

#ifdef __cplusplus
}
#endif

#endif /* LIST_H */
