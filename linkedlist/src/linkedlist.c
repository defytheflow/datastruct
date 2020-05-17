#include "../src/linkedlist.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static ListNode* listnode_create(size_t data_size, const void* data_ptr);

static void listnode_free(ListNode*, FreeFunc);

/*
 *                                Construction.
 */

LinkedList* linkedlist_create(LinkedList* list, size_t data_size, FreeFunc free_func)
{
    list->data_size = data_size;
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    list->free_func = (*free_func);
    return list;
}

/*
 *                                Destruction.
 */

void linkedlist_free(LinkedList* list)
{
    ListNode *current_node;

    while (list->head) {
        current_node = list->head;
        list->head = list->head->next;
        listnode_free(current_node, list->free_func);
    }
}

/*
 *                                  Indexing.
 */

void* linkedlist_get(const LinkedList* list, size_t pos)
{
    assert(pos < linkedlist_size(list));

    ListNode* current_node = list->head;

    for (size_t i = 0; i < pos; ++i, current_node = current_node->next)
        ;

    return current_node->data_ptr;
}

void linkedlist_set(const LinkedList* list, size_t pos, const void* data_ptr)
{
    assert(pos < linkedlist_size(list));

    ListNode* current_node = list->head;

    for (size_t i = 0; i < pos; ++i, current_node = current_node->next)
        ;

    memcpy(current_node->data_ptr, data_ptr, list->data_size);
}

/*
 *                                 Insertion.
 */

void linkedlist_push_back(LinkedList* list, const void* data_ptr)
{
    ListNode *new_node = listnode_create(list->data_size, data_ptr);

    if (linkedlist_is_empty(list))
        list->head = list->tail = new_node;
    else {
        list->tail->next = new_node;
        list->tail = new_node;
    }

    ++list->size;
}

void linkedlist_push_front(LinkedList* list, const void* data_ptr)
{
    ListNode *new_node = listnode_create(list->data_size, data_ptr);

    new_node->next = list->head;
    list->head = new_node;

    if (!list->tail)
        list->tail = list->head;

    ++list->size;
}

void linkedlist_insert(LinkedList* list, size_t pos, const void* data_ptr)
{
    assert(pos < linkedlist_size(list));

    ListNode* new_node = listnode_create(list->data_size, data_ptr);
    ListNode* current_node = list->head;

    for (size_t i = 0; i < pos - 1; ++i, current_node = current_node->next)
        ;

    new_node->next = current_node->next;
    current_node->next = new_node;

    ++list->size;
}

/*
 *                                  Removal.
 */

/* void* linkedlist_pop_back(LinkedList* list) */
/* { */
    /* assert(!linkedlist_is_empty(list)); */

/*     ListNode* prev_node, current_node; */
/*     void* data_ptr; */

/*     if (linkedlist_size(list) == 1) { */
/*         --list->size; */
/*         return list->head_node->data_ptr; */
/*     } */

/*     current_node = list->head; */
/*     data_ptr = NULL; */

/*     while (current_node->next->next) */
/*         current_node = current_node->next; */

/*     memcpy(data_ptr, current_node->data_ptr, list->data_size); */
/*     listnode_free(current_node, list->free_func); */

/*     return data_ptr; */
/* } */

/* void* linkedlist_pop_front(LinkedList* list) { */
/*     assert(!linkedlist_is_empty(list)); */

/* } */

/* void linkedlist_erase(LinkedList* list, size_t pos); */

/*
 *                                   Printing.
 */

void linkedlist_print(const LinkedList* list, PrintFunc print_func)
{
    ListNode* current_node = list->head;

    if (linkedlist_is_empty(list)) {
        puts("[]");
        return;
    }

    printf("[");
    while (current_node) {
        (*print_func)(current_node->data_ptr);
        if (current_node->next)
            printf(" -> ");
        current_node = current_node->next;
    }
    printf("]\n");
}

/*
 *                                  Internal.
 */

static ListNode* listnode_create(size_t data_size, const void* data_ptr)
{
    ListNode* new_node = malloc(sizeof(ListNode));
    assert(new_node);

    new_node->data_ptr = malloc(data_size);
    assert(new_node->data_ptr);

    memcpy(new_node->data_ptr, data_ptr, data_size);
    new_node->next = NULL;

    return new_node;
}

static void listnode_free(ListNode* node, FreeFunc free_func)
{
    if (free_func)
        free_func(node->data_ptr);
    else
        free(node->data_ptr);
    free(node);
}
