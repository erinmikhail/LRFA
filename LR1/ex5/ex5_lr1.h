#ifndef EX5_LR1_H
#define EX5_LR1_H

#include <stdio.h>


int is_latin_letter(char c);
int is_arabic_digit(char c);
int is_space(char c);


void process_d(FILE *in, FILE *out);
void process_i(FILE *in, FILE *out);
void process_s(FILE *in, FILE *out);
void process_a(FILE *in, FILE *out);


void get_filename(const char *path, char *filename);


int validate_arguments(int argc, char *argv[]);
int parse_flag(const char *flag, char *action_flag, int *has_n);
int create_output_path(char *output_path, const char *input_path, int has_n, char *argv[]);

#endif