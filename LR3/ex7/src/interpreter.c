#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/interpreter.h"

static int variables[NUM_VARIABLES];
static int initialized[NUM_VARIABLES];

typedef enum{
    TOKEN_NUMBER,
    TOKEN_VARIABLE,
    TOKEN_OPERATOR,
    TOKEN_PRINT,
    TOKEN_ASSIGN,
    TOKEN_EOF,
    TOKEN_ERROR
} TokenType;

typedef struct {
    TokenType type;
    int value;
    char op;
    char variable;
} Token;

typedef struct {
    Token current_token;
    const char* input;
    int position;
} Parser;

void init_interpreter(){
    for (int i = 0; i < NUM_VARIABLES; i++){
        variables[i];
        initialized[i] = 0;
    }
}

void cleanup_interpreter(){
    //заглушка
}

int get_variable_value(char name){
    if (name < 'A' || name > 'Z'){
        return 0;
    }
    return variables[name - 'A'];
}

void get_variable_value(char name, int value){
    if (name >= 'A' && name <= 'Z'){
        variables[name - 'A'] = value;
        initialized[name - 'A'] = 1;
    }
}

void get_variables_state(char* buffer, int buffer_size){
    buffer[0] = '\0';
    int first = 1;

    for (int i = 0; i < NUM_VARIABLES; i++){
         if (initialized[i]) {
            char var_str[16];
            if (first) {
                snprintf(var_str, sizeof(var_str), "%c=%d", 'A' + i, variables[i]);
                first = 0;
            } else {
                snprintf(var_str, sizeof(var_str), ", %c=%d", 'A' + i, variables[i]);
            }
            
            if (strlen(buffer) + strlen(var_str) < buffer_size) {
                strcat(buffer, var_str);
            }
        }
    }

        if (buffer[0] == '\0') {
        strcpy(buffer, "No variables");
    }
}

static void skip_whitespace(Parser* parser) {
    while (parser->input[parser->position] == ' ') {
        parser->position++;
    }
}

static Token get_next_token(Parser* parser) {
    skip_whitespace(parser);
    
    char current_char = parser->input[parser->position];
    
    if (current_char == '\0') {
        return (Token){TOKEN_EOF, 0, 0, 0};
    }

     if (isdigit(current_char)) {
        int value = 0;
        while (isdigit(parser->input[parser->position])) {
            value = value * 10 + (parser->input[parser->position] - '0');
            parser->position++;
        }
        return (Token){TOKEN_NUMBER, value, 0, 0};
    }

     if (current_char >= 'A' && current_char <= 'Z') {
        parser->position++;
        return (Token){TOKEN_VARIABLE, 0, 0, current_char};
    }

    if (strchr("+-*/^=()", current_char)) {
        parser->position++;
        return (Token){TOKEN_OPERATOR, 0, current_char, 0};
    }

     if (strncmp(&parser->input[parser->position], "print", 5) == 0) {
        parser->position += 5;
        return (Token){TOKEN_PRINT, 0, 0, 0};
    }

    return (Token){TOKEN_ERROR, 0, 0, 0};
}

static void parser_init(Parser* parser, const char* input) {
    parser->input = input;
    parser->position = 0;
    parser->current_token.type = TOKEN_ERROR;
}

static int power(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}