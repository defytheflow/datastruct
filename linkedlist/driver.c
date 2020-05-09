#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_int(const void* i);
void print_str(const void* s);

void str_free(void* s);

int main()
{
    LinkedList* ll = linkedlist_new(sizeof(char*), str_free);

    const char *names[] = { "Jane", "David", "Kevin", "Michael", "Craig", "Jimi" };

    char *name;
    for(int i = 0; i < sizeof(names) / sizeof(char*); ++i) {
        name = strdup(names[i]);
        linkedlist_push_back(ll, &name);
    }

    linkedlist_print(ll, print_str);

    linkedlist_delete(ll);

    return 0;
}

void print_int(const void* i)
{
    printf("%d", *(int*)i);
}

void print_str(const void* s)
{
    printf("'%s'", *(const char**)s);
}

void str_free(void* s)
{
    free(*(char**)s);
}
