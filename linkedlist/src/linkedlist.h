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

struct ll_node {
    void* data_ptr;
    struct ll_node* next;
};

typedef struct {
    size_t data_size;
    FreeFunc free_func;
    struct ll_node* head;
} LinkedList;

/* Constructor. */
LinkedList* linkedlist_new(size_t data_size, FreeFunc);

/* Destructor. */
void linkedlist_del(LinkedList*);

/* State. */
bool linkedlist_is_empty(const LinkedList*);

/* Insert. */
void linkedlist_push_back(LinkedList*, const void* data_ptr);

void linkedlist_push_front(LinkedList*, const void* data_ptr);

void linkedlist_insert(LinkedList*, size_t pos, const void* data_ptr);

void linkedlist_print(const LinkedList*, PrintFunc);

#ifdef __cplusplus
}
#endif

#endif /* LINKED_LIST_H */
