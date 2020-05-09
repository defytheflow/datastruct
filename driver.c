#include "arraylist.h"

#include <stdio.h>
#include <stdlib.h>

int compare_int(const void* a_ptr, const void* b_ptr);
void print_int(const void* i);

int main()
{
    ArrayList* al1 = arraylist_new(sizeof(int));

    for (int i = 0; i < 10; ++i) {
        int val = rand() % 101;
        arraylist_push(al1, &val);
    }

    arraylist_info(al1);
    arraylist_print(al1, print_int);

    int val = 54;
    arraylist_remove(al1, &val);
    arraylist_erase(al1, arraylist_size(al1) - 2);

    arraylist_print(al1, print_int);
    arraylist_info(al1);

    arraylist_del(al1);

    return 0;
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
