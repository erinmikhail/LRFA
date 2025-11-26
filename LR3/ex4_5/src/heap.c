#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/heap.h"

Heap create_heap(size_t initial_capacity) {
    Heap h;
    h.data = (int*)malloc(initial_capacity * sizeof(int));
    if (!h.data) {
        fprintf(stderr, "Memory allocation failed for heap\n");
        h.size = 0;
        h.capacity = 0;
        return h;
    }
    h.size = 0;
    h.capacity = initial_capacity;
    return h;
}