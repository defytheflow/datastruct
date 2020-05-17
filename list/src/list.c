#include "../src/list.h"

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

List* list_create(List* list, size_t data_size, FreeFunc free_func)
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

void list_free(List* list)
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

void* list_get(const List* list, size_t pos)
{
    assert(pos < list_size(list));

    ListNode* current_node = list->head;

    for (size_t i = 0; i < pos; ++i, current_node = current_node->next)
        ;

    return current_node->data_ptr;
}

void list_set(const List* list, size_t pos, const void* data_ptr)
{
    assert(pos < list_size(list));

    ListNode* current_node = list->head;

    for (size_t i = 0; i < pos; ++i, current_node = current_node->next)
        ;

    memcpy(current_node->data_ptr, data_ptr, list->data_size);
}

/*
 *                                 Insertion.
 */

void list_push_back(List* list, const void* data_ptr)
{
    ListNode *new_node = listnode_create(list->data_size, data_ptr);

    if (list_is_empty(list))
        list->head = list->tail = new_node;
    else {
        list->tail->next = new_node;
        list->tail = new_node;
    }

    ++list->size;
}

void list_push_front(List* list, const void* data_ptr)
{
    ListNode *new_node = listnode_create(list->data_size, data_ptr);

    new_node->next = list->head;
    list->head = new_node;

    if (!list->tail)
        list->tail = list->head;

    ++list->size;
}

void list_insert(List* list, size_t pos, const void* data_ptr)
{
    assert(pos < list_size(list));

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

/* void* list_pop_back(List* list, void* data_out) */
/* { */
/*     assert(!list_is_empty(list)); */

/*     ListNode* last_node = list->tail; */
/*     memcpy(data_out, last_node->data_ptr, list->data_size); */

/*     ListNode *current_node; */


/*     list->tail = current_node; */

/*     listnode_free(last_node, NULL); */

/*     return data_out; */
/* } */

/* void* list_pop_front(List* list) { */
/*     assert(!list_is_empty(list)); */

/* } */

/* void list_erase(List* list, size_t pos); */

/*
 *                                   Printing.
 */

void list_print(const List* list, PrintFunc print_func)
{
    ListNode* current_node = list->head;

    if (list_is_empty(list)) {
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
