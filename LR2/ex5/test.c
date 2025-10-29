#include "include.h"
#include <assert.h>
#include <sys/stat.h>

// Тест для функции is_printAble
void test_is_printable() {
    printf("Testing is_printAble...\n");
    
    // Тестируем читаемые символы - должны возвращать true
    assert(is_printAble('a') == true);
    assert(is_printAble('Z') == true);
    assert(is_printAble('5') == true);
    assert(is_printAble('!') == true);
    assert(is_printAble('@') == true);
    
    // Тестируем НЕчитаемые символы - должны возвращать false
    assert(is_printAble(' ') == false);
    assert(is_printAble('\t') == false);
    assert(is_printAble('\n') == false);
    assert(is_printAble('\r') == false);
    assert(is_printAble('\0') == false);
    
    printf("✓ is_printAble tests passed\n");
}

// Тест для add_space с короткой строкой (ИСПРАВЛЕННЫЙ)
void test_add_space_short() {
    printf("Testing add_space with short line...\n");
    
    // Используем буфер достаточного размера
    char test_line[256] = "Hello world test";
    int original_len = strlen(test_line);
    
    add_space(test_line, original_len);
    
    // После выравнивания строка должна стать длиннее
    size_t new_len = strlen(test_line);
    assert(new_len > (size_t)original_len);
    assert(new_len == 80);  // Должна быть выровнена до 80 символов
    
    // Проверяем, что слова остались на своих местах
    assert(strstr(test_line, "Hello") != NULL);
    assert(strstr(test_line, "world") != NULL);
    assert(strstr(test_line, "test") != NULL);
    
    printf("✓ Short line spacing test passed\n");
}

// Тест для add_space с уже длинной строкой
void test_add_space_already_long() {
    printf("Testing add_space with already long line...\n");
    
    // Создаем строку длиннее 80 символов
    char long_line[256];
    memset(long_line, 'a', 85);
    long_line[85] = '\0';
    
    int original_len = strlen(long_line);
    add_space(long_line, original_len);
    
    // Длина не должна измениться (функция должна выйти сразу)
    size_t new_len = strlen(long_line);
    assert(new_len == (size_t)original_len);
    
    printf("✓ Long line spacing test passed\n");
}

// Тест для add_space без пробелов
void test_add_space_no_spaces() {
    printf("Testing add_space with no spaces...\n");
    
    char test_line[256] = "VeryLongWordWithoutAnySpaces";
    int original_len = strlen(test_line);
    
    add_space(test_line, original_len);
    
    // Длина не должна измениться (нет пробелов для добавления)
    size_t new_len = strlen(test_line);
    assert(new_len == (size_t)original_len);
    
    printf("✓ No spaces test passed\n");
}

// Тест для process_line с короткой строкой
void test_process_line_short() {
    printf("Testing process_line with short line...\n");
    
    // Создаем временный файл для вывода
    FILE* output = tmpfile();
    const char* input_line = "This is a short line.\n";
    
    process_line(input_line, output);
    
    // Проверяем результат
    rewind(output);
    char result[256];
    fgets(result, sizeof(result), output);
    
    // Убираем \n для сравнения
    result[strcspn(result, "\n")] = '\0';
    
    // Короткая строка должна остаться без изменений
    assert(strcmp(result, "This is a short line.") == 0);
    
    fclose(output);
    printf("✓ Short line processing test passed\n");
}

// Тест для process_line с длинной строкой
void test_process_line_long() {
    printf("Testing process_line with long line...\n");
    
    FILE* output = tmpfile();
    const char* input_line = "This is a very long line that should be split into multiple lines because it exceeds the eighty character limit by a significant margin and needs proper handling.\n";
    
    process_line(input_line, output);
    
    // Проверяем, что строка разбита на несколько строк
    rewind(output);
    char line[256];
    int line_count = 0;
    
    while (fgets(line, sizeof(line), output)) {
        line_count++;
    }
    
    // Длинная строка должна быть разбита на несколько строк
    assert(line_count > 1);
    
    // Проверяем первую строку
    rewind(output);
    fgets(line, sizeof(line), output);
    line[strcspn(line, "\n")] = '\0';
    
    // Первая строка должна быть длиной 80 символов
    assert(strlen(line) == 80);
    
    // Проверяем, что строка не обрывается посередине слова
    assert(line[79] != ' '); // Последний символ не пробел
    
    fclose(output);
    printf("✓ Long line processing test passed\n");
}

// Тест для process_line с пустой строкой
void test_process_line_empty() {
    printf("Testing process_line with empty line...\n");
    
    FILE* output = tmpfile();
    const char* input_line = "\n";
    
    process_line(input_line, output);
    
    // Проверяем результат
    rewind(output);
    char result[256];
    fgets(result, sizeof(result), output);
    
    // Пустая строка должна остаться пустой
    result[strcspn(result, "\n")] = '\0';
    assert(strlen(result) == 0);
    
    fclose(output);
    printf("✓ Empty line processing test passed\n");
}

// Тест для format_text (интеграционный тест)
void test_format_text() {
    printf("Testing format_text...\n");
    
    // Создаем временные файлы
    FILE* input = tmpfile();
    FILE* output = tmpfile();
    
    // Записываем тестовые данные во входной файл
    fprintf(input, "First line.\n");
    fprintf(input, "This is a very long line that needs to be split into multiple lines because it's too long for the eighty character limit and requires proper formatting.\n");
    fprintf(input, "Last line.\n");
    rewind(input);
    
    format_text(input, output);
    
    // Проверяем результат
    rewind(output);
    char buffer[256];
    int line_count = 0;
    
    while (fgets(buffer, sizeof(buffer), output)) {
        line_count++;
        buffer[strcspn(buffer, "\n")] = '\0';
        
        // Проверяем, что каждая строка имеет длину <= 80 символов
        size_t line_len = strlen(buffer);
        assert(line_len <= 80);
        
        // Проверяем, что строка начинается с читаемого символа (если не пустая)
        if (line_len > 0) {
            assert(is_printAble(buffer[0]));
        }
    }
    
    // Должно быть как минимум 3 строки
    assert(line_count >= 3);
    
    fclose(input);
    fclose(output);
    printf("✓ format_text test passed\n");
}

// Тест пограничных случаев
void test_edge_cases() {
    printf("Testing edge cases...\n");
    
    // Тест со строкой ровно 80 символов
    FILE* output = tmpfile();
    char exact_80[256];
    memset(exact_80, 'a', 80);
    exact_80[80] = '\n';
    exact_80[81] = '\0';
    
    process_line(exact_80, output);
    rewind(output);
    
    char result[256];
    fgets(result, sizeof(result), output);
    result[strcspn(result, "\n")] = '\0';
    assert(strlen(result) == 80);
    
    fclose(output);
    printf("✓ Edge cases tests passed\n");
}

// Главная функция запуска всех тестов
void runAllTests() {
    printf("=== UNIT TESTS FOR TEXT FORMATTER ===\n\n");
    
    test_is_printable();
    test_add_space_short();
    test_add_space_already_long();
    test_add_space_no_spaces();
    test_process_line_short();
    test_process_line_long();
    test_process_line_empty();
    test_format_text();
    test_edge_cases();
    
    printf("\n ALL TESTS PASSED! \n");
}