#include "arraylist.h"

#include <stdio.h>
#include <stdlib.h>

int compare_int(const void* a_ptr, const void* b_ptr);
void print_int(const void* i);

int main()
{
    ArrayList* al = arraylist_new(sizeof(int));

    for (int i = 0; i < 10; ++i) {
        int val = rand() % 101;
        arraylist_push_back(al, &val);
    }

    arraylist_print(al, print_int);

    arraylist_del(al);
}

int compare_int(const void* a_ptr, const void* b_ptr)
{
    int a_val = *(int*)a_ptr;
    int b_val = *(int*)b_ptr;

    if (a_val < b_val)
        return -1;
    else if (a_val > b_val)
        return 1;
    else
        return 0;
}

void print_int(const void* i)
{
    printf("%d", *(int*)i);
}
