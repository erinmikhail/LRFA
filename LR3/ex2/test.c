#include <stdio.h>
#include <string.h>
#include <assert.h>

#define VECTOR_TYPE char*
#include "vector.h"

// Функции для работы с char*
char* copy_string(char* str) {
    if (!str) return NULL;
    char* copy = malloc(strlen(str) + 1);
    strcpy(copy, str);
    return copy;
}

void delete_string(char* str) {
    free(str);
}

void test_create_and_basic_operations() {
    printf("Test 1: Create and basic operations\n");
    Vector vec = create_vector(2, copy_string, delete_string);
    
    assert(vec.size == 0);
    assert(vec.capacity == 2);
    assert(vec.CopyVoidPtr == copy_string);
    assert(vec.DeleteVoidPtr == delete_string);
    
    push_back_vector(&vec, "Hello");
    push_back_vector(&vec, "World");
    assert(vec.size == 2);
    
    push_back_vector(&vec, "Test");  // Должно увеличить capacity
    assert(vec.size == 3);
    assert(vec.capacity >= 3);
    
    erase_vector(&vec);
    printf("✓ Create and basic operations passed\n");
}

void test_get_and_delete_at() {
    printf("Test 2: Get and delete by index\n");
    Vector vec = create_vector(5, copy_string, delete_string);
    
    push_back_vector(&vec, "Apple");
    push_back_vector(&vec, "Banana");
    push_back_vector(&vec, "Cherry");
    
    assert(strcmp(get_at_vector(&vec, 0), "Apple") == 0);
    assert(strcmp(get_at_vector(&vec, 1), "Banana") == 0);
    assert(strcmp(get_at_vector(&vec, 2), "Cherry") == 0);
    
    delete_at_vector(&vec, 1);  // Удаляем "Banana"
    assert(vec.size == 2);
    assert(strcmp(get_at_vector(&vec, 0), "Apple") == 0);
    assert(strcmp(get_at_vector(&vec, 1), "Cherry") == 0);
    
    printf("✓ Get and delete by index passed\n");
    erase_vector(&vec);
}

void test_copy_operations() {
    printf("Test 3: Copy operations\n");
    Vector vec1 = create_vector(3, copy_string, delete_string);
    push_back_vector(&vec1, "One");
    push_back_vector(&vec1, "Two");
    
    // Копирование в существующий вектор
    Vector vec2 = create_vector(1, copy_string, delete_string);
    copy_vector(&vec2, &vec1);
    
    // Копирование в новый вектор
    Vector* vec3 = copy_vector_new(&vec1);
    assert(vec3->size == vec1.size);
    assert(vec3->capacity == vec1.capacity);
    
    printf("✓ Copy operations passed\n");
    
    erase_vector(&vec1);
    erase_vector(&vec2);
    delete_vector(vec3);
}

void test_comparison() {
    printf("Test 4: Vector comparison\n");
    Vector vec1 = create_vector(3, copy_string, delete_string);
    Vector vec2 = create_vector(3, copy_string, delete_string);
    
    push_back_vector(&vec1, "Same");
    push_back_vector(&vec1, "Data");
    push_back_vector(&vec2, "Same");
    push_back_vector(&vec2, "Data");
    
    push_back_vector(&vec1, "Extra");
    assert(!is_equal_vector(&vec1, &vec2)); // Теперь не равны
    
    printf("✓ Comparison passed\n");
    
    erase_vector(&vec1);
    erase_vector(&vec2);
}

void test_edge_cases() {
    printf("Test 5: Edge cases\n");
    
    // Создание с capacity = 0
    Vector vec = create_vector(0, copy_string, delete_string);
    assert(vec.capacity >= 1);  // Должно быть минимум 1
    
    // Получение невалидного индекса
    assert(get_at_vector(&vec, 100) == NULL);
    
    // Удаление невалидного индекса (не должно крашиться)
    delete_at_vector(&vec, 100);
    
    printf("✓ Edge cases passed\n");
    erase_vector(&vec);
}

int main() {
    printf("Starting Vector Library Tests...\n\n");
    
    test_create_and_basic_operations();
    test_get_and_delete_at();
    test_copy_operations();
    test_comparison();
    test_edge_cases();
    
    printf("\n All tests passed successfully!\n");
    return 0;
}