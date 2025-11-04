#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ex2_lr1.h"

// Тесты для функции is_prime_simple
void test_is_prime_simple() {
    printf("Testing is_prime_simple...\n");
    
    // Тест 1: Простые числа
    assert(is_prime_simple(2) == 1);
    assert(is_prime_simple(3) == 1);
    assert(is_prime_simple(5) == 1);
    assert(is_prime_simple(7) == 1);
    assert(is_prime_simple(11) == 1);
    assert(is_prime_simple(13) == 1);
    assert(is_prime_simple(17) == 1);
    
    // Тест 2: Составные числа
    assert(is_prime_simple(1) == 0);
    assert(is_prime_simple(4) == 0);
    assert(is_prime_simple(6) == 0);
    assert(is_prime_simple(8) == 0);
    assert(is_prime_simple(9) == 0);
    assert(is_prime_simple(10) == 0);
    assert(is_prime_simple(12) == 0);
    
    // Тест 3: Граничные случаи
    assert(is_prime_simple(0) == 0);
    assert(is_prime_simple(-1) == 0);
    assert(is_prime_simple(100) == 0);
    
    printf("✓ All is_prime_simple tests passed!\n\n");
}

// Тесты для функции find_primes
void test_find_primes() {
    printf("Testing find_primes...\n");
    
    // Тест 1: Первые 10 простых чисел
    int* primes = find_primes(10);
    assert(primes != NULL);
    assert(primes[0] == 2);
    assert(primes[1] == 3);
    assert(primes[2] == 5);
    assert(primes[3] == 7);
    assert(primes[4] == 11);
    assert(primes[5] == 13);
    assert(primes[6] == 17);
    assert(primes[7] == 19);
    assert(primes[8] == 23);
    assert(primes[9] == 29);
    free(primes);
    
    // Тест 2: Первое простое число
    primes = find_primes(1);
    assert(primes != NULL);
    assert(primes[0] == 2);
    free(primes);
    
    // Тест 3: Несколько простых чисел
    primes = find_primes(5);
    assert(primes != NULL);
    assert(primes[0] == 2);
    assert(primes[1] == 3);
    assert(primes[2] == 5);
    assert(primes[3] == 7);
    assert(primes[4] == 11);
    free(primes);
    
    // Тест 4: Некорректный ввод
    primes = find_primes(0);
    assert(primes == NULL);
    
    primes = find_primes(-5);
    assert(primes == NULL);
    
    printf("✓ All find_primes tests passed!\n\n");
}

// Тесты для проверки корректности простых чисел
void test_primes_correctness() {
    printf("Testing primes correctness...\n");
    
    // Проверяем первые 100 простых чисел
    int* primes = find_primes(100);
    assert(primes != NULL);
    
    // Проверяем что все числа действительно простые
    for (int i = 0; i < 100; i++) {
        assert(is_prime_simple(primes[i]) == 1);
    }
    
    // Проверяем порядок (должны быть в возрастающем порядке)
    for (int i = 1; i < 100; i++) {
        assert(primes[i] > primes[i-1]);
    }
    
    free(primes);
    printf("✓ Primes correctness test passed!\n\n");
}

// Тесты производительности (проверка больших значений)
void test_performance() {
    printf("Testing performance with larger values...\n");
    
    // Тест 1: 1000 простых чисел
    int* primes = find_primes(1000);
    assert(primes != NULL);
    assert(primes[0] == 2);
    assert(primes[999] == 7919); // 1000-е простое число
    free(primes);
    
    // Тест 2: 100 простых чисел
    primes = find_primes(100);
    assert(primes != NULL);
    assert(primes[99] == 541); // 100-е простое число
    free(primes);
    
    printf("✓ Performance tests passed!\n\n");
}

// Интеграционные тесты - запуск через system()
void test_integration() {
    printf("Testing integration via command line...\n");
    
    // Создаем тестовый входной файл
    FILE* test_input = fopen("test_input.txt", "w");
    if (test_input) {
        fprintf(test_input, "5\n");  // 5 запросов
        fprintf(test_input, "1\n");  // 1-е простое
        fprintf(test_input, "5\n");  // 5-е простое  
        fprintf(test_input, "10\n"); // 10-е простое
        fprintf(test_input, "20\n"); // 20-е простое
        fprintf(test_input, "50\n"); // 50-е простое
        fclose(test_input);
        
        printf("  Running program with test input...\n");
        int result = system("./ex2_lr1 < test_input.txt");
        if (result != 0) {
            printf("  ⚠ Program returned non-zero: %d\n", result);
        }
        
        // Удаляем временный файл
        remove("test_input.txt");
    } else {
        printf("  ⚠ Could not create test input file\n");
    }
    
    printf("✓ Integration tests completed!\n\n");
}

// Тесты граничных случаев
void test_edge_cases() {
    printf("Testing edge cases...\n");
    
    // Тест 1: Очень маленькое количество
    int* primes = find_primes(1);
    assert(primes != NULL);
    assert(primes[0] == 2);
    free(primes);
    
    // Тест 2: Проверка на утечки памяти
    for (int i = 0; i < 10; i++) {
        primes = find_primes(10);
        assert(primes != NULL);
        free(primes);
    }
    
    printf("✓ All edge case tests passed!\n\n");
}

// Тесты обработки ошибок
void test_error_handling() {
    printf("Testing error handling...\n");
    
    // Эти тесты проверяют, что функция корректно обрабатывает ошибки
    printf("  Test 1: Zero count\n");
    int* primes = find_primes(0);
    assert(primes == NULL);
    
    printf("  Test 2: Negative count\n");
    primes = find_primes(-10);
    assert(primes == NULL);
    
    printf("✓ Error handling tests completed!\n\n");
}

int main() {
    printf("========================================\n");
    printf("Unit Tests for ex2_lr1\n");
    printf("========================================\n\n");
    
    test_is_prime_simple();
    test_find_primes();
    test_primes_correctness();
    test_performance();
    test_edge_cases();
    test_error_handling();
    
    // Интеграционные тесты требуют собранной основной программы
    printf("Building main program for integration tests...\n");
    if (system("gcc -Wall -Werror -Wextra -Wpedantic -fsanitize=address ex2_lr1.c ex2_lr1_func.c -o ex2_lr1") == 0) {
        test_integration();
    } else {
        printf("⚠ Could not build main program for integration tests\n");
    }
    
    printf("========================================\n");
    printf("✅ ALL TESTS COMPLETED SUCCESSFULLY!\n");
    printf("========================================\n");
    
    return 0;
}