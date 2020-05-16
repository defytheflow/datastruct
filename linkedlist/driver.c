#include "src/linkedlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void int_print(const void*);
void str_print(const void*);

void str_free(void*);

int main()
{
    LinkedList* ll = linkedlist_init(sizeof(char*), str_free);

    const char* strings[] = {
        "First",
        "Second",
        "Third",
        "Fourth",
        "Fifth",
        "Sixth",
    };

    char *string;
    for(size_t i = 0; i < 3; ++i) {
        string = strdup(strings[i]);
        linkedlist_push_back(ll, &string);
    }

    for(size_t i = 3; i < 6; ++i) {
        string = strdup(strings[i]);
        linkedlist_push_front(ll, &string);
    }

    linkedlist_print(ll, str_print);

    linkedlist_free(ll);
}

void int_print(const void* i)
{
    printf("%d", *(int*) i);
}

void str_print(const void* s)
{
    printf("'%s'", *(const char**) s);
}

void str_free(void* s)
{
    free(*(char**) s);
    free(s);
}
