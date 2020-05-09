#include "linkedlist.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASSERT_MEMORY_ALLOCATED(PTR) \
    assert((PTR) && "Memory allocation error");

/* Constructor */
LinkedList* linkedlist_new(size_t data_size, void(*free_func)(void*))
{
    LinkedList* ll = malloc(sizeof(LinkedList));
    ASSERT_MEMORY_ALLOCATED(ll);

    ll->data_size = data_size;
    ll->free_func = (*free_func);
    ll->head = NULL;

    return ll;
}

/* Destructor */
void linkedlist_delete(LinkedList* ll)
{
    Node* curr_node = ll->head;

    while (curr_node->next) {
        Node* temp = curr_node->next;
        ll->free_func(curr_node->data_ptr);
        free(curr_node);
        curr_node = temp;
    }

    ll->free_func(curr_node->data_ptr);
    free(curr_node);
    free(ll);
}

/* States */
bool linkedlist_empty(const LinkedList* ll) { return ll->head == NULL; }

/* Methods */
void linkedlist_push_back(LinkedList* ll, const void* data_ptr)
{
    Node *new_node, *curr_node;

    new_node = malloc(sizeof(Node));
    ASSERT_MEMORY_ALLOCATED(new_node);

    new_node->data_ptr = malloc(ll->data_size);
    ASSERT_MEMORY_ALLOCATED(new_node);

    memcpy(new_node->data_ptr, data_ptr, ll->data_size);
    new_node->next = NULL;

    if (linkedlist_empty(ll)) {
        ll->head = new_node;
        return;
    }

    for (curr_node = ll->head; curr_node->next; curr_node = curr_node->next);
    curr_node->next = new_node;
}

void linkedlist_print(const LinkedList* ll, void(*print_func)(const void*))
{
    Node* curr_node = ll->head;

    if (linkedlist_empty(ll)) {
        puts("[]");
        return;
    }

    printf("[");
    while (curr_node) {
        (*print_func)(curr_node->data_ptr);
        if (curr_node->next) printf(" -> ");
        curr_node = curr_node->next;
    }
    printf("]\n");
}
