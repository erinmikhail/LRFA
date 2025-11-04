#include "ex8_lr1.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void test_get_char_type() {
    printf("Testing get_char_type...\n");
    
    assert(get_char_type('0') == DIGIT);
    assert(get_char_type('5') == DIGIT);
    assert(get_char_type('9') == DIGIT);
    assert(get_char_type('A') == UPPERCASE_LETTER);
    assert(get_char_type('Z') == UPPERCASE_LETTER);
    assert(get_char_type('F') == UPPERCASE_LETTER);
    assert(get_char_type('a') == INVALID_SYMBOL);
    assert(get_char_type('@') == INVALID_SYMBOL);
    assert(get_char_type('[') == INVALID_SYMBOL);
    assert(get_char_type(' ') == INVALID_SYMBOL);
    
    printf("get_char_type tests passed!\n");
}

void test_char_to_value() {
    printf("Testing char_to_value...\n");
    
    assert(char_to_value('0') == 0);
    assert(char_to_value('5') == 5);
    assert(char_to_value('9') == 9);
    assert(char_to_value('A') == 10);
    assert(char_to_value('F') == 15);
    assert(char_to_value('Z') == 35);
    assert(char_to_value('a') == -1);
    assert(char_to_value('@') == -1);
    assert(char_to_value('[') == -1);
    
    printf("char_to_value tests passed!\n");
}

void test_value_to_char() {
    printf("Testing value_to_char...\n");
    
    assert(value_to_char(0) == '0');
    assert(value_to_char(5) == '5');
    assert(value_to_char(9) == '9');
    assert(value_to_char(10) == 'A');
    assert(value_to_char(15) == 'F');
    assert(value_to_char(35) == 'Z');
    assert(value_to_char(-1) == '?');
    assert(value_to_char(36) == '?');
    
    printf("value_to_char tests passed!\n");
}

void test_validate_number() {
    printf("Testing validate_number...\n");
    
    assert(validate_number("123", 10) == SUCCESS);
    assert(validate_number("A", 11) == SUCCESS);
    assert(validate_number("FF", 16) == SUCCESS);
    assert(validate_number("-123", 10) == SUCCESS);
    assert(validate_number("-A", 11) == SUCCESS);
    assert(validate_number("", 10) == ERROR_EMPTY_INPUT);
    assert(validate_number("12A", 10) == ERROR_INVALID_CHARACTER);
    assert(validate_number("12", 2) == ERROR_INVALID_CHARACTER);
    assert(validate_number("1G", 16) == ERROR_INVALID_CHARACTER);
    assert(validate_number("1a", 16) == ERROR_INVALID_CHARACTER);
    
    printf("validate_number tests passed!\n");
}

void test_str_to_base10() {
    printf("Testing str_to_base10...\n");
    
    assert(str_to_base10("101", 2) == 5);
    assert(str_to_base10("12", 3) == 5);
    assert(str_to_base10("123", 4) == 27);
    assert(str_to_base10("FF", 16) == 255);
    assert(str_to_base10("A", 11) == 10);
    assert(str_to_base10("-101", 2) == -5);
    assert(str_to_base10("-FF", 16) == -255);
    assert(str_to_base10("-A", 11) == -10);
    assert(str_to_base10("0", 10) == 0);
    assert(str_to_base10("0", 2) == 0);
    
    printf("str_to_base10 tests passed!\n");
}

void test_convert_base_to_base() {
    printf("Testing convert_base_to_base...\n");
    
    char result[BUFFER_SIZE];
    StatusCode status;
    
    status = convert_base_to_base("101", 2, 10, result);
    assert(status == SUCCESS);
    assert(strcmp(result, "5") == 0);
    
    status = convert_base_to_base("FF", 16, 10, result);
    assert(status == SUCCESS);
    assert(strcmp(result, "255") == 0);
    
    status = convert_base_to_base("255", 10, 16, result);
    assert(status == SUCCESS);
    assert(strcmp(result, "FF") == 0);
    
    status = convert_base_to_base("A", 11, 10, result);
    assert(status == SUCCESS);
    assert(strcmp(result, "10") == 0);
    
    status = convert_base_to_base("-101", 2, 10, result);
    assert(status == SUCCESS);
    assert(strcmp(result, "-5") == 0);
    
    status = convert_base_to_base("-FF", 16, 10, result);
    assert(status == SUCCESS);
    assert(strcmp(result, "-255") == 0);
    
    status = convert_base_to_base("0", 10, 16, result);
    assert(status == SUCCESS);
    assert(strcmp(result, "0") == 0);
    
    status = convert_base_to_base("123", 1, 10, result);
    assert(status == ERROR_INVALID_BASE);
    
    status = convert_base_to_base("123", 10, 37, result);
    assert(status == ERROR_INVALID_BASE);
    
    printf("convert_base_to_base tests passed!\n");
}

void test_remove_leading_zeros() {
    printf("Testing remove_leading_zeros...\n");
    
    char buffer[BUFFER_SIZE];
    
    strcpy(buffer, "00123");
    remove_leading_zeros(buffer);
    assert(strcmp(buffer, "123") == 0);
    
    strcpy(buffer, "0000");
    remove_leading_zeros(buffer);
    assert(strcmp(buffer, "0") == 0);
    
    strcpy(buffer, "0");
    remove_leading_zeros(buffer);
    assert(strcmp(buffer, "0") == 0);
    
    strcpy(buffer, "100");
    remove_leading_zeros(buffer);
    assert(strcmp(buffer, "100") == 0);
    
    strcpy(buffer, "-00123");
    remove_leading_zeros(buffer);
    assert(strcmp(buffer, "-123") == 0);
    
    strcpy(buffer, "-0000");
    remove_leading_zeros(buffer);
    assert(strcmp(buffer, "-0") == 0);
    
    strcpy(buffer, "00A");
    remove_leading_zeros(buffer);
    assert(strcmp(buffer, "A") == 0);
    
    printf("remove_leading_zeros tests passed!\n");
}

void test_required_bases_conversion() {
    printf("Testing required bases conversion...\n");
    
    char result[BUFFER_SIZE];
    StatusCode status;
    
    struct TestCase {
        const char* decimal_str;
        int target_base;
        const char* expected;
    } test_cases[] = {
        {"255", 9,  "313"},
        {"255", 18, "E3"},
        {"255", 27, "9C"},
        {"255", 36, "73"},
        {"100", 9,  "121"},
        {"100", 18, "5A"},
        {"0",   9,  "0"},
        {"10",  18, "A"},
        {"35",  36, "Z"}
    };
    
    int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_cases; i++) {
        status = convert_base_to_base(test_cases[i].decimal_str, 10, test_cases[i].target_base, result);
        assert(status == SUCCESS);
        
        remove_leading_zeros(result);
        assert(strcmp(result, test_cases[i].expected) == 0);
    }
    
    printf("required_bases_conversion tests passed!\n");
}

void test_find_max_absolute_logic() {
    printf("Testing find_max_absolute logic...\n");
    
    char* test_numbers[] = {"1A", "FF", "-2B", "7", "-80"};
    int base = 16;
    
    Number max_number = {"", 0, 0};
    int numbers_count = 0;
    
    for (int i = 0; i < 5; i++) {
        StatusCode validation_status = validate_number(test_numbers[i], base);
        assert(validation_status == SUCCESS);
        
        long long current_value = str_to_base10(test_numbers[i], base);
        long long current_abs_value = llabs(current_value);
        long long max_abs_value = llabs(max_number.decimal_value);
        
        if (numbers_count == 0 || current_abs_value > max_abs_value) {
            strcpy(max_number.original_str, test_numbers[i]);
            max_number.decimal_value = current_value;
            max_number.original_base = base;
        }
        
        numbers_count++;
    }
    
    assert(strcmp(max_number.original_str, "FF") == 0);
    assert(max_number.decimal_value == 255);
    assert(max_number.original_base == 16);
    
    printf("find_max_absolute_logic tests passed!\n");
}

void test_edge_cases() {
    printf("Testing edge cases...\n");
    
    char result[BUFFER_SIZE];
    
    StatusCode status = convert_base_to_base("ZZ", 36, 10, result);
    assert(status == SUCCESS);
    assert(strcmp(result, "1295") == 0);
    
    status = convert_base_to_base("1", 2, 10, result);
    assert(status == SUCCESS);
    assert(strcmp(result, "1") == 0);
    
    status = convert_base_to_base("Z", 36, 10, result);
    assert(status == SUCCESS);
    assert(strcmp(result, "35") == 0);
    
    char long_number[100];
    memset(long_number, '1', 50);
    long_number[50] = '\0';
    assert(validate_number(long_number, 2) == SUCCESS);
    
    printf("edge_cases tests passed!\n");
}

int main() {
    printf("Starting EX8 unit tests...\n\n");
    
    test_get_char_type();
    test_char_to_value();
    test_value_to_char();
    test_validate_number();
    test_str_to_base10();
    test_convert_base_to_base();
    test_remove_leading_zeros();
    test_required_bases_conversion();
    test_find_max_absolute_logic();
    test_edge_cases();
    
    printf("\nAll EX8 tests passed! ✓\n");
    return 0;
}