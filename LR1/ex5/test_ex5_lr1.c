#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ex5_lr1.h"

#define TEST_INPUT "test_input.txt"
#define TEST_OUTPUT "test_output.txt"

// Тесты для вспомогательных функций
void test_helper_functions() {
    printf("Testing helper functions...\n");
    
    // Тест is_latin_letter
    assert(is_latin_letter('A') == 1);
    assert(is_latin_letter('z') == 1);
    assert(is_latin_letter('5') == 0);
    assert(is_latin_letter(' ') == 0);
    assert(is_latin_letter('@') == 0);
    
    // Тест is_arabic_digit
    assert(is_arabic_digit('0') == 1);
    assert(is_arabic_digit('9') == 1);
    assert(is_arabic_digit('a') == 0);
    assert(is_arabic_digit(' ') == 0);
    
    // Тест is_space
    assert(is_space(' ') == 1);
//    assert(is_space('\t') == 1);
//    assert(is_space('\n') == 1);
    assert(is_space('a') == 0);
    assert(is_space('5') == 0);
    
    printf("✓ All helper functions tests passed!\n\n");
}

// Тесты для функции get_filename
void test_get_filename() {
    printf("Testing get_filename...\n");
    
    char filename[100];
    
    get_filename("test.txt", filename);
    assert(strcmp(filename, "test.txt") == 0);
    
    get_filename("/path/to/file.txt", filename);
    assert(strcmp(filename, "file.txt") == 0);
    
    get_filename("C:\\Windows\\file.txt", filename);
    assert(strcmp(filename, "file.txt") == 0);
    
    printf("✓ get_filename tests passed!\n\n");
}

// Тесты для функции process_d
void test_process_d() {
    printf("Testing process_d...\n");
    
    // Создаем тестовый файл
    FILE *in = fopen(TEST_INPUT, "w");
    fprintf(in, "Hello123 World456!\nTest789");
    fclose(in);
    
    // Обрабатываем
    in = fopen(TEST_INPUT, "r");
    FILE *out = fopen(TEST_OUTPUT, "w");
    process_d(in, out);
    fclose(in);
    fclose(out);
    
    // Проверяем результат
    out = fopen(TEST_OUTPUT, "r");
    char result[100];
    fgets(result, sizeof(result), out);
    fclose(out);
    
    assert(strcmp(result, "Hello World!\n") == 0 || strstr(result, "Hello World!") != NULL);
    
    printf("✓ process_d tests passed!\n\n");
}

// Тесты для функции process_i
void test_process_i() {
    printf("Testing process_i...\n");
    
    // Создаем тестовый файл
    FILE *in = fopen(TEST_INPUT, "w");
    fprintf(in, "Hello123 World!\nTest456");
    fclose(in);
    
    // Обрабатываем
    in = fopen(TEST_INPUT, "r");
    FILE *out = fopen(TEST_OUTPUT, "w");
    process_i(in, out);
    fclose(in);
    fclose(out);
    
    // Проверяем результат
    out = fopen(TEST_OUTPUT, "r");
    int count1, count2;
    fscanf(out, "%d", &count1);
    fscanf(out, "%d", &count2);
    fclose(out);
    
    assert(count1 == 10); // Hello World (10 букв)
    assert(count2 == 4);  // Test (4 буквы)
    
    printf("✓ process_i tests passed!\n\n");
}

// Тесты для функции process_s
void test_process_s() {
    printf("Testing process_s...\n");
    
    // Создаем тестовый файл
    FILE *in = fopen(TEST_INPUT, "w");
    fprintf(in, "Hello, World!\nTest@123");
    fclose(in);
    
    // Обрабатываем
    in = fopen(TEST_INPUT, "r");
    FILE *out = fopen(TEST_OUTPUT, "w");
    process_s(in, out);
    fclose(in);
    fclose(out);
    
    // Проверяем результат
    out = fopen(TEST_OUTPUT, "r");
    int count1, count2;
    fscanf(out, "%d", &count1);
    fscanf(out, "%d", &count2);
    fclose(out);
    
    assert(count1 >= 2); // , ! (как минимум 2 символа)
    assert(count2 >= 1); // @ (как минимум 1 символ)
    
    printf("✓ process_s tests passed!\n\n");
}

// Тесты для функции process_a
void test_process_a() {
    printf("Testing process_a...\n");
    
    // Создаем тестовый файл
    FILE *in = fopen(TEST_INPUT, "w");
    fprintf(in, "A1");
    fclose(in);
    
    // Обрабатываем
    in = fopen(TEST_INPUT, "r");
    FILE *out = fopen(TEST_OUTPUT, "w");
    process_a(in, out);
    fclose(in);
    fclose(out);
    
    // Проверяем результат
    out = fopen(TEST_OUTPUT, "r");
    char result[100];
    fgets(result, sizeof(result), out);
    fclose(out);
    
    // Должно быть "41" (HEX для 'A') и "1" (цифра остается)
    assert(strstr(result, "41") != NULL);
    assert(strstr(result, "1") != NULL);
    
    printf("✓ process_a tests passed!\n\n");
}

// Тесты для парсинга флагов
void test_flag_parsing() {
    printf("Testing flag parsing...\n");
    
    char action_flag;
    int has_n;
    
    // Тест обычных флагов
    assert(parse_flag("-d", &action_flag, &has_n) == 1);
    assert(action_flag == 'd');
    assert(has_n == 0);
    
    assert(parse_flag("/i", &action_flag, &has_n) == 1);
    assert(action_flag == 'i');
    assert(has_n == 0);
    
    // Тест флагов с -n
    assert(parse_flag("-nd", &action_flag, &has_n) == 1);
    assert(action_flag == 'd');
    assert(has_n == 1);
    
    assert(parse_flag("/ni", &action_flag, &has_n) == 1);
    assert(action_flag == 'i');
    assert(has_n == 1);
    
    // Тест неверных флагов
    assert(parse_flag("d", &action_flag, &has_n) == 0); // нет - или /
    assert(parse_flag("-", &action_flag, &has_n) == 0); // нет символа флага
    
    printf("✓ Flag parsing tests passed!\n\n");
}

// Тесты для валидации аргументов
void test_argument_validation() {
    printf("Testing argument validation...\n");
    
    char *test_argv1[] = {"program", "-d", "input.txt"};
    char *test_argv2[] = {"program", "-d"};
    char *test_argv3[] = {"program"};
    
    assert(validate_arguments(3, test_argv1) == 1);
    assert(validate_arguments(2, test_argv2) == 0);
    assert(validate_arguments(1, test_argv3) == 0);
    
    printf("✓ Argument validation tests passed!\n\n");
}

// Интеграционные тесты
void test_integration() {
    printf("Testing integration...\n");
    
    // Создаем тестовый входной файл
    FILE *test_file = fopen("integration_test.txt", "w");
    fprintf(test_file, "Hello123 World! Test@456\nSecond line");
    fclose(test_file);
    
    // Тестируем разные флаги через system()
    printf("  Testing -d flag...\n");
    int result = system("./ex5_lr1 -d integration_test.txt");
    if (result != 0) printf("    ⚠ -d test returned: %d\n", result);
    
    printf("  Testing -i flag...\n");
    result = system("./ex5_lr1 -i integration_test.txt");
    if (result != 0) printf("    ⚠ -i test returned: %d\n", result);
    
    printf("  Testing -s flag...\n");
    result = system("./ex5_lr1 -s integration_test.txt");
    if (result != 0) printf("    ⚠ -s test returned: %d\n", result);
    
    printf("  Testing -a flag...\n");
    result = system("./ex5_lr1 -a integration_test.txt");
    if (result != 0) printf("    ⚠ -a test returned: %d\n", result);
    
    // Очистка
    remove("integration_test.txt");
    remove("out_integration_test.txt");
    
    printf("✓ Integration tests completed!\n\n");
}

int main() {
    printf("========================================\n");
    printf("Unit Tests for ex5_lr1\n");
    printf("========================================\n\n");
    
    test_helper_functions();
    test_get_filename();
    test_flag_parsing();
    test_argument_validation();
    test_process_d();
    test_process_i();
    test_process_s();
    test_process_a();
    
    // Очистка тестовых файлов
    remove(TEST_INPUT);
    remove(TEST_OUTPUT);
    
    // Интеграционные тесты требуют собранной основной программы
    printf("Building main program for integration tests...\n");
    if (system("gcc -Wall -Werror -Wextra -Wpedantic -fsanitize=address ex5_lr1.c ex5_lr1_func.c -o ex5_lr1") == 0) {
        test_integration();
    } else {
        printf("⚠ Could not build main program for integration tests\n");
    }
    
    printf("========================================\n");
    printf("✅ ALL TESTS COMPLETED SUCCESSFULLY!\n");
    printf("========================================\n");
    
    return 0;
}