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