#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "list.h"
#include "liver.h"
#include "command.h"

void test_create_and_basic_list_operations() {
    printf("Test 1: Create list and basic operations\n");
    
    LinkedList list = create_list();
    assert(list.head == NULL);
    assert(list.tail == NULL);
    assert(list.size == 0);
    
    // Test push back
    struct tm birth_date = {0};
    birth_date.tm_mday = 15;
    birth_date.tm_mon = 5;
    birth_date.tm_year = 1990 - 1900;
    
    Liver liver1 = create_liver(1, "Smith", "John", "Michael", birth_date, 'M', 2500.50);
    push_back_list(&list, liver1);
    
    assert(list.size == 1);
    assert(list.head != NULL);
    assert(list.tail != NULL);
    assert(list.head == list.tail);
    
    // Test push front
    Liver liver2 = create_liver(2, "Johnson", "Mary", "Ann", birth_date, 'W', 3000.75);
    push_front_list(&list, liver2);
    
    assert(list.size == 2);
    assert(list.head->data.id == 2);
    assert(list.tail->data.id == 1);
    
    printf("✓ Create list and basic operations passed\n");
    delete_list(&list);
}

void test_pop_operations() {
    printf("Test 2: Pop operations\n");
    
    LinkedList list = create_list();
    struct tm birth_date = {0};
    birth_date.tm_mday = 10;
    birth_date.tm_mon = 3;
    birth_date.tm_year = 1985 - 1900;
    
    Liver liver1 = create_liver(1, "Brown", "Robert", "James", birth_date, 'M', 1800.00);
    Liver liver2 = create_liver(2, "Davis", "Sarah", "", birth_date, 'W', 2750.25);
    
    push_back_list(&list, liver1);
    push_back_list(&list, liver2);
    
    assert(list.size == 2);
    
    // Test pop back
    Liver popped_back = pop_back_list(&list);
    assert(popped_back.id == 2);
    assert(list.size == 1);
    assert(list.head->data.id == 1);
    assert(list.tail->data.id == 1);
    
    // Test pop front
    Liver popped_front = pop_front_list(&list);
    assert(popped_front.id == 1);
    assert(list.size == 0);
    assert(list.head == NULL);
    assert(list.tail == NULL);
    
    printf("✓ Pop operations passed\n");
}

void test_insert_and_delete_at() {
    printf("Test 3: Insert and delete at position\n");
    
    LinkedList list = create_list();
    struct tm birth_date = {0};
    birth_date.tm_mday = 20;
    birth_date.tm_mon = 7;
    birth_date.tm_year = 1978 - 1900;
    
    Liver liver1 = create_liver(1, "Wilson", "David", "", birth_date, 'M', 4100.80);
    Liver liver2 = create_liver(2, "Taylor", "Lisa", "Marie", birth_date, 'W', 3200.50);
    Liver liver3 = create_liver(3, "Anderson", "Mark", "Robert", birth_date, 'M', 2900.00);
    
    push_back_list(&list, liver1);
    push_back_list(&list, liver3);
    
    assert(list.size == 2);
    
    // Insert at middle
    insert_at_list(&list, 1, liver2);
    assert(list.size == 3);
    assert(get_at_list(&list, 0).id == 1);
    assert(get_at_list(&list, 1).id == 2);
    assert(get_at_list(&list, 2).id == 3);
    
    // Delete from middle
    delete_at_list(&list, 1);
    assert(list.size == 2);
    assert(get_at_list(&list, 0).id == 1);
    assert(get_at_list(&list, 1).id == 3);
    
    printf("✓ Insert and delete at position passed\n");
    delete_list(&list);
}

void test_sorted_insert_by_age() {
    printf("Test 4: Sorted insert by age\n");
    
    LinkedList list = create_list();
    struct tm birth_date1 = {0}; // Oldest
    birth_date1.tm_mday = 15;
    birth_date1.tm_mon = 5;
    birth_date1.tm_year = 1980 - 1900;
    
    struct tm birth_date2 = {0}; // Middle
    birth_date2.tm_mday = 22;
    birth_date2.tm_mon = 8;
    birth_date2.tm_year = 1975 - 1900;
    
    struct tm birth_date3 = {0}; // Youngest
    birth_date3.tm_mday = 10;
    birth_date3.tm_mon = 12;
    birth_date3.tm_year = 1990 - 1900;
    
    Liver liver1 = create_liver(1, "Old", "Person", "", birth_date1, 'M', 2500.50);
    Liver liver2 = create_liver(2, "Middle", "Person", "", birth_date2, 'W', 3000.75);
    Liver liver3 = create_liver(3, "Young", "Person", "", birth_date3, 'M', 1800.00);
    
    // Insert in random order - should be sorted by age (birth date)
    insert_sorted_by_age(&list, liver3); // Youngest
    insert_sorted_by_age(&list, liver1); // Oldest
    insert_sorted_by_age(&list, liver2); // Middle
    
    // Should be sorted: oldest first (liver2), then liver1, then liver3
    assert(list.size == 3);
    assert(get_at_list(&list, 0).id == 2); // Oldest (1975)
    assert(get_at_list(&list, 1).id == 1); // Middle (1980)
    assert(get_at_list(&list, 2).id == 3); // Youngest (1990)
    
    printf("✓ Sorted insert by age passed\n");
    delete_list(&list);
}

void test_stack_operations() {
    printf("Test 5: Stack operations\n");
    
    LinkedList stack = create_list();
    struct tm birth_date = {0};
    birth_date.tm_mday = 15;
    birth_date.tm_mon = 5;
    birth_date.tm_year = 1985 - 1900;
    
    Liver liver1 = create_liver(1, "Stack", "First", "", birth_date, 'M', 1000.00);
    Liver liver2 = create_liver(2, "Stack", "Second", "", birth_date, 'W', 2000.00);
    
    // Test push stack
    push_stack(&stack, liver1);
    push_stack(&stack, liver2);
    
    assert(stack.size == 2);
    
    // Test peek stack
    Liver top = peek_stack(&stack);
    assert(top.id == 2);
    
    // Test pop stack
    Liver popped = pop_stack(&stack);
    assert(popped.id == 2);
    assert(stack.size == 1);
    
    printf("✓ Stack operations passed\n");
    delete_list(&stack);
}

void test_queue_operations() {
    printf("Test 6: Queue operations\n");
    
    LinkedList queue = create_list();
    struct tm birth_date = {0};
    birth_date.tm_mday = 15;
    birth_date.tm_mon = 5;
    birth_date.tm_year = 1985 - 1900;
    
    Liver liver1 = create_liver(1, "Queue", "First", "", birth_date, 'M', 1000.00);
    Liver liver2 = create_liver(2, "Queue", "Second", "", birth_date, 'W', 2000.00);
    
    // Test enqueue
    enqueue(&queue, liver1);
    enqueue(&queue, liver2);
    
    assert(queue.size == 2);
    
    // Test peek queue
    Liver front = peek_queue(&queue);
    assert(front.id == 1);
    
    // Test dequeue
    Liver dequeued = dequeue(&queue);
    assert(dequeued.id == 1);
    assert(queue.size == 1);
    
    printf("✓ Queue operations passed\n");
    delete_list(&queue);
}

void test_liver_validation() {
    printf("Test 7: Liver validation\n");
    
    struct tm valid_birth_date = {0};
    valid_birth_date.tm_mday = 15;
    valid_birth_date.tm_mon = 5;
    valid_birth_date.tm_year = 1985 - 1900;
    
    // Test valid liver
    Liver valid_liver = create_liver(1, "Valid", "Name", "Patronymic", valid_birth_date, 'M', 2500.50);
    assert(is_valid_liver(&valid_liver) == 1);
    
    // Test invalid surname (empty)
    Liver invalid_surname = create_liver(2, "", "EmptySurname", "", valid_birth_date, 'M', 2500.50);
    assert(is_valid_liver(&invalid_surname) == 0);
    
    // Test invalid surname (non-alphabetic)
    Liver invalid_surname_chars = create_liver(3, "Invalid123", "Surname", "", valid_birth_date, 'M', 2500.50);
    assert(is_valid_liver(&invalid_surname_chars) == 0);
    
    // Test invalid name (empty)
    Liver invalid_name = create_liver(4, "Invalid", "", "", valid_birth_date, 'M', 2500.50);
    assert(is_valid_liver(&invalid_name) == 0);
    
    // Test invalid patronymic (non-alphabetic)
    Liver invalid_patronymic = create_liver(5, "Invalid", "Patronymic", "123", valid_birth_date, 'M', 2500.50);
    assert(is_valid_liver(&invalid_patronymic) == 0);
    
    // Test invalid gender
    Liver invalid_gender = create_liver(6, "Invalid", "Gender", "", valid_birth_date, 'X', 2500.50);
    assert(is_valid_liver(&invalid_gender) == 0);
    
    // Test invalid income
    Liver invalid_income = create_liver(7, "Invalid", "Income", "", valid_birth_date, 'M', -100.00);
    assert(is_valid_liver(&invalid_income) == 0);
    
    printf("✓ Liver validation passed\n");
}

void test_command_history() {
    printf("Test 8: Command history\n");
    
    CommandHistory history;
    init_command_history(&history);
    
    assert(history.count == 0);
    assert(history.current_index == 0);
    
    struct tm birth_date = {0};
    birth_date.tm_mday = 15;
    birth_date.tm_mon = 5;
    birth_date.tm_year = 1985 - 1900;
    
    Liver test_liver = create_liver(1, "Test", "History", "", birth_date, 'M', 2500.50);
    
    // Test add modification
    Modification mod;
    mod.type = CMD_ADD;
    mod.index = 0;
    mod.new_data = test_liver;
    
    add_modification(&history, mod);
    assert(history.count == 1);
    assert(history.current_index == 1);
    
    printf("✓ Command history passed\n");
}

void test_find_by_id() {
    printf("Test 9: Find liver by ID\n");
    
    LinkedList list = create_list();
    struct tm birth_date = {0};
    birth_date.tm_mday = 15;
    birth_date.tm_mon = 5;
    birth_date.tm_year = 1985 - 1900;
    
    Liver liver1 = create_liver(1, "Find", "First", "", birth_date, 'M', 1000.00);
    Liver liver2 = create_liver(2, "Find", "Second", "", birth_date, 'W', 2000.00);
    Liver liver3 = create_liver(3, "Find", "Third", "", birth_date, 'M', 3000.00);
    
    push_back_list(&list, liver1);
    push_back_list(&list, liver2);
    push_back_list(&list, liver3);
    
    // Test finding existing ID
    int found_index = find_liver_by_id(&list, 2);
    assert(found_index == 1);
    
    // Test finding non-existing ID
    int not_found_index = find_liver_by_id(&list, 999);
    assert(not_found_index == -1);
    
    printf("✓ Find liver by ID passed\n");
    delete_list(&list);
}

void test_edge_cases() {
    printf("Test 10: Edge cases\n");
    
    LinkedList list = create_list();
    
    // Test operations on empty list
    assert(find_liver_by_id(&list, 1) == -1);
    
    // Test invalid index access (should not crash)
    delete_at_list(&list, 100); // Should print error but not crash
    
    printf("✓ Edge cases passed\n");
    delete_list(&list);
}

int main() {
    printf("Starting Linked List Library Tests...\n\n");
    
    test_create_and_basic_list_operations();
    test_pop_operations();
    test_insert_and_delete_at();
    test_sorted_insert_by_age();
    test_stack_operations();
    test_queue_operations();
    test_liver_validation();
    test_command_history();
    test_find_by_id();
    test_edge_cases();
    
    printf("\n✅ All tests passed successfully!\n");
    return 0;
}