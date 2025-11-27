#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "heap.h"
#include "post_system.h"

void test_heap_operations() {
    printf("Testing heap operations...\n");
    
    Heap h = create_heap(5);
    assert(is_empty_heap(&h));
    assert(size_heap(&h) == 0);
    
    push_heap(&h, 5);
    push_heap(&h, 3);
    push_heap(&h, 8);
    push_heap(&h, 1);
    push_heap(&h, 4);
    
    assert(size_heap(&h) == 5);
    assert(peek_heap(&h) == 8);
    
    assert(pop_heap(&h) == 8);
    assert(pop_heap(&h) == 5);
    assert(pop_heap(&h) == 4);
    assert(pop_heap(&h) == 3);
    assert(pop_heap(&h) == 1);
    assert(is_empty_heap(&h));
    
    delete_heap(&h);
    printf("Heap tests passed\n");
}

void test_heap_build() {
    printf("Testing heap build...\n");
    
    int arr[] = {9, 5, 3, 7, 2, 8};
    Heap h = build_heap(arr, 6);
    
    assert(peek_heap(&h) == 9);
    assert(pop_heap(&h) == 9);
    assert(pop_heap(&h) == 8);
    assert(pop_heap(&h) == 7);
    assert(pop_heap(&h) == 5);
    assert(pop_heap(&h) == 3);
    assert(pop_heap(&h) == 2);
    
    delete_heap(&h);
    printf("Heap build tests passed\n");
}

void test_post_offices() {
    printf("Testing post offices...\n");
    
    PostSystem *system = create_post_system("test.log");
    assert(system != NULL);
    assert(system->office_count == 0);
    
    int connections[] = {2, 3};
    assert(add_post_office(system, 1, 5, connections, 2));
    assert(add_post_office(system, 2, 3, NULL, 0));
    assert(system->office_count == 2);
    
    PostOffice *office = find_office_by_id(system, 1);
    assert(office != NULL);
    assert(office->id == 1);
    assert(office->max_capacity == 5);
    
    assert(remove_post_office(system, 2));
    assert(system->office_count == 1);
    assert(find_office_by_id(system, 2) == NULL);
    
    delete_post_system(system);
    printf("Post office tests passed\n");
}

void test_letters() {
    printf("Testing letters...\n");
    
    PostSystem *system = create_post_system("test.log");
    add_post_office(system, 1, 5, NULL, 0);
    add_post_office(system, 2, 5, NULL, 0);
    
    int letter_id = add_letter(system, REGULAR, 10, 1, 2, "test");
    assert(letter_id == 1);
    assert(system->letter_count == 1);
    
    Letter *letter = find_letter_by_id(system, 1);
    assert(letter != NULL);
    assert(letter->priority == 10);
    assert(letter->state == IN_TRANSIT);
    
    assert(mark_letter_undeliverable(system, 1));
    assert(letter->state == UNDELIVERED);
    
    delete_post_system(system);
    printf("Letter tests passed\n");
}

void test_delivery() {
    printf("Testing delivery...\n");
    
    PostSystem *system = create_post_system("test.log");
    
    int connections1[] = {2};
    int connections2[] = {1};
    add_post_office(system, 1, 5, connections1, 1);
    add_post_office(system, 2, 5, connections2, 1);
    
    add_letter(system, REGULAR, 5, 1, 2, "delivery_test");
    
    Letter *letter = find_letter_by_id(system, 1);
    
    printf("Before first delivery: current_post_id=%d, state=%d\n", 
           letter->current_post_id, letter->state);
    
    process_mail_delivery(system);
    
    printf("After first delivery: current_post_id=%d, state=%d\n", 
           letter->current_post_id, letter->state);

    assert(letter->current_post_id == 2);
    assert(letter->state == IN_TRANSIT);
    
    printf("Before second delivery: current_post_id=%d, state=%d\n", 
           letter->current_post_id, letter->state);
    
    process_mail_delivery(system);
    
    printf("After second delivery: current_post_id=%d, state=%d\n", 
           letter->current_post_id, letter->state);

    assert(letter->state == DELIVERED);
    
    delete_post_system(system);
    printf("Delivery tests passed\n");
}

int main() {
    printf("Running unit tests...\n\n");
    
    test_heap_operations();
    test_heap_build();
    test_post_offices();
    test_letters();
    test_delivery();
    
    printf("\nAll tests passed!\n");
    return 0;
}