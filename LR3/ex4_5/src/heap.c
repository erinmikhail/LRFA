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

void delete_heap(Heap *h){
    if (h && h->data){
        free(h->data);
        h->data = NULL;
        h->size = 0;
        h->capacity = 0;
    }
}

int is_empty_heap(const Heap *h){
    return h == NULL || h->size == 0;
}

size_t size_heap(const Heap *h){
    return h ? h->size : 0;
}

int peek_heap(const Heap *h){
    if (is_empty_heap(h)){
        fprintf(stderr, "Heap id empty\n");
        return -1;
    }
    return h->data[0];
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(Heap *h, int index){
    while (index > 0){
        int parent = (index -1) / 2;
        if (h->data[parent] <= h->data[index]){
            break;
        }
        swap(&h->data[parent], &h->data[index]);
        index = parent;
    }
}

void heapify_down(Heap *h, int index){
    int size = h->size;
    while (1){
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size && h->data[left] < h->data[smallest]){
            smallest = left;
        }

        if (right < size && h->data[right] < h->data[smallest]){
            smallest = right;
        }

        if (smallest == index){
            break;
        }

        swap(&h->data[index], &h->data[smallest]);
        index = smallest;
    }
}

