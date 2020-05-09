#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct node {
    void* data_ptr;
    struct node* next;
} Node;

typedef struct {
    size_t data_size;
    void (*free_func)(void*);
    Node* head;
} LinkedList;

/* Constructor */
LinkedList* linkedlist_new(size_t data_size, void(*free_func)(void*));

/* Destructor */
void linkedlist_delete(LinkedList* ll);

/* States */
bool linkedlist_empty(const LinkedList* ll);

/* Methods */
void linkedlist_push_back(LinkedList* ll, const void* data_ptr);

void linkedlist_print(const LinkedList* ll, void(*print_func)(const void*));

#endif /* LINKED_LIST_H */
