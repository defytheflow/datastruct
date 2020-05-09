#include "vector.h"

#include <stdio.h>

int main()
{
    Vector v;
    vector_init(&v, 10, sizeof(const char*));

    vector_push_back(&v, "dog");
    vector_push_back(&v, "cat");
    vector_push_back(&v, "elephant");

    for (int i = 0; i < vector_size(&v); ++i) {
        printf("%s\n", (const char*)vector_at(&v, i));
    }

    vector_del(&v, NULL);
    return 0;
}
