#include "ex8_lr1.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

CharType get_char_type(char c) {
    if (c >= '0' && c <= '9') {
        return DIGIT;
    } else if (c >= 'A' && c <= 'Z') {
        return UPPERCASE_LETTER;
    } else {
        return INVALID_SYMBOL;
    }
}

int char_to_value(char c) {
    CharType type = get_char_type(c);
    
    switch (type) {
        case DIGIT:
            return c - '0';
        case UPPERCASE_LETTER:
            return c - 'A' + 10;
        case INVALID_SYMBOL:
        default:
            return -1;
    }
}

char value_to_char(int value) {
    if (value >= 0 && value <= 9) {
        return '0' + value;
    } else if (value >= 10 && value <= 35) {
        return 'A' + (value - 10);
    } else {
        return '?';
    }
}

StatusCode validate_number(const char *str, int base) {
    if (str == NULL || str[0] == '\0') {
        return ERROR_EMPTY_INPUT;
    }
    
    const char *p = str;
    
    if (*p == '-') {
        p++;
    }
    
    for (; *p; p++) {
        int digit_value = char_to_value(*p);
        
        if (digit_value == -1) {
            return ERROR_INVALID_CHARACTER;
        }
        
        if (digit_value >= base) {
            return ERROR_INVALID_CHARACTER;
        }
    }
    
    return SUCCESS;
}

long long str_to_base10(const char *str, int base) {
    long long result = 0;
    
    int sign = 1;
    const char *p = str;
    
    if (*p == '-') {
        sign = -1;
        p++;
    }
    
    for (; *p; p++) {
        int digit_value = char_to_value(*p);
        result = result * base + digit_value;
    }
    
    return result * sign;
}

StatusCode convert_base_to_base(const char *input_str, int from_base, int to_base, char *result) {
    if (from_base < MIN_BASE || from_base > MAX_BASE || 
        to_base < MIN_BASE || to_base > MAX_BASE) {
        return ERROR_INVALID_BASE;
    }
    
    long long decimal_value = str_to_base10(input_str, from_base);
    
    if (decimal_value == 0) {
        result[0] = '0';
        result[1] = '\0';
        return SUCCESS;
    }
    
    int is_negative = 0;
    unsigned long long abs_num;
    
    if (decimal_value < 0) {
        is_negative = 1;
        abs_num = -decimal_value;
    } else {
        abs_num = decimal_value;
    }
    
    char temp[BUFFER_SIZE];
    int index = 0;
    
    while (abs_num > 0) {
        int digit = abs_num % to_base;
        temp[index++] = value_to_char(digit);
        abs_num /= to_base;
        
        if (index >= BUFFER_SIZE - 2) {
            return ERROR_CONVERSION;
        }
    }
    
    int result_index = 0;
    if (is_negative) {
        result[result_index++] = '-';
    }
    
    for (int i = index - 1; i >= 0; i--) {
        result[result_index++] = temp[i];
    }
    result[result_index] = '\0';
    
    return SUCCESS;
}

void remove_leading_zeros(char *str) {
    char *dst = str;
    char *src = str;
    
    if (*src == '-') {
        *dst++ = *src++;
    }
    
    while (*src == '0' && *(src + 1) != '\0') {
        src++;
    }
    
    while (*src) {
        *dst++ = *src++;
    }
    *dst = '\0';
}