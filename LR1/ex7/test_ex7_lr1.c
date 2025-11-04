#include "ex7_lr1.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

// Тесты для char_to_value
void test_char_to_value() {
    printf("Testing char_to_value...\n");
    
    // Цифры
    assert(char_to_value('0') == 0);
    assert(char_to_value('5') == 5);
    assert(char_to_value('9') == 9);
    
    // Заглавные буквы (A-Z допустимы в 36-ричной системе)
    assert(char_to_value('A') == 10);
    assert(char_to_value('F') == 15);
    assert(char_to_value('G') == 16);
    assert(char_to_value('Z') == 35);
    
    // Строчные буквы
    assert(char_to_value('a') == 10);
    assert(char_to_value('f') == 15);
    assert(char_to_value('g') == 16);
    assert(char_to_value('z') == 35);
    
    // Недопустимые символы (все что после Z)
    assert(char_to_value(' ') == INVALID_CHAR_VALUE);
    assert(char_to_value('@') == INVALID_CHAR_VALUE);
    assert(char_to_value('[') == INVALID_CHAR_VALUE);
    assert(char_to_value('{') == INVALID_CHAR_VALUE);
    
    printf("char_to_value tests passed!\n");
}

// Тесты для min_base
void test_min_base() {
    printf("Testing min_base...\n");
    
    // Двоичные числа
    assert(min_base("0") == 2);
    assert(min_base("1") == 2);
    assert(min_base("101") == 2);
    
    // Числа с разными основаниями
    assert(min_base("2") == 3);      // макс. цифра 2 → основание 3
    assert(min_base("3") == 4);      // макс. цифра 3 → основание 4
    assert(min_base("7") == 8);      // макс. цифра 7 → основание 8
    assert(min_base("8") == 9);      // макс. цифра 8 → основание 9
    assert(min_base("9") == 10);     // макс. цифра 9 → основание 10
    assert(min_base("123") == 4);    // макс. цифра 3 → основание 4
    
    // 16-ричные числа
    assert(min_base("A") == 11);     // A=10 → основание 11
    assert(min_base("F") == 16);     // F=15 → основание 16
    assert(min_base("G") == 17);     // G=16 → основание 17
    assert(min_base("1F") == 16);    // макс. цифра F=15 → основание 16
    
    // 36-ричные числа
    assert(min_base("Z") == 36);     // Z=35 → основание 36
    assert(min_base("10Z") == 36);   // макс. цифра Z=35 → основание 36
    
    // Числа с ведущими нулями
    assert(min_base("001") == 2);
    assert(min_base("00A") == 11);
    assert(min_base("00G") == 17);
    
    // Недопустимые символы
    assert(min_base("[") == INVALID_CHAR_VALUE);
    assert(min_base("12!") == INVALID_CHAR_VALUE);
    assert(min_base("ABC@") == INVALID_CHAR_VALUE);
    
    printf("min_base tests passed!\n");
}

// Тесты для remove_leading_zeros
void test_remove_leading_zeros() {
    printf("Testing remove_leading_zeros...\n");
    
    char buffer[BUFFER_SIZE];
    
    // Обычные случаи
    strcpy(buffer, "00123");
    remove_leading_zeros(buffer);
    assert(strcmp(buffer, "123") == 0);
    
    strcpy(buffer, "100");
    remove_leading_zeros(buffer);
    assert(strcmp(buffer, "100") == 0);
    
    // Крайние случаи
    strcpy(buffer, "0000");
    remove_leading_zeros(buffer);
    assert(strcmp(buffer, "0") == 0);
    
    strcpy(buffer, "0");
    remove_leading_zeros(buffer);
    assert(strcmp(buffer, "0") == 0);
    
    strcpy(buffer, "A0B");
    remove_leading_zeros(buffer);
    assert(strcmp(buffer, "A0B") == 0);
    
    // Буквенные числа
    strcpy(buffer, "00G");
    remove_leading_zeros(buffer);
    assert(strcmp(buffer, "G") == 0);
    
    printf("remove_leading_zeros tests passed!\n");
}

// Тесты для str_to_base10
void test_str_to_base10() {
    printf("Testing str_to_base10...\n");
    
    long long result;
    StatusCode status;
    
    // Двоичная система
    status = str_to_base10("101", 2, &result);
    assert(status == SUCCESS);
    assert(result == 5);
    
    // Троичная система
    status = str_to_base10("12", 3, &result);
    assert(status == SUCCESS);
    assert(result == 5); // 1*3 + 2 = 5
    
    // Четверичная система
    status = str_to_base10("123", 4, &result);
    assert(status == SUCCESS);
    assert(result == 27); // 1*16 + 2*4 + 3 = 27
    
    // Десятичная система
    status = str_to_base10("123", 10, &result);
    assert(status == SUCCESS);
    assert(result == 123);
    
    // 16-ричная система
    status = str_to_base10("1F", 16, &result);
    assert(status == SUCCESS);
    assert(result == 31);
    
    status = str_to_base10("A", 11, &result);
    assert(status == SUCCESS);
    assert(result == 10);
    
    // 17-ричная система с G
    status = str_to_base10("G", 17, &result);
    assert(status == SUCCESS);
    assert(result == 16);
    
    status = str_to_base10("1G", 17, &result);
    assert(status == SUCCESS);
    assert(result == 33); // 1*17 + 16 = 33
    
    // Недопустимые случаи
    status = str_to_base10("12", 1, &result); // Основание < 2
    assert(status == ERROR_INVALID_CHARACTER);
    
    status = str_to_base10("12", 37, &result); // Основание > 36
    assert(status == ERROR_INVALID_CHARACTER);
    
    status = str_to_base10("12[", 16, &result); // Недопустимый символ
    assert(status == ERROR_INVALID_CHARACTER);
    
    status = str_to_base10("2", 2, &result); // Цифра >= основания
    assert(status == ERROR_INVALID_CHARACTER);
    
    status = str_to_base10("G", 16, &result); // G в 16-ричной системе
    assert(status == ERROR_INVALID_CHARACTER); // G=16, но основание=16
    
    printf("str_to_base10 tests passed!\n");
}

// Тесты для process_number
void test_process_number() {
    printf("Testing process_number...\n");
    
    char output[BUFFER_SIZE];
    int base;
    long long decimal;
    StatusCode status;
    
    // Корректные числа
    status = process_number("101", output, &base, &decimal);
    assert(status == SUCCESS);
    assert(strcmp(output, "101") == 0);
    assert(base == 2);
    assert(decimal == 5);
    
    status = process_number("00A", output, &base, &decimal);
    assert(status == SUCCESS);
    assert(strcmp(output, "A") == 0);
    assert(base == 11);
    assert(decimal == 10);
    
    status = process_number("0000", output, &base, &decimal);
    assert(status == SUCCESS);
    assert(strcmp(output, "0") == 0);
    assert(base == 2);
    assert(decimal == 0);
    
    status = process_number("123", output, &base, &decimal);
    assert(status == SUCCESS);
    assert(strcmp(output, "123") == 0);
    assert(base == 4);  // макс. цифра 3 → основание 4
    assert(decimal == 27); // 1*16 + 2*4 + 3 = 27
    
    status = process_number("1Z", output, &base, &decimal);
    assert(status == SUCCESS);
    assert(base == 36);
    assert(decimal == 71); // 1*36 + 35 = 71
    
    // Число с G (17-ричная система)
    status = process_number("G", output, &base, &decimal);
    assert(status == SUCCESS);
    assert(base == 17);
    assert(decimal == 16);
    
    // Некорректные числа
    status = process_number("12[", output, &base, &decimal);
    assert(status == ERROR_INVALID_CHARACTER);
    
    // Тест на очень длинное число (больше BUFFER_SIZE)
    char long_number[BUFFER_SIZE + 10];
    memset(long_number, '1', BUFFER_SIZE + 5);
    long_number[BUFFER_SIZE + 5] = '\0';
    status = process_number(long_number, output, &base, &decimal);
    assert(status == ERROR_INVALID_CHARACTER);
    
    printf("process_number tests passed!\n");
}

// Интеграционный тест - эмуляция работы с файлами
void test_integration() {
    printf("Testing integration...\n");
    
    // Создаем временные файлы
    FILE *fin = fopen("test_input.txt", "w");
    assert(fin != NULL);
    fprintf(fin, "101 00A 123 000 G 12[\n"); // 12[ - ошибка, остальные корректны
    fclose(fin);
    
    FILE *fout = fopen("test_output.txt", "w");
    assert(fout != NULL);
    
    // Обрабатываем файл
    fin = fopen("test_input.txt", "r");
    StatusCode status = process_file(fin, fout);
    fclose(fin);
    fclose(fout);
    
    // Проверяем что функция завершилась успешно (несмотря на одно ошибочное число)
    assert(status == SUCCESS);
    
    // Проверяем результат
    fout = fopen("test_output.txt", "r");
    assert(fout != NULL);
    
    char line[BUFFER_SIZE];
    int line_count = 0;
    int success_count = 0;
    int error_count = 0;
    
    while (fgets(line, sizeof(line), fout)) {
        line_count++;
        if (strstr(line, "ERROR") != NULL) {
            error_count++;
        } else {
            success_count++;
        }
    }
    fclose(fout);
    
    // Должно быть 6 строк (5 успешных + 1 ошибка)
    assert(line_count == 6);
    assert(success_count == 5);
    assert(error_count == 1);
    
    printf("Integration test passed!\n");
}

// Тест на обработку ошибок в process_file
void test_process_file_errors() {
    printf("Testing process_file error handling...\n");
    
    // Создаем файл с разными числами
    FILE *fin = fopen("test_error_input.txt", "w");
    assert(fin != NULL);
    fprintf(fin, "123 456 78[ 90A\n"); // 78[ - ошибка, остальные корректны
    fclose(fin);
    
    FILE *fout = fopen("test_error_output.txt", "w");
    assert(fout != NULL);
    
    fin = fopen("test_error_input.txt", "r");
    StatusCode status = process_file(fin, fout);
    fclose(fin);
    fclose(fout);
    
    // Должен вернуть SUCCESS, так как ошибки обрабатываются внутри
    assert(status == SUCCESS);
    
    printf("process_file error handling test passed!\n");
}

// Тест на граничные случаи
void test_edge_cases() {
    printf("Testing edge cases...\n");
    
    char output[BUFFER_SIZE];
    int base;
    long long decimal;
    StatusCode status;
    
    // Максимальное основание (36)
    status = process_number("Z", output, &base, &decimal);
    assert(status == SUCCESS);
    assert(base == 36);
    assert(decimal == 35);
    
    // Число с максимально возможными цифрами
    status = process_number("ZZ", output, &base, &decimal);
    assert(status == SUCCESS);
    assert(base == 36);
    assert(decimal == 35 * 36 + 35); // 1295
    
    // Число из всех нулей
    status = process_number("000000", output, &base, &decimal);
    assert(status == SUCCESS);
    assert(strcmp(output, "0") == 0);
    assert(base == 2);
    assert(decimal == 0);
    
    // Число с разным регистром букв
    status = process_number("aBc", output, &base, &decimal);
    assert(status == SUCCESS);
    assert(base == 13); // макс. цифра c=12 → основание 13
    // a=10, B=11, c=12: 10*169 + 11*13 + 12 = 1690 + 143 + 12 = 1845
    assert(decimal == 1845);
    
    printf("Edge cases tests passed!\n");
}

int main() {
    printf("Starting unit tests...\n\n");
    
    test_char_to_value();
    test_min_base();
    test_remove_leading_zeros();
    test_str_to_base10();
    test_process_number();
    test_edge_cases();
    test_integration();
    test_process_file_errors();
    
    printf("\nAll tests passed! ✓\n");
    return 0;
}