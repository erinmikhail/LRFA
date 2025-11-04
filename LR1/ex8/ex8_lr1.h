#ifndef EX8_LR1_H
#define EX8_LR1_H

#include <stdio.h>

typedef enum {
    MIN_BASE = 2,
    MAX_BASE = 36,
    BUFFER_SIZE = 256,
    OUTPUT_BASES_COUNT = 4
} Constants;

typedef enum {
    SUCCESS = 0,
    ERROR_INVALID_BASE = 1,
    ERROR_INVALID_CHARACTER = 2,
    ERROR_EMPTY_INPUT = 3,
    ERROR_READING_INPUT = 4,
    ERROR_CONVERSION = 5
} StatusCode;

typedef enum {
    DIGIT = 0,
    UPPERCASE_LETTER = 1,
    INVALID_SYMBOL = 2
} CharType;

typedef struct {
    char original_str[BUFFER_SIZE];
    long long decimal_value;
    int original_base;
} Number;

CharType get_char_type(char c);
int char_to_value(char c);
char value_to_char(int value);
long long str_to_base10(const char *str, int base);
StatusCode convert_base_to_base(const char *input_str, int from_base, int to_base, char *result);
void remove_leading_zeros(char *str);
StatusCode validate_number(const char *str, int base);
StatusCode find_max_absolute(void);

#endif