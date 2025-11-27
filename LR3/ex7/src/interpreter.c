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