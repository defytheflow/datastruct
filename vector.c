#include "vector.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static void vector_resize(Vector* v);

void vector_init(Vector* v, size_t capacity, size_t elem_size)
{
    v->elem_size = elem_size;
    v->size = 0;
    v->capacity = capacity;
    v->buffer = malloc(elem_size * capacity);
    if (!v->buffer) {
            fprintf(stderr, "vector_init: memory allocation error\n");
            exit(1);
    }
}

void vector_del(Vector* v)
{
    free(v->buffer);
}

int vector_size(const Vector* v)
{
    return v->size;
}

int vector_capacity(const Vector* v)
{
    return v->capacity;
}

void vector_push_back(Vector* v, const void* elem)
{
    if (v->capacity == v->size) {
            vector_resize(v);
    }

    void* dest = v->buffer + v->size * v->elem_size;
    memmove(dest, elem, v->elem_size);

    ++v->size;
}

void* vector_at(const Vector* v, size_t pos)
{
    if (pos < 0 || pos >= v->size) {
        fprintf(stderr, "vector_at: index out of bounds\n");
        return NULL;
    }
    return v->buffer + pos * v->elem_size;
}

void* vector_pop_back(Vector* v)
{
    if (v->size == 0) {
        fprintf(stderr, "vector_pop_back: vector is empty\n");
        return NULL;
    }
    --v->size;
    return v->buffer + (v->size * v->elem_size);
}

static void vector_resize(Vector* v)
{
    v->capacity = v->capacity * 2;
    v->buffer = realloc(v->buffer, v->capacity * v->elem_size);
    if (!v->buffer) {
        fprintf(stderr, "vector_resize: memory allocation error\n");
        exit(1);
    }
}
