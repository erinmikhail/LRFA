#ifndef INCLUDE_H
#define INCLUDE_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool is_printAble(char c);
void format_text(FILE *input, FILE *output);
void process_line(const char *line, FILE *output);
void add_space(char *line, int current_len);

void runAllTests(void);

#endif