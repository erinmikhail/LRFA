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
        pop_frint_list(list);
    }
}

void delete_list(LinkedList *list){
    erase_list(list);
}

void push_back_list(LinkedList *list, LIST_TYPE value){
    Uzel* new_uzel = (Uzel*)malloc(sizeof(Uzel));
    if (!new_uzel){
        fprinf(stderr, "Memory allocation failed\n");
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
        fprintf(stderr, "List is empty");
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

