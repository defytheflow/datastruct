#include "src/vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int int_cmp(const void*, const void*);
void int_print(const void*);

void str_print(const void*);

int main()
{
    Vector* v = vector_create(sizeof(int), NULL);

    vector_free(v);
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

void str_print(const void* s)
{
    printf("'%s'", *(char**)s);
}
