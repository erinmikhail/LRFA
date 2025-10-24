#ifndef INCLUDE_H
#define INCLUDE_H

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int overfprintf(FILE *stream, const char *format, ...);
int oversprintf(char *str, const char *format, ...);

char* int_to_roman(int num);
char* zeckendorf_representation(unsigned int num);
char* int_to_base(int num, int base, int uppercase);
long long str_to_int_base(const char *str, int base, int uppercase);
char* memory_dump_int(int value);
char* memory_dump_uint(unsigned int value);
char* memory_dump_double(double value);
char* memory_dump_float(float value);

char* byte_to_binary(unsigned char byte);
int is_valid_base(int base);

void runAllTests(void);

#endif