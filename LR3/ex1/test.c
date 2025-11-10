#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include.h"

// Функция для захвата вывода printf
char* capture_output(int number, int r) {
    // Сохраняем стандартный вывод
    fflush(stdout);
    FILE* original_stdout = stdout;
    
    // Создаем временный файл для захвата вывода
    char* temp_filename = tmpnam(NULL);
    FILE* temp_file = fopen(temp_filename, "w+");
    
    if (temp_file == NULL) {
        return NULL;
    }
    
    // Перенаправляем stdout
    stdout = temp_file;
    
    // Вызываем тестируемую функцию
    decimalBase(number, r);
    
    // Восстанавливаем stdout
    fflush(temp_file);
    stdout = original_stdout;
    
    // Читаем результат из временного файла
    fseek(temp_file, 0, SEEK_END);
    long length = ftell(temp_file);
    fseek(temp_file, 0, SEEK_SET);
    
    char* result = malloc(length + 1);
    if (result) {
        fread(result, 1, length, temp_file);
        result[length] = '\0';
        
        // Удаляем символ новой строки если есть
        if (length > 0 && result[length - 1] == '\n') {
            result[length - 1] = '\0';
        }
    }
    
    fclose(temp_file);
    remove(temp_filename);
    return result;
}

// Макрос для тестирования
#define TEST(description, number, r, expected) \
    do { \
        char* actual = capture_output(number, r); \
        if (actual && strcmp(actual, expected) == 0) { \
            printf("✓ PASS: %s\n", description); \
            printf("  %d (r=%d) -> %s\n", number, r, actual); \
        } else { \
            printf("✗ FAIL: %s\n", description); \
            printf("  Expected: '%s'\n", expected); \
            printf("  Actual:   '%s'\n", actual ? actual : "NULL"); \
        } \
        free(actual); \
    } while(0)

void run_tests() {
    printf("ЗАПУСК ЮНИТ-ТЕСТОВ\n");
    printf("==================\n\n");
    
    // Тест 1: Ноль
    TEST("Ноль в двоичной", 0, 1, "0");
    
    // Тест 2: Положительные числа в разных системах
    TEST("13 в двоичной", 13, 1, "1101");
    TEST("42 в восьмеричной", 42, 3, "52");
    TEST("255 в шестнадцатеричной", 255, 4, "FF");
    TEST("1023 в 32-ричной", 1023, 5, "VV");
    
    // Тест 3: Отрицательные числа (ДОПОЛНИТЕЛЬНЫЙ КОД!)
    TEST("-10 в двоичной", -10, 1, "11111111111111111111111111110110");
    TEST("-42 в шестнадцатеричной", -42, 4, "FFFFFFD6");
    TEST("-255 в восьмеричной", -255, 3, "37777777401");
    
    // Тест 4: Граничные значения r
    TEST("r=1 (двоичная)", 15, 1, "1111");
    TEST("r=5 (32-ричная)", 31, 5, "V");
    
    // Тест 5: Некорректный r
    TEST("r=0 (ошибка)", 10, 0, "Error: r must be 1-5");
    TEST("r=6 (ошибка)", 10, 6, "Error: r must be 1-5");
    
    printf("\nТЕСТИРОВАНИЕ ЗАВЕРШЕНО\n");
}

int main() {
    run_tests();
    return 0;
}