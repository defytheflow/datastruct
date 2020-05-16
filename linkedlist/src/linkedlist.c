#include "../src/linkedlist.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct LLNode {
    void* data_ptr;
    struct LLNode* next;
};

static struct LLNode* ll_node_init(size_t data_size, const void* data_ptr);
static void ll_node_free(struct LLNode*, FreeFunc);

/* Constructor. */
LinkedList* linkedlist_init(size_t data_size, FreeFunc free_func)
{
    LinkedList* ll = malloc(sizeof(LinkedList));
    assert(ll);

    ll->data_size = data_size;
    ll->size = 0;
    ll->free_func = (*free_func);
    ll->head = NULL;

    return ll;
}

/* Destructor. */
void linkedlist_free(LinkedList* ll)
{
    struct LLNode *curr_node, *temp;

    if (linkedlist_is_empty(ll)) {
        free(ll);
        return;
    }

    curr_node = ll->head;

    while (curr_node->next) {
        temp = curr_node->next;
        ll_node_free(curr_node, ll->free_func);
        curr_node = temp;
    }

    ll_node_free(curr_node, ll->free_func);
    free(ll);
}

void* linkedlist_get(const LinkedList* ll, size_t pos)
{
    assert(pos < ll->size);

    struct LLNode* curr_node = ll->head;

    for (size_t i = 0; i < pos; ++i, curr_node = curr_node->next)
        ;

    return curr_node->data_ptr;
}

void linkedlist_set(const LinkedList* ll, size_t pos, const void* data_ptr)
{
    assert(pos < ll->size);

    struct LLNode* curr_node = ll->head;

    for (size_t i = 0; i < pos; ++i, curr_node = curr_node->next)
        ;

    memcpy(curr_node->data_ptr, data_ptr, ll->data_size);
}

void linkedlist_push_back(LinkedList* ll, const void* data_ptr)
{
    struct LLNode *new_node, *curr_node;

    new_node = ll_node_init(ll->data_size, data_ptr);

    if (linkedlist_is_empty(ll)) {
        ll->head = new_node;
        ++ll->size;
        return;
    }

    for (curr_node = ll->head; curr_node->next; curr_node = curr_node->next)
        ;

    curr_node->next = new_node;
    ++ll->size;
}

void linkedlist_push_front(LinkedList* ll, const void* data_ptr)
{
    struct LLNode *new_node, *temp_node;

    new_node = ll_node_init(ll->data_size, data_ptr);

    if (linkedlist_is_empty(ll)) {
        ll->head = new_node;
        ++ll->size;
        return;
    }

    temp_node = ll->head;
    ll->head = new_node;
    new_node->next = temp_node;
    ++ll->size;
}

/* void linkedlist_insert(LinkedList*, size_t pos, const void* data_ptr) */
/* { */
/*     struct LLNode *new_node, *temp_node; */

/*     new_node = ll_node_init(ll->data_size, data_ptr); */

/* } */

void linkedlist_print(const LinkedList* ll, PrintFunc print_func)
{
    struct LLNode* curr_node = ll->head;

    if (linkedlist_is_empty(ll)) {
        puts("[]");
        return;
    }

    printf("[");
    while (curr_node) {
        (*print_func)(curr_node->data_ptr);
        if (curr_node->next)
            printf(" -> ");
        curr_node = curr_node->next;
    }
    printf("]\n");
}

static struct LLNode* ll_node_init(size_t data_size, const void* data_ptr)
{
    struct LLNode* new_node = malloc(sizeof(struct LLNode));
    assert(new_node);

    new_node->data_ptr = malloc(data_size);
    assert(new_node->data_ptr);

    memcpy(new_node->data_ptr, data_ptr, data_size);
    new_node->next = NULL;

    return new_node;
}

static void ll_node_free(struct LLNode* node, FreeFunc free_func)
{
    if (free_func)
        free_func(node->data_ptr);
    else
        free(node->data_ptr);
    free(node);
}
