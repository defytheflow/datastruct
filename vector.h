#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct {
    size_t elem_size;
    size_t size;
    size_t capacity;
    void* buffer;
} Vector;

void vector_init(Vector* v, size_t capacity, size_t elem_size);

void vector_del(Vector* v);

int vector_size(const Vector* v);

int vector_capacity(const Vector* v);

void vector_push_back(Vector* v, const void* elem);

void* vector_at(const Vector* v, size_t pos);

void* vector_pop_back(Vector* v);

void vector_clear(Vector* v);

#endif /* VECTOR_H */
