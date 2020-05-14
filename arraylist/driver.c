#include "arraylist.h"

#include <stdio.h>
#include <stdlib.h>

int int_cmp(const void* a_ptr, const void* b_ptr);
void int_print(const void* i);

int main()
{
    ArrayList* al = arraylist_new(sizeof(int));

    for (int i = 0; i < 100; ++i) {
        arraylist_push_back(al, &i);
    }

    arraylist_print(al, int_print);
    printf("%d\n", arraylist_is_sorted(al, int_cmp));
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
