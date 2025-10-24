#ifndef INCLUDE_H
#define INCLUDE_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int overfscanf(FILE *stream, const char *format, ...);
int oversscanf(const char *str, const char *format, ...);

int roman_to_int(const char *roman);
unsigned int zeckendorf_to_uint(const char *zeck);
long long str_to_int_base_ptr(const char **str, int base, int uppercase);

void runAllTests(void);

#endif