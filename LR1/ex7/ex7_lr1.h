#ifndef EX7_LR1_H
#define EX7_LR1_H

#include <stdio.h>


typedef enum {
    MIN_BASE = 2,
    MAX_BASE = 36,
    BUFFER_SIZE = 256,
    INVALID_CHAR_VALUE = -1
} Constants;


typedef enum {
    SUCCESS = 0,
    ERROR_OPEN_INPUT_FILE = 1,
    ERROR_OPEN_OUTPUT_FILE = 2,
    ERROR_INVALID_CHARACTER = 3,
    ERROR_INVALID_ARGUMENTS = 4,
    ERROR_READING_FILE = 5
} StatusCode;


int char_to_value(char c);
int min_base(const char *num_str);
StatusCode str_to_base10(const char *num_str, int base, long long *result);
void remove_leading_zeros(char *str);
StatusCode process_file(FILE *fin, FILE *fout);
StatusCode process_number(const char *input, char *output, int *base, long long *decimal);

#endif