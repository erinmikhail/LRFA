#include "ex1.h"
#include <assert.h>
#include <string.h>

// Тестовая функция для проверки has_finite_rep
void test_has_finite_rep() {
    printf("=== Тестирование has_finite_rep ===\n");
    
    // Отладочная информация для 0.1 в двоичной
    printf("Проверка 0.1 в двоичной системе:\n");
    bool test1 = has_finite_rep(0.1, 2);
    printf("Результат: %s (ожидается: бесконечное)\n\n", test1 ? "конечное" : "бесконечное");
    
    // Тест 1: Конечные представления
    assert(has_finite_rep(0.5, 2) == true);    // 0.5 в двоичной = 0.1
    assert(has_finite_rep(0.25, 2) == true);   // 0.25 в двоичной = 0.01
    assert(has_finite_rep(0.125, 2) == true);  // 0.125 в двоичной = 0.001
    assert(has_finite_rep(0.5, 10) == true);   // 0.5 в десятичной = 0.5
    assert(has_finite_rep(0.2, 10) == true);   // 0.2 в десятичной = 0.2
    
    // Тест 2: Бесконечные представления
    assert(has_finite_rep(0.1, 2) == false);   // 0.1 в двоичной бесконечно
    assert(has_finite_rep(0.333333, 2) == false); // 1/3 в двоичной бесконечно
    assert(has_finite_rep(0.1, 3) == false);   // 0.1 в троичной бесконечно
    
    // Тест 3: Граничные случаи
    assert(has_finite_rep(0.999999, 2) == false); // Почти 1
    assert(has_finite_rep(0.000001, 2) == false); // Почти 0
    
    // Тест 4: Некорректные входные данные
    assert(has_finite_rep(1.0, 2) == false);   // Вне диапазона
    assert(has_finite_rep(0.0, 2) == false);   // Вне диапазона
    assert(has_finite_rep(0.5, 1) == false);   // Неправильное основание
    
    printf("Все тесты has_finite_rep пройдены успешно!\n\n");
}

// Тест для get_system_name
void test_get_system_name() {
    printf("=== Тестирование get_system_name ===\n");
    
    assert(strcmp(get_system_name(BINARY), "двоичная") == 0);
    assert(strcmp(get_system_name(OCTAL), "восьмеричная") == 0);
    assert(strcmp(get_system_name(DECIMAL), "десятичная") == 0);
    assert(strcmp(get_system_name(HEXADECIMAL), "шестнадцатеричная") == 0);
    assert(strcmp(get_system_name(CUSTOM_BASE), "произвольная") == 0);
    
    printf("Все тесты get_system_name пройдены успешно!\n\n");
}

// Демонстрационные тесты для функций с переменным числом аргументов
void test_variadic_functions() {
    printf("=== Тестирование функций с переменным числом аргументов ===\n");
    
    printf("Тест 1: Двоичная система\n");
    check_finite_rep_count(BINARY, 3, 0.5, 0.25, 0.1);
    
    printf("Тест 2: Десятичная система\n");
    check_finite_rep_count(DECIMAL, 2, 0.5, 0.333333);
    
    printf("Тест 3: Восьмеричная система с маркером\n");
    check_finite_rep_sentinel(OCTAL, 0.5, 0.125, 0.1, 0.0);
    
    printf("Тесты функций с переменным числом аргументов завершены!\n\n");
}

// Основная функция тестирования
int main() {
    printf("ЗАПУСК UNIT-ТЕСТОВ\n");
    printf("==================\n\n");
    
    test_has_finite_rep();
    test_get_system_name();
    test_variadic_functions();
    
    printf("=== ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО! ===\n");
    return 0;
}