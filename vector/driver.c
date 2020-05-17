#include "src/vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int int_cmp(const void*, const void*);
void int_print(const void*);

int main()
{
    Vector v;
    vector_create(&v, sizeof(int), NULL);

    for (size_t i = 0; i < 15; ++i)
        vector_push_back(&v, &i);

    vector_print(&v, int_print);

    vector_clear(&v);

    vector_print(&v, int_print);

    vector_free(&v);
}

int int_cmp(const void* a_ptr, const void* b_ptr)
{
    int a_val = *(int*)a_ptr;
    int b_val = *(int*)b_ptr;

    if (a_val < b_val) return -1;
    else if (a_val > b_val) return 1;
    else return 0;
}

void int_print(const void* i)
{
    printf("%d", *(int*)i);
}
