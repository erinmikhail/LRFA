#include "vector.h"

Vector create_vector(size_t initial_capacity,
VECTOR_TYPE (*CopyFunc)(VECTOR_TYPE),
void (*DeleteFunc)(VECTOR_TYPE)){
    Vector v;
    v.size = 0;
    v.capacity = initial_capacity > 0 ? initial_capacity : 1;
    v.CopyVoidPtr = CopyFunc;
    v.DeleteVoidPtr = DeleteFunc;

    v.data = (VECTOR_TYPE*)malloc(v.capacity * sizeof(VECTOR_TYPE));
    return v;
}

void erase_vector(Vector *v) {
    if (v && v->data) {
         if (v->DeleteVoidPtr) {
            for (size_t i = 0; i < v->size; i++) {
                v->DeleteVoidPtr(v->data[i]);
            }
        }
        
        free(v->data);
        v->data = NULL;
        v->size = 0;
        v->capacity = 0;
    }
}

int is_equal_vector(const Vector *v1, const Vector *v2) {
    if (v1 == v2) return 1;
    if (!v1 || !v2) return 0;
    if (v1->size != v2->size) return 0;
    for (size_t i = 0; i < v1->size; i++) {
        if (v1->data[i] != v2->data[i]) {
            return 0;
        }
    }
    return 1;
}

void copy_vector(Vector *dest, const Vector *src) {
    if (!dest || !src) return;
    
    erase_vector(dest);

    dest->CopyVoidPtr = src->CopyVoidPtr;
    dest->DeleteVoidPtr = src->DeleteVoidPtr;
    dest->capacity = src->capacity;
    dest->size = src->size;

    dest->data = (VECTOR_TYPE*)malloc(dest->capacity * sizeof(VECTOR_TYPE));
    if (!dest->data) {
        dest->capacity = 0;
        dest->size = 0;
        return;
    }

    if (src->CopyVoidPtr) {
        for (size_t i = 0; i < src->size; i++) {
            dest->data[i] = src->CopyVoidPtr(src->data[i]);
        }
    } else {
        memcpy(dest->data, src->data, src->size * sizeof(VECTOR_TYPE));
    }
}

Vector *copy_vector_new(const Vector *src) {
    if (!src) return NULL;
    
    Vector *new_vec = (Vector*)malloc(sizeof(Vector));
    if (!new_vec) return NULL;

    new_vec->size = src->size;
    new_vec->capacity = src->capacity;
    new_vec->CopyVoidPtr = src->CopyVoidPtr;
    new_vec->DeleteVoidPtr = src->DeleteVoidPtr;

    new_vec->data = (VECTOR_TYPE*)malloc(new_vec->capacity * sizeof(VECTOR_TYPE));
    if (!new_vec->data) {
        free(new_vec);
        return NULL;
    }

    if (src->CopyVoidPtr) {
        for (size_t i = 0; i < src->size; i++) {
            new_vec->data[i] = src->CopyVoidPtr(src->data[i]);
        }
    } else {
        memcpy(new_vec->data, src->data, src->size * sizeof(VECTOR_TYPE));
    }
    
    return new_vec;
}