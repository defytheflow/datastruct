#include "../src/linkedlist.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct ll_node* ll_node_new(size_t data_size, const void* data_ptr);
static void ll_node_del(struct ll_node*, FreeFunc);

/* Constructor. */
LinkedList* linkedlist_new(size_t data_size, FreeFunc free_func)
{
    LinkedList* ll = malloc(sizeof(LinkedList));
    assert(ll);

    ll->data_size = data_size;
    ll->free_func = (*free_func);
    ll->head = NULL;

    return ll;
}

/* Destructor. */
void linkedlist_del(LinkedList* ll)
{
    struct ll_node *curr_node, *temp;

    curr_node = ll->head;

    while (curr_node->next) {
        temp = curr_node->next;
        ll_node_del(curr_node, ll->free_func);
        curr_node = temp;
    }

    ll_node_del(curr_node, ll->free_func);
    free(ll);
}

/* State. */

bool linkedlist_is_empty(const LinkedList* ll)
{
    return ll->head == NULL;
}

/* Insert. */

void linkedlist_push_back(LinkedList* ll, const void* data_ptr)
{
    struct ll_node *new_node, *curr_node;

    new_node = ll_node_new(ll->data_size, data_ptr);

    if (linkedlist_is_empty(ll)) {
        ll->head = new_node;
        return;
    }

    for (curr_node = ll->head;
         curr_node->next;
         curr_node = curr_node->next);

    curr_node->next = new_node;
}

void linkedlist_push_front(LinkedList* ll, const void* data_ptr)
{
    struct ll_node *new_node, *temp_node;

    new_node = ll_node_new(ll->data_size, data_ptr);

    if (linkedlist_is_empty(ll)) {
        ll->head = new_node;
        return;
    }

    temp_node = ll->head;
    ll->head = new_node;
    new_node->next = temp_node;
}

/* void linkedlist_insert(LinkedList*, size_t pos, const void* data_ptr) */
/* { */
/*     struct ll_node *new_node, *temp_node; */

/*     new_node = ll_node_new(ll->data_size, data_ptr); */

/* } */

/* Print. */

void linkedlist_print(const LinkedList* ll, PrintFunc print_func)
{
    struct ll_node* curr_node = ll->head;

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

/* Internal. */

static struct ll_node* ll_node_new(size_t data_size, const void* data_ptr)
{
    struct ll_node* new_node = malloc(sizeof(struct ll_node));
    assert(new_node);

    new_node->data_ptr = malloc(data_size);
    assert(new_node->data_ptr);

    memcpy(new_node->data_ptr, data_ptr, data_size);
    new_node->next = NULL;

    return new_node;
}

static void ll_node_del(struct ll_node* node, FreeFunc free_func)
{
    free_func(node->data_ptr);
    free(node);
}
