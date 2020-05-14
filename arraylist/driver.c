#include "arraylist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int int_cmp(const void* a_ptr, const void* b_ptr);
void int_print(const void* i);

void str_print(const void* s);
void str_free(void* s);

int main()
{
    ArrayList* al = arraylist_new(sizeof(int), NULL);


    arraylist_del(al);
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

void str_free(void* s)
{
    free(*(char**)s);
}
