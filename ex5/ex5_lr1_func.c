#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ex5_lr1.h"

int is_latin_letter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int is_arabic_digit(char c) {
    return c >= '0' && c <= '9';
}

int is_space(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

void process_d(FILE *in, FILE *out) {
    char c;
    while ((c = fgetc(in)) != EOF) {
        if (!is_arabic_digit(c))
            fputc(c, out);
    }
}

void process_i(FILE *in, FILE *out) {
    char line[1024];
    while (fgets(line, sizeof(line), in)) {
        int count = 0;
        for (int i = 0; line[i] != '\0'; i++) {
            if (is_latin_letter(line[i]))
                count++;
        }
        fprintf(out, "%d\n", count);
    }
}

void process_s(FILE *in, FILE *out) {
    char line[1024];
    while (fgets(line, sizeof(line), in)) {
        int count = 0;
        for (int i = 0; line[i] != '\0'; i++) {
            char ch = line[i];
            if (!is_latin_letter(ch) && !is_arabic_digit(ch) && !is_space(ch))
                count++;
        }
        fprintf(out, "%d\n", count);
    }
}

void process_a(FILE *in, FILE *out) {
    char c;
    while ((c = fgetc(in)) != EOF) {
        if (is_arabic_digit(c))
            fputc(c, out);
        else
            fprintf(out, "%02X", (unsigned char)c);
    }
}

void get_filename(const char *path, char *filename) {
    int len = strlen(path);
    int last_slash = -1;
    
    for (int i = 0; i < len; i++) {
        if (path[i] == '/' || path[i] == '\\') {
            last_slash = i;
        }
    }

    if (last_slash == -1) {
        strcpy(filename, path);
    } else {
        strcpy(filename, path + last_slash + 1);
    }
}

int validate_arguments(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Недостаточно аргументов\n");
        printf("Использование: %s [-/][n][flag] input_file [output_file]\n", argv[0]);
        printf("Флаги: d - удалить цифры, i - подсчитать буквы, s - подсчитать спецсимволы, a - заменить на HEX\n");
        return 0;
    }
    return 1;
}

int parse_flag(const char *flag, char *action_flag, int *has_n) {
    if (flag[0] != '-' && flag[0] != '/') {
        printf("Неверный формат флага: %s\n", flag);
        printf("Флаг должен начинаться с '-' или '/'\n");
        return 0;
    }

    if (flag[1] == 'n' && flag[2] != '\0') {
        *has_n = 1;
        *action_flag = flag[2];
    } else {
        *has_n = 0;
        *action_flag = flag[1];
    }

    if (*action_flag == '\0') {
        printf("Неверный формат флага: %s\n", flag);
        return 0;
    }

    return 1;
}

int create_output_path(char *output_path, const char *input_path, int has_n, char *argv[]) {
    if (has_n && argv[3] != NULL) {
        strcpy(output_path, argv[3]);
    } else {
        char filename[100];
        get_filename(input_path, filename);
        sprintf(output_path, "out_%s", filename);
    }
    return 1;
}