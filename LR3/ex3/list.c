#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

LinkedList create_list(void){
    LinkedList list;
    list.head = NULL;
    list.tail = NULL;
    list.size = 0;
    return list;
}

void erase_list(LinkedList *list){
    while (list->size > 0){
        pop_front_list(list);
    }
}

void delete_list(LinkedList *list){
    erase_list(list);
}

void push_back_list(LinkedList *list, LIST_TYPE value){
    Uzel* new_uzel = (Uzel*)malloc(sizeof(Uzel));
    if (!new_uzel){
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    new_uzel->data = value;
    new_uzel->next = NULL;
    new_uzel->prev = list->tail;

    if (list->tail){
        list->tail->next = new_uzel;
    } else {
        list->head = new_uzel;
    }

    list->tail = new_uzel;
    list->size++;
}

void push_front_list(LinkedList* list, LIST_TYPE value) {
    Uzel* new_uzel = (Uzel*)malloc(sizeof(Uzel));
    if (!new_uzel) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    new_uzel->data = value;
    new_uzel->prev = NULL;
    new_uzel->next = list->head;
    
    if (list->head) {
        list->head->prev = new_uzel;
    } else {
        list->tail = new_uzel;
    }
    
    list->head = new_uzel;
    list->size++;
}

LIST_TYPE pop_back_list(LinkedList *list){
    if (list->size == 0){
        fprintf(stderr, "List is empty");
        exit(1);
    }
    
    Uzel *last_uzel = list->tail;
    LIST_TYPE value = last_uzel->data;

    if (list->head == list->tail){
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->tail = last_uzel->prev;
        list->tail->next = NULL;
    }

    free(last_uzel);
    list->size--;
    return value;
}

LIST_TYPE pop_front_list(LinkedList *list){
    if (list->size == 0){
        fprintf(stderr, "List is empty\n");
        exit(1);
    }

    Uzel *first_uzel = list->head;
    LIST_TYPE value = first_uzel->data;

    if (list->head == list->tail){
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = first_uzel->next;
        list->head->prev = NULL;
    }

    free(first_uzel);
    list->size--;
    return value;
}

void insert_at_list(LinkedList *list, size_t index, LIST_TYPE  value){
    if (index > list->size){
        fprintf(stderr, "Index out of bounds\n");
        return;
    }

    if (index == 0){
        push_front_list(list, value);
        return;
    }

    if (index == list->size){
        push_front_list(list,value);
        return;
    }

    Uzel* current = list->head;
    for (size_t i = 0; i < index; i ++){
        current = current->next;
    }

    Uzel *new_uzel = (Uzel*)malloc(sizeof(Uzel));
    if (!new_uzel){
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    new_uzel->data = value;
    new_uzel->prev = current->prev;
    new_uzel->next = current;

    current->prev->next = new_uzel;
    current->prev = new_uzel;

    list->size++;
}

LIST_TYPE get_at_list(const LinkedList* list, size_t index) {
    if (index >= list->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(1);
    }
    
    Uzel* current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    return current->data;
}

void delete_at_list(LinkedList *list, size_t index){
    if (index >= list->size){
        fprintf(stderr, "index out of bounds\n");
        return;
    }

    if (index == 0){
        pop_front_list(list);
        return;
    }

    Uzel* current = list->head;
    for (size_t i = 0; i < index; i++){
        current = current->next;
    }

    current->prev->next = current->next;
    current->next->prev = current->prev;

    free(current);
    list->size--;
}

void push_stack(LinkedList *stack, LIST_TYPE value){
    push_back_list(stack, value);
}

LIST_TYPE pop_stack(LinkedList *stack){
    return pop_back_list(stack);
}

LIST_TYPE peek_stack(const LinkedList *stack){
    if (stack->size == 0){
        fprintf(stderr, "stack is empty\n");
        exit(1);
    }

    return stack->tail->data;
}

void enqueue(LinkedList *queue, LIST_TYPE value){
    push_back_list(queue, value);
}

LIST_TYPE dequeue(LinkedList *queue){
    return pop_front_list(queue);
}

LIST_TYPE peek_queue(const LinkedList *queue){
    if (queue->size == 0){
        fprintf(stderr, "queue is empty\n");
        exit(1);
    }

    return queue->head->data;
}

void insert_sorted_by_age(LinkedList *list, LIST_TYPE value){
    if (list->size == 0){
        push_back_list(list, value);
        return;
    }

    Uzel *current = list->head;
    size_t index = 0;

    while (current){
        if (compare_liver_age(&value, current->data) <= 0){
            insert_at_list(list, index, value);
            return;
        }

        current = current->next;
        index++;
    }

    push_back_list(list, value);
}

int find_liver_by_id(const LinkedList* list, unsigned int id) {
    Uzel* current = list->head;
    int index = 0;
    
    while (current) {
        if (current->data.id == id) {
            return index;
        }
        current = current->next;
        index++;
    }
    
    return -1;
}


void print_list(const LinkedList* list) {
    printf("List size: %zu\n", list->size);
    Uzel* current = list->head;
    int index = 0;
    
    while (current) {
        printf("[%d] ", index++);
        print_liver(&current->data);
        current = current->next;
    }
}

int is_equal_list(const LinkedList* l1, const LinkedList* l2) {
    if (l1->size != l2->size) {
        return 0;
    }
    
    Uzel* uzel1 = l1->head;
    Uzel* uzel2 = l2->head;
    
    while (uzel1 && uzel2) {
        if (memcmp(&uzel1->data, &uzel2->data, sizeof(LIST_TYPE)) != 0) {
            return 0;
        }
        uzel1 = uzel1->next;
        uzel2 = uzel2->next;
    }
    
    return 1;
}