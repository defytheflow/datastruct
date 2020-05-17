#include "src/linkedlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void str_print(const void*);

void str_free(void*);

int main()
{
    LinkedList list;
    linkedlist_create(&list, sizeof(char*), str_free);

    const char* strings[] = {
        "First",
        "Second",
        "Third",
        "Fourth",
        "Fifth",
        "Sixth",
    };

    char *string;

    for(size_t i = 0; i < sizeof(strings) / sizeof(strings[0]); ++i) {
        string = strdup(strings[i]);
        linkedlist_push_back(&list, &string);
    }

    linkedlist_print(&list, str_print);
    /* char buffer[256]; */

    /* linkedlist_pop_back(&list, buffer); */

    /* char* last_string = *(char**) linkedlist_pop_back(&list); */

    linkedlist_free(&list);
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
